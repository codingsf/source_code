#include "MacthEngine.h"
#include <muduo/base/Logging.h>
#include <unistd.h>
#include <iostream>
#include <sched.h>
#include <muduo/base/Timestamp.h>
CMacthEngine::CMacthEngine()
{
	m_pOrderCache = new STOrderCache[MAX_ORDER_INDEX];
//	memset(m_pOrderCache, 0, sizeof(STOrderCache)*MAX_ORDER_INDEX);

// 	m_hashMapExAsk.clear();
// 	m_hashMapExBid.clear();
	m_mapMatchExch.clear();
	m_pInputRingBuf = new XRingBuffer(RING_BUF_SIZE);
	m_pOutputRingBuf = new XRingBuffer(RING_BUF_SIZE);
	//�������������ڴ���е�һ����
	m_pFirstOrder = m_memPool.allocate(1);
//	m_pRemAskOrder = NULL;
//m_pRemBidOrder = NULL;
	m_listMarketAskOrder.clear();
	m_listMarketBidOrder.clear();
	m_iProcCnt = 0;
	m_iWriteWaitCnt = 0;
	m_iSetCpuID = 255;
	m_threadID = 0;
	m_lStartTime = 0;
}


CMacthEngine::~CMacthEngine()
{
	ExitWork();
	m_bIsRunning = false;
	m_listMarketAskOrder.clear();
	m_listMarketBidOrder.clear();
	if (m_pOrderCache)
	{
		delete []m_pOrderCache;
	}
	if (m_pInputRingBuf)
	{
		delete[]m_pInputRingBuf;
	}
	if (m_pOutputRingBuf)
	{
		delete[]m_pOutputRingBuf;
	}
	if (m_bIsRunning)
		ExitWork();
}

bool CMacthEngine::AddAskOrBidOrder(STSubmitOrderInfo* pOrderInfo, STOrderBookInfo* pOrderBookInfo)
{
	//�����ί����/�����Ļ���������Ҫ�鿴�Ƿ���ʣ����г����������еĻ��������ȴ���
	std::list<STSubmitOrderInfo*>* pListOrder = (pOrderInfo->ucTransType == EN_ORDER_BID) ? &m_listMarketAskOrder : &m_listMarketBidOrder;
	while (pListOrder->size() > 0)
	{
		STExechOrderinfo stExecOrder;
		STSubmitOrderInfo* pMarketOrder = pListOrder->front();
		//���ί�е�С�ڻ�����г����������еĵ�һ����
		if ((pOrderInfo->fNumber < pMarketOrder->fNumber) || IsFloatEqual(pOrderInfo->fNumber, pMarketOrder->fNumber))
		{
			//����ɽ�������д��ɽ���ϸ��
			stExecOrder.lExchID = ++m_ulTransID;
			stExecOrder.lPrice = pOrderInfo->lPrice;
			stExecOrder.fNumber = pOrderInfo->fNumber;
			stExecOrder.lAskOrderID = (pOrderInfo->ucTransType == EN_ORDER_BID) ? pMarketOrder->lSubmitOrderID : pOrderInfo->lSubmitOrderID;
			stExecOrder.lBidOrderID = (pOrderInfo->ucTransType == EN_ORDER_BID) ? pOrderInfo->lSubmitOrderID : pMarketOrder->lSubmitOrderID;
			stExecOrder.ucExchType = 1;
			WriteTransferOrder(&stExecOrder);
			//����պ���ȵĻ�������г������б��е����ζ���
			if (IsFloatEqual(pOrderInfo->fNumber, pMarketOrder->fNumber))
			{
				//����Ԫ�أ������ڴ�
				pListOrder->pop_front();
				m_memPool.destroy(pMarketOrder);
				m_memPool.deallocate(pMarketOrder);
			}
			else
			{
				pMarketOrder->fNumber -= pOrderInfo->fNumber;
				pMarketOrder->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
			}
			//��ί�е���������ֱ��
			return true;
		}
		else
		{
			//����ɽ�������д��ɽ���ϸ��
			stExecOrder.lExchID = ++m_ulTransID;
			stExecOrder.lPrice = pOrderInfo->lPrice;
			stExecOrder.fNumber = pMarketOrder->fNumber;
			stExecOrder.lAskOrderID = (pOrderInfo->ucTransType == EN_ORDER_BID) ? pMarketOrder->lSubmitOrderID : pOrderInfo->lSubmitOrderID;
			stExecOrder.lBidOrderID = (pOrderInfo->ucTransType == EN_ORDER_BID) ? pOrderInfo->lSubmitOrderID : pMarketOrder->lSubmitOrderID;
			stExecOrder.ucExchType = 1;
			WriteTransferOrder(&stExecOrder);

			//���ί�е������г�������������б��е������г���
			pOrderInfo->fNumber -= pMarketOrder->fNumber;
			pOrderInfo->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
			pListOrder->pop_front();
			m_memPool.destroy(pMarketOrder);
			m_memPool.deallocate(pMarketOrder);
		}
	}

	//�ܽ���˲�˵��֮ǰ���г����������Ѿ��������꣬��ʱ��ί�ж������뵽OrderBook��ȥ
	MapOrderBook* pMapOrderBook = (pOrderInfo->ucTransType == EN_ORDER_BID) ? &(pOrderBookInfo->mapBidOrderBook) : &(pOrderBookInfo->mapAskOrderBook);
	MapOrderBook::iterator iter = pMapOrderBook->find(pOrderInfo->lPrice);
	STSubmitOrderInfo* pTmpOrder = NULL;
	//��ȡ�ڴ���еĵ�ַ
	if (NULL != m_pFirstOrder)
	{
		pTmpOrder = m_pFirstOrder;
		m_pFirstOrder = NULL;//ֻʹ��1�Σ�Ŀ����Ϊ��ʹ���ڴ�صĵ�һ�����ڴ�ķ����ڹ��캯���׶ξͽ��з���
	}
	else
		pTmpOrder = m_memPool.allocate(1);
	memcpy(pTmpOrder, pOrderInfo, sizeof(STSubmitOrderInfo));
	//���ռ۸�ȥ���Ҳ����뵽OrderBool��ȥ
	if (iter != pMapOrderBook->end())
	{
		//����ʱ����ж����ļ���
		iter->second.fTotalNumber += pTmpOrder->fNumber;
		iter->second.mulmapOrder.insert(std::make_pair(pOrderInfo->lSubmitTime, pTmpOrder));
	}
	else
	{
		STPriceOrderInfo stPriceOrder;
		stPriceOrder.fTotalNumber = pTmpOrder->fNumber;
		stPriceOrder.mulmapOrder.insert(std::make_pair(pOrderInfo->lSubmitTime, pTmpOrder));
		pMapOrderBook->insert(std::make_pair(pOrderInfo->lPrice, stPriceOrder));
	}
	//��������Ͷ�����Ϣ���й���
	//reinterpret_cast��Ҫ�ǽ����ݴ�һ�����͵�ת��Ϊ��һ�����͡���ν��ͨ��Ϊ��������λģʽ�ṩ�ϵͲ�����½��͡�Ҳ����˵�������Զ����ƴ�����ʽ�����½���
	//����Ҳ���ǽ�pTmpOrderָ�����½��Ͳ�ת��Ϊuintptr_t
	UINT uiIndex = EffectiveMod(pTmpOrder->uiOrderIndex, MAX_ORDER_INDEX);
	m_pOrderCache[uiIndex].pOrderAddr = reinterpret_cast<uintptr_t>(pTmpOrder);
	m_pOrderCache[uiIndex].lSubmitOrderID = pTmpOrder->lSubmitOrderID;
	return true;
}

bool CMacthEngine::WriteTransferOrder(const STExechOrderinfo* pTransOrder)
{
	m_iProcCnt++;
	//������д�������������ȥ
	if (m_iProcCnt == 3400)
	{
		long lEndTime = muduo::Timestamp::now().microSecondsSinceEpoch();
		std::cout << "Process 3400 trans all cost time = " << (long)((lEndTime - m_lStartTime)*0.5)<< std::endl;
	}
	int iLen = sizeof(STExechOrderinfo);
	ST_MARKET_HEADER_INFO stMarketInfo;
	stMarketInfo.iLen = iLen;
	stMarketInfo.uiMagicWords = MARKET_MAGIC_WORDS;
	stMarketInfo.wMsgType = 0;
	while (1)
	{
		if (m_pOutputRingBuf->getFreeSize() >= (sizeof(stMarketInfo)+iLen) )
		{
			m_pOutputRingBuf->pushData(&stMarketInfo, sizeof(stMarketInfo));
			m_pOutputRingBuf->pushData(pTransOrder, iLen);
			return true;


		}
	
		
		usleep(1);
		m_iWriteWaitCnt++;
		

	}

	return true;

}

bool CMacthEngine::WriteOrderBook()
{
//	int iLen = sizeof(STExechOrderinfo);
	std::map<UINT, MapPlatformOrderBook>::iterator iter = m_mapMatchExch.begin();
	ST_MARKET_HEADER_INFO stMarketInfo;
	stMarketInfo.uiMagicWords = MARKET_MAGIC_WORDS;
	stMarketInfo.wMsgType = 1;
	for (; iter != m_mapMatchExch.end(); iter++)
	{
		MapPlatformOrderBook::iterator iterOrderBook = iter->second.begin();
		for (; iterOrderBook != iter->second.end(); iterOrderBook++)
		{
			LOG_INFO << "ExchObj = " << iter->first << " Exchange's ID = " << iterOrderBook->first << " 's OrderBook is : ";
			int iDataLen = iterOrderBook->second.mapAskOrderBook.size() * sizeof(STSigOrderBookItem);
			stMarketInfo.iLen = iDataLen;
			stMarketInfo.wTransType = 1;
			STSigOrderBookItem stSigOrder;
			//дAsk OrderBook
			while (1)
			{
				if (iDataLen < 1)
				{
					break;
				}
				if (m_pOutputRingBuf->getFreeSize() >= sizeof(ST_MARKET_HEADER_INFO) + iDataLen)
				{
					m_pOutputRingBuf->pushData(&stMarketInfo, sizeof(ST_MARKET_HEADER_INFO));
					MapOrderBook::reverse_iterator re_ask_iter = iterOrderBook->second.mapAskOrderBook.rbegin();
					for (; re_ask_iter != iterOrderBook->second.mapAskOrderBook.rend(); re_ask_iter++)
					{
						stSigOrder.lPrice = re_ask_iter->first;
						stSigOrder.fNumber = re_ask_iter->second.fTotalNumber;
						m_pOutputRingBuf->pushData(&stSigOrder, sizeof(STSigOrderBookItem));
					}
					break;
				}
				usleep(2);
				continue;
			}
			iDataLen = iterOrderBook->second.mapBidOrderBook.size() * sizeof(STSigOrderBookItem);
			stMarketInfo.iLen = iDataLen;
			stMarketInfo.wTransType = 0;
			while (1)
			{
				if (iDataLen < 1)
				{
					break;
				}
				if (m_pOutputRingBuf->getFreeSize() >= sizeof(ST_MARKET_HEADER_INFO) + iDataLen)
				{
					m_pOutputRingBuf->pushData(&stMarketInfo, sizeof(ST_MARKET_HEADER_INFO));
					MapOrderBook::reverse_iterator re_bid_iter = iterOrderBook->second.mapBidOrderBook.rbegin();
					for (; re_bid_iter != iterOrderBook->second.mapBidOrderBook.rend(); re_bid_iter++)
					{
						stSigOrder.lPrice = re_bid_iter->first;
						stSigOrder.fNumber = re_bid_iter->second.fTotalNumber;
						m_pOutputRingBuf->pushData(&stSigOrder, sizeof(STSigOrderBookItem));
					}
					break;
				}
				usleep(2);
				continue;
			}
		}
	}
	return true;

}

bool CMacthEngine::ProcMarketOrder(STSubmitOrderInfo* pOrderInfo, STOrderBookInfo* pOrderBookInfo)
{
	if (pOrderInfo->ucTransType == EN_ORDER_BID)
		return ProcMarketBidOrder(pOrderInfo, &(pOrderBookInfo->mapAskOrderBook));
	else
		return ProcMarketAskOrder(pOrderInfo, &(pOrderBookInfo->mapBidOrderBook));
}
//�����г��򵥣�����������б��д�С������д���
bool CMacthEngine::ProcMarketBidOrder(STSubmitOrderInfo* pSubmitOrder, MapOrderBook* pOrderBook)
{
	//����г��������б����д������ݣ��򽲸��г��������뵽�б���ȥ�ȴ��ŶӴ���
	if (m_listMarketBidOrder.size() > 0)
	{
		//���ڴ�ص��������ڴ�ռ�
		STSubmitOrderInfo* pMarketOrder = m_memPool.allocate(1);
		memcpy(pMarketOrder, pSubmitOrder, sizeof(STSubmitOrderInfo));
		m_listMarketBidOrder.push_back(pMarketOrder);
		return true;
	}
	//��ʼ���к�ί�ж������гɽ�
	MapOrderBook::iterator iter = (*pOrderBook).begin();
	bool bIsRet = false;
	while (iter != (*pOrderBook).end())
	{
		std::multimap<long, STSubmitOrderInfo*>::iterator iterTimeOrder = (iter->second).mulmapOrder.begin();
		while (iterTimeOrder != (iter->second).mulmapOrder.end())
		{
			//��ִ�е����˵���г��������Ѿ���ȫ�ɽ����ˣ����Ҹü۸���Ȼ����ί�е�
			if (bIsRet)
				return true;
			//����õ��Ѿ��������ˣ��������õ��������ͷ��ڴ�
			if (iterTimeOrder->second->ucTransStatus == EN_TRANS_STATUS_CPL_CANCEL || iterTimeOrder->second->ucTransStatus == EN_TRANS_STATUS_PART_CANCEL ||
				iterTimeOrder->second->ucTransStatus == EN_TRANS_STATUS_CPL_TRANS)
			{
				//���ո�ί�ж���
				//				UINT uiIndex = EffectiveMod(iterTimeOrder->second->uiOrderIndex, MAX_ORDER_INDEX);
				// 				if (0 == m_pOrderCache[uiIndex].lSubmitOrderID || m_pOrderCache[uiIndex].lSubmitOrderID == iterTimeOrder->second->lSubmitOrderID)
				// 					m_pOrderCache[uiIndex].pOrderAddr = NULL;
				if (iterTimeOrder->second->ucTransStatus == EN_TRANS_STATUS_CPL_TRANS)
					LOG_ERROR << "exchange disorder, AskOrder(" << iterTimeOrder->second->lSubmitOrderID << ") should be erase before.";

				(iter->second).fTotalNumber -= iterTimeOrder->second->fNumber;
				m_memPool.destroy(iterTimeOrder->second);
				m_memPool.deallocate(iterTimeOrder->second);
				iterTimeOrder = (iter->second).mulmapOrder.erase(iterTimeOrder);
				continue;
			}
			STExechOrderinfo stExecOrder;
			stExecOrder.lExchID = ++m_ulTransID;
			stExecOrder.lPrice = iterTimeOrder->second->lPrice;
			stExecOrder.lAskOrderID = iterTimeOrder->second->lSubmitOrderID;
			stExecOrder.lBidOrderID = pSubmitOrder->lSubmitOrderID;

			stExecOrder.ucExchType = 1;
			//����г�������С��ί�е���������������Ӧ��ί�е����޸�ʣ�����������޸ĳɽ����λ
			//Ȼ���ͳɽ����������������ֱ�ӷ���
			if (pSubmitOrder->fNumber < iterTimeOrder->second->fNumber)
			{
				stExecOrder.fNumber = pSubmitOrder->fNumber;
				(iter->second).fTotalNumber -= pSubmitOrder->fNumber;
				iterTimeOrder->second->fNumber -= pSubmitOrder->fNumber;
				iterTimeOrder->second->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
				WriteTransferOrder(&stExecOrder);
				return true;
			}
			else
			{
				(iter->second).fTotalNumber -= iterTimeOrder->second->fNumber;
				if (IsFloatEqual(pSubmitOrder->fNumber, iterTimeOrder->second->fNumber))
					bIsRet = true;
				else
				{
					pSubmitOrder->fNumber -= iterTimeOrder->second->fNumber;
					pSubmitOrder->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
				}
				stExecOrder.fNumber = iterTimeOrder->second->fNumber;
				WriteTransferOrder(&stExecOrder);
				//���ո�ί�ж���
				UINT uiIndex = EffectiveMod(iterTimeOrder->second->uiOrderIndex, MAX_ORDER_INDEX);
				if (0 == m_pOrderCache[uiIndex].lSubmitOrderID || m_pOrderCache[uiIndex].lSubmitOrderID == iterTimeOrder->second->lSubmitOrderID)
					m_pOrderCache[uiIndex].pOrderAddr = 0;

				m_memPool.destroy(iterTimeOrder->second);
				m_memPool.deallocate(iterTimeOrder->second);
				iterTimeOrder = (iter->second).mulmapOrder.erase(iterTimeOrder);
			}
		}
		//�������bIsRet�ǿ��ǵ������г��������պðѸü۸�������һ��ί�ж����ɽ��˵Ļ���
		//����Ҫ����mulmapɾ�����ٽ��з���
		iter = (*pOrderBook).erase(iter);
		if (bIsRet)
			return true;

	}
	//��ִ�е����˵�����г����Ѿ�ȫ���Ե��˵�ǰȫ�����г�ί�����������һ���ʣ����򵥣�����Ҫ������뵽�г������б���
	STSubmitOrderInfo* pTmpOrder = m_memPool.allocate(1);
	memcpy(pTmpOrder, pSubmitOrder, sizeof(STSubmitOrderInfo));
	m_listMarketBidOrder.push_back(pTmpOrder);
	return true;
}


//�����г�����
bool CMacthEngine::ProcMarketAskOrder(STSubmitOrderInfo* pSubmitOrder, MapOrderBook* pOrderBook)
{
	//����г��������б����д������ݣ��򽲸��г��������뵽�б���ȥ�ȴ��ŶӴ���
	if (m_listMarketAskOrder.size() > 0)
	{
		//���ڴ�ص��������ڴ�ռ�
		STSubmitOrderInfo* pMarketOrder = m_memPool.allocate(1);
		memcpy(pMarketOrder, pSubmitOrder, sizeof(STSubmitOrderInfo));
		m_listMarketAskOrder.push_back(pMarketOrder);
		return true;
	}
	bool bIsRet = false;
	MapOrderBook::reverse_iterator iter = (*pOrderBook).rbegin();

	while (iter != (*pOrderBook).rend())
	{
		std::multimap<long, STSubmitOrderInfo*>::iterator iterTimeOrder = (iter->second).mulmapOrder.begin();
		while (iterTimeOrder != (iter->second).mulmapOrder.end())
		{
			//��ִ�е����˵���г��������Ѿ���ȫ�ɽ����ˣ����Ҹü۸���Ȼ����ί�е�
			if (bIsRet)
				return true;
			//����õ��Ѿ��������ˣ��������õ��������ͷ��ڴ�
			if (iterTimeOrder->second->ucTransStatus == EN_TRANS_STATUS_CPL_CANCEL || iterTimeOrder->second->ucTransStatus == EN_TRANS_STATUS_PART_CANCEL ||
				iterTimeOrder->second->ucTransStatus == EN_TRANS_STATUS_CPL_TRANS)
			{
				//���ո�ί�ж���
//				UINT uiIndex = EffectiveMod(iterTimeOrder->second->uiOrderIndex, MAX_ORDER_INDEX);
// 				if (0 == m_pOrderCache[uiIndex].lSubmitOrderID || m_pOrderCache[uiIndex].lSubmitOrderID == iterTimeOrder->second->lSubmitOrderID)
// 					m_pOrderCache[uiIndex].pOrderAddr = NULL;
				if (iterTimeOrder->second->ucTransStatus == EN_TRANS_STATUS_CPL_TRANS)
					LOG_ERROR << "exchange disorder, BidOrder(" << iterTimeOrder->second->lSubmitOrderID << ") should be erase before.";

				(iter->second).fTotalNumber -= iterTimeOrder->second->fNumber;
				m_memPool.destroy(iterTimeOrder->second);
				m_memPool.deallocate(iterTimeOrder->second);
				iterTimeOrder = (iter->second).mulmapOrder.erase(iterTimeOrder);
				continue;
			}
			STExechOrderinfo stExecOrder;
			stExecOrder.lExchID = ++m_ulTransID;
			stExecOrder.lPrice = iterTimeOrder->second->lPrice;
			stExecOrder.lAskOrderID = pSubmitOrder->lSubmitOrderID;
			stExecOrder.lBidOrderID = iterTimeOrder->second->lSubmitOrderID;
			stExecOrder.ucExchType = 1;
			//����г�������С��ί�е���������������Ӧ��ί�е����޸�ʣ�����������޸ĳɽ����λ
			//Ȼ���ͳɽ����������������ֱ�ӷ���
			if (pSubmitOrder->fNumber < iterTimeOrder->second->fNumber)
			{
				(iter->second).fTotalNumber -= pSubmitOrder->fNumber;
				stExecOrder.fNumber = pSubmitOrder->fNumber;
				iterTimeOrder->second->fNumber -= pSubmitOrder->fNumber;
				iterTimeOrder->second->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
				WriteTransferOrder(&stExecOrder);
				return true;
			}
			else
			{
				(iter->second).fTotalNumber -= iterTimeOrder->second->fNumber;
				if (IsFloatEqual(pSubmitOrder->fNumber, iterTimeOrder->second->fNumber))
					bIsRet = true;
				else
				{
					pSubmitOrder->fNumber -= iterTimeOrder->second->fNumber;
					pSubmitOrder->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
				}

				stExecOrder.fNumber = iterTimeOrder->second->fNumber;
				WriteTransferOrder(&stExecOrder);
				//���ո�ί�ж���
				UINT uiIndex = EffectiveMod(iterTimeOrder->second->uiOrderIndex, MAX_ORDER_INDEX);
				if (0 == m_pOrderCache[uiIndex].lSubmitOrderID || m_pOrderCache[uiIndex].lSubmitOrderID == iterTimeOrder->second->lSubmitOrderID)
					m_pOrderCache[uiIndex].pOrderAddr = 0;
				
				m_memPool.destroy(iterTimeOrder->second);
				m_memPool.deallocate(iterTimeOrder->second);
				iterTimeOrder = (iter->second).mulmapOrder.erase(iterTimeOrder);
			}
		}
		//�������bIsRet�ǿ��ǵ������г��������պðѸü۸�������һ��ί�ж����ɽ��˵Ļ���
		//����Ҫ����mulmapɾ�����ٽ��з���
		iter = MapOrderBook::reverse_iterator((*pOrderBook).erase((++iter).base()));
		if (bIsRet)
			return true;

	}
	//��ִ�е����˵�����г������Ѿ�ȫ���Ե��˵�ǰȫ�����г�ί���򵥣�����Ҫ������뵽�г������б���
	STSubmitOrderInfo* pTmpOrder = m_memPool.allocate(1);
	memcpy(pTmpOrder, pSubmitOrder, sizeof(STSubmitOrderInfo));
	m_listMarketAskOrder.push_back(pTmpOrder);
	return true;

}

bool CMacthEngine::CancelSubmitOrder(const STSubmitOrderInfo* pOrderInfo, STOrderBookInfo* pOrderBookInfo)
{
	UINT uiIndex = EffectiveMod(pOrderInfo->uiOrderIndex, MAX_ORDER_INDEX);
	//�������0������Ϊ�ǳ�ʼ��״̬���������տ�ʼ������ʱ�򣬿϶������ж������г���
	//����0ʱ�򣬷�Ϊ2�������Ҳ�������˶����ͱ��ȴ����г������ɽ��˻����ǳ�����Ϊĳ��ԭ������֮��Ҫ�ӳ־û������лָ����ݵ�������
	//���ڻָ�������ʱ�򣬻�дOrderCache����ʱ�������0���ʹ���������û�иö�����Ҳ���Ǳ�ʾ�Ѿ��ɽ��ˣ����Կ���ֱ�ӷ������账��
	if (m_pOrderCache[uiIndex].lSubmitOrderID == 0)
	{
		return true;
	}
	else if (m_pOrderCache[uiIndex].lSubmitOrderID == pOrderInfo->lSubmitOrderID)
	{
		if (m_pOrderCache[uiIndex].pOrderAddr > 0)
		{
			STSubmitOrderInfo* pPreOrder = reinterpret_cast<STSubmitOrderInfo*>(m_pOrderCache[uiIndex].pOrderAddr);
			STExechOrderinfo stExecOrder;
			stExecOrder.lExchID = ++m_ulTransID;
			stExecOrder.lPrice = pPreOrder->lPrice;
			stExecOrder.fNumber = pPreOrder->fNumber;

			BYTE ucTransStatus = pPreOrder->ucTransStatus;
			if (ucTransStatus == EN_TRANS_STATUS_SUBMIT)
				pPreOrder->ucTransStatus = EN_TRANS_STATUS_CPL_CANCEL;
			else if (ucTransStatus == EN_TRANS_STATUS_PART_TRANS)
				pPreOrder->ucTransStatus = EN_TRANS_STATUS_PART_CANCEL;
			//�������ȫ���ɽ���ȫ���������߲��ֳ���״̬�Ļ�����ʱ�ö�������Ӧʣ�������Ӧ��Ϊ0����������ô����Ϊ�˽�֮ǰ�ĳɽ���Ϣ�͸ôεĳ�����Ϣ���ֿ����Ա��ں�����ϳɽ�������ö���������ʱ��
			//���������ܹ���ȥ��ȷ������
			else
				pPreOrder->fNumber = 0;
			m_pOrderCache[uiIndex].pOrderAddr = 0;
	
			if (pPreOrder->ucTransType == EN_ORDER_BID)
				stExecOrder.lBidOrderID = pPreOrder->lSubmitOrderID;
			else
				stExecOrder.lAskOrderID = pPreOrder->lSubmitOrderID;
			stExecOrder.ucExchType = 0;
			WriteTransferOrder(&stExecOrder);

		}

		return true;
	}
	//�������ȣ���˵��������ű�����ˣ�����Ҫ��OrderBook��ȥѰ��,�ҵ����������ȫ���ɽ������Ѿ����������
	//��ֱ�ӳ����õ�����mulmap��ɾ���õ㣬�����ڸü۸�����Ӧ���������м�ȥ�������ĵ��е�����
	else
	{
		MapOrderBook* pMapOrderBook = (pOrderInfo->ucTransType == EN_ORDER_BID) ? &(pOrderBookInfo->mapBidOrderBook) : &(pOrderBookInfo->mapAskOrderBook);
		MapOrderBook::iterator iter = (*pMapOrderBook).find(pOrderInfo->lPrice);
		if (iter != (*pMapOrderBook).end())
		{
			typedef std::multimap<long, STSubmitOrderInfo*>::iterator TimeOrderIter;
			//	TimeOrderIter iterTimeOrder = (iter->second).find(pOrderInfo->lSubmitTime);

			std::pair<TimeOrderIter, TimeOrderIter> range = (iter->second).mulmapOrder.equal_range(pOrderInfo->lSubmitTime);
			while (range.first != range.second)
			{
				//������ҵ�������г���������������
				if (range.first->second->lSubmitOrderID == pOrderInfo->lSubmitOrderID)
				{
					//����Ǵ���ί��״̬����״̬��Ϊȫ���ɽ�
					bool bIsNeedCancel = false;
					if (range.first->second->ucTransStatus == EN_TRANS_STATUS_SUBMIT)
					{
						(iter->second).fTotalNumber -= range.first->second->fNumber;
						range.first->second->ucTransStatus = EN_TRANS_STATUS_CPL_CANCEL;
						bIsNeedCancel = true;
					}
					//������Ѿ����ֳɽ�����״̬��Ϊ���ֳ���
					else if (range.first->second->ucTransStatus == EN_TRANS_STATUS_PART_TRANS)
					{
						(iter->second).fTotalNumber -= range.first->second->fNumber;
						range.first->second->ucTransStatus = EN_TRANS_STATUS_PART_CANCEL;
						bIsNeedCancel = true;
					}
					//�����ȫ���ɽ������ǳ���״̬����������г���
					else
						bIsNeedCancel = false;
					if (bIsNeedCancel)
					{
						STExechOrderinfo stExecOrder;
						stExecOrder.lExchID = ++m_ulTransID;
						stExecOrder.lPrice = range.first->second->lPrice;
						stExecOrder.fNumber = range.first->second->fNumber;
						if (range.first->second->ucTransType == EN_ORDER_BID)
							stExecOrder.lBidOrderID = range.first->second->lSubmitOrderID;
						else
							stExecOrder.lAskOrderID = range.first->second->lSubmitOrderID;
						stExecOrder.ucExchType = 0;
						WriteTransferOrder(&stExecOrder);
					}
					//��mulmap�н���ɾ��
					range.first = (iter->second).mulmapOrder.erase(range.first);
					return true;

				}
				else
					range.first++;
			}

		}
		return true;
	}

}

bool CMacthEngine::AddSubmitOrder(STSubmitOrderInfo* pSubmitOrder)
{
	STOrderBookInfo* pOrderBook = NULL;
	std::map<UINT, MapPlatformOrderBook>::iterator iter = m_mapMatchExch.find(pSubmitOrder->uiExchObjID);
	MapPlatformOrderBook::iterator iterPlatOrder;
	if (iter == m_mapMatchExch.end())
	{
		if (pSubmitOrder->ucIsCancelOrder == 1)
			return false;
		STOrderBookInfo stOrderBook;
		MapPlatformOrderBook mapPlatOrderBook;
		mapPlatOrderBook.clear();
		mapPlatOrderBook[pSubmitOrder->uiPlatformID] = stOrderBook;
		m_mapMatchExch[pSubmitOrder->uiExchObjID] = mapPlatOrderBook;
		iter = m_mapMatchExch.find(pSubmitOrder->uiExchObjID);
		iterPlatOrder = iter->second.find(pSubmitOrder->uiPlatformID);
	}
	else
	{
		iterPlatOrder = iter->second.find(pSubmitOrder->uiPlatformID);
		if (iterPlatOrder == iter->second.end())
		{
			if (pSubmitOrder->ucIsCancelOrder == 1)
				return false;
			STOrderBookInfo stOrderBook;
			iter->second.insert(std::make_pair(pSubmitOrder->uiPlatformID, stOrderBook));
			iterPlatOrder = iter->second.find(pSubmitOrder->uiPlatformID);
		}
	}
	pOrderBook = &(iterPlatOrder->second);

	if (pSubmitOrder->ucIsCancelOrder == 1)
	 return	CancelSubmitOrder(pSubmitOrder, pOrderBook);
	else
	{
		if (1 == pSubmitOrder->ucOrderType)
		   return ProcMarketOrder(pSubmitOrder, pOrderBook);
		else
		   return AddAskOrBidOrder(pSubmitOrder, pOrderBook);
	}

}
bool CMacthEngine::MatchExchangeObj(STOrderBookInfo& stOrderBook)
{
	//////////////////////////////////////////////////////////////////////////
// 	MapOrderBook::reverse_iterator  rev_iter_bid_test = stOrderBook.mapAskOrderBook.rbegin();
// 	for (; rev_iter_bid_test != stOrderBook.mapAskOrderBook.rend(); rev_iter_bid_test++)
// 		LOG_INFO << "test Ask Order Book:" << (1.0*rev_iter_bid_test->first) / FLOAT_PRICE_TO_LONG << " " << rev_iter_bid_test->second.fTotalNumber;
// 
// 	for (MapOrderBook::iterator iter_test = stOrderBook.mapBidOrderBook.begin(); iter_test != stOrderBook.mapBidOrderBook.end(); iter_test++)
// 	{
// 		LOG_INFO << "test Bid Order Book:" << (1.0*iter_test->first) / FLOAT_PRICE_TO_LONG << " " << iter_test->second.fTotalNumber;
// 	}

	
	//////////////////////////////////////////////////////////////////////////
	MapOrderBook::reverse_iterator  rev_iter_bid = stOrderBook.mapBidOrderBook.rbegin();
	typedef std::multimap<long, STSubmitOrderInfo*>::iterator timeorder_iter;
	if (stOrderBook.mapAskOrderBook.size() < 1 || stOrderBook.mapBidOrderBook.size() < 1)
	{
		LOG_DEBUG << "there is no order in ask_order_book or bid_order_book";
		return true;
	}	

	MapOrderBook::iterator iter_ask = stOrderBook.mapAskOrderBook.begin();
	timeorder_iter iter_time_ask = (iter_ask->second).mulmapOrder.begin();
	STExechOrderinfo stExecOrder;
	//���������
	while (rev_iter_bid != stOrderBook.mapBidOrderBook.rend())
	{
		if (iter_ask->first > rev_iter_bid->first)
		{
			LOG_DEBUG << "ask price is greatter than bid price";
			return true;
		}
		//��ȡ�ü۸��µ�������
        timeorder_iter iter_time_bid = (rev_iter_bid->second).mulmapOrder.begin();

		while (iter_time_bid != (rev_iter_bid->second).mulmapOrder.end())
		{
			if (rev_iter_bid->first < iter_ask->first)
				return true;
			//�����ü۸��µ���������
			while (iter_time_ask != (iter_ask->second).mulmapOrder.end())
			{     
				memset(&stExecOrder, 0, sizeof(STExechOrderinfo));
				stExecOrder.lExchID = ++m_ulTransID;
				//�ɽ������򵥵���߼�Ϊ��
				stExecOrder.lPrice = iter_time_bid ->second->lPrice;
				stExecOrder.lAskOrderID = iter_time_ask->second->lSubmitOrderID;
				stExecOrder.lBidOrderID = iter_time_bid->second->lSubmitOrderID;
			 
				stExecOrder.ucExchType = 1;
				//���������С�ڵ����������򽫸���ȫ���ɽ�
 				if ((iter_time_bid->second->fNumber < iter_time_ask->second->fNumber) || IsFloatEqual(iter_time_bid->second->fNumber, iter_time_ask->second->fNumber))
				{
					stExecOrder.fNumber = iter_time_bid->second->fNumber;
					WriteTransferOrder(&stExecOrder);
					//�޸���������������Ϣ
					(rev_iter_bid->second).fTotalNumber -= iter_time_bid->second->fNumber;
	     			(iter_ask->second).fTotalNumber -= iter_time_bid->second->fNumber;

					iter_time_bid->second->ucTransStatus = EN_TRANS_STATUS_CPL_TRANS;
//					iter_time_ask->second->fNumber -= iter_time_bid->second->fNumber;
					iter_time_ask->second->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
					UINT uiIndex = EffectiveMod(iter_time_bid->second->uiOrderIndex, MAX_ORDER_INDEX);
					if (0 == m_pOrderCache[uiIndex].lSubmitOrderID)
						LOG_ERROR << "Order Cache's submit order id is null. Org SubmitOrdrID =" << iter_time_bid->second->lSubmitOrderID << "OrderIndex = " << iter_time_bid->second->uiOrderIndex;
					//����OrderCache�еı��Ϊ�ѳɽ�
					else if (m_pOrderCache[uiIndex].lSubmitOrderID == iter_time_bid->second->lSubmitOrderID)
						m_pOrderCache[uiIndex].pOrderAddr = 0;
			
                    //�����ȵĻ�����ͬʱҲҪ��������������Ϣ
					if (IsFloatEqual(iter_time_bid->second->fNumber, iter_time_ask->second->fNumber))
					{
						iter_time_ask->second->fNumber -= iter_time_bid->second->fNumber;
						iter_time_ask->second->ucTransStatus = EN_TRANS_STATUS_CPL_TRANS;
						uiIndex = EffectiveMod(iter_time_ask->second->uiOrderIndex, MAX_ORDER_INDEX);
						if (0 == m_pOrderCache[uiIndex].lSubmitOrderID)
							LOG_ERROR << "Order Cache's submit order id is null. Org AskSubmitOrdrID =" << iter_time_ask->second->lSubmitOrderID << "OrderIndex = " << iter_time_ask->second->uiOrderIndex;
						//����OrderCache�еı��Ϊ�ѳɽ�
						else if (m_pOrderCache[uiIndex].lSubmitOrderID == iter_time_ask->second->lSubmitOrderID)
							m_pOrderCache[uiIndex].pOrderAddr = 0;
						//�ͷ��ڴ�
						m_memPool.destroy(iter_time_ask->second);
						m_memPool.deallocate(iter_time_ask->second);
						iter_time_ask = (iter_ask->second).mulmapOrder.erase(iter_time_ask);
					}
					else
					{
						iter_time_ask->second->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
						iter_time_ask->second->fNumber -= iter_time_bid->second->fNumber;
					}
			
					//�ͷ��򵥵��ڴ�������Ϣ
					m_memPool.destroy(iter_time_bid->second);
					m_memPool.deallocate(iter_time_bid->second);
					iter_time_bid = (rev_iter_bid->second).mulmapOrder.erase(iter_time_bid);
					//����������Ķ�������򵥱���ȫ���ף���������������ѭ������������һ����
					break;
				}
				else//����򵥵�������������
				{
					stExecOrder.fNumber = iter_time_ask->second->fNumber;
					WriteTransferOrder(&stExecOrder);
					//�޸���������������Ϣ
					(rev_iter_bid->second).fTotalNumber -= iter_time_ask->second->fNumber;
					(iter_ask->second).fTotalNumber -= iter_time_ask->second->fNumber;

					iter_time_bid->second->ucTransStatus = EN_TRANS_STATUS_PART_TRANS;
					iter_time_bid->second->fNumber -= iter_time_ask->second->fNumber;
					//��������������Ϣ
					iter_time_ask->second->ucTransStatus = EN_TRANS_STATUS_CPL_TRANS;
					UINT uiIndex = EffectiveMod(iter_time_ask->second->uiOrderIndex, MAX_ORDER_INDEX);
					if (0 == m_pOrderCache[uiIndex].lSubmitOrderID)
						LOG_ERROR << "Order Cache's submit order id is null. Org AskSubmitOrdrID =" << iter_time_ask->second->lSubmitOrderID << "OrderIndex = " << iter_time_ask->second->uiOrderIndex;
					//����OrderCache�еı��Ϊ�ѳɽ�
					else if (m_pOrderCache[uiIndex].lSubmitOrderID == iter_time_ask->second->lSubmitOrderID)
						m_pOrderCache[uiIndex].pOrderAddr = 0;
					//�ͷ��ڴ�
					m_memPool.destroy(iter_time_ask->second);
					m_memPool.deallocate(iter_time_ask->second);
					iter_time_ask = (iter_ask->second).mulmapOrder.erase(iter_time_ask);
				}
			
			}
			//��������иü۸�������򵥶��ѳɽ�����ɾ����ǰ�۸񣬻�ȡ��һ���۸��������Ϣ
			if (iter_time_ask == (iter_ask->second).mulmapOrder.end())
			{
				iter_ask = stOrderBook.mapAskOrderBook.erase(iter_ask);
				//�������ȫ�����ɽ��ˣ����Ƴ�
				if (iter_ask == stOrderBook.mapAskOrderBook.end())
				{
					return true;
				}
				iter_time_ask = (iter_ask->second).mulmapOrder.begin();
			}
		}
		//�����е��ⲽ��˵���ü۸�����Ѿ�ȫ�������ף���Ҫ��ȡ��һ���۸����
		rev_iter_bid = MapOrderBook::reverse_iterator(stOrderBook.mapBidOrderBook.erase((++rev_iter_bid).base()));

	}
	return true;


}
bool CMacthEngine::StartMatchExchange()
{
	std::map<UINT, MapPlatformOrderBook>::iterator iter = m_mapMatchExch.begin();
	MapPlatformOrderBook::iterator iterPlatorder;
	for (; iter != m_mapMatchExch.end(); iter++)
	{
		for (iterPlatorder = iter->second.begin(); iterPlatorder != iter->second.end(); iterPlatorder++)
		{
			MatchExchangeObj(iterPlatorder->second);
		}
		
	}
	return true;
}

bool CMacthEngine::WriteMarketSnapShot()
{
	//temp delete
	//LOG_INFO << "Current proc transmition number:" << m_iProcCnt << " and write exchange order wait times:"<<m_iWriteWaitCnt;
	m_iProcCnt = 0;
	m_iWriteWaitCnt = 0;
	WriteOrderBook();
	return true;
}

bool CMacthEngine::StartWork()
{
	m_bIsRunning = true;
	if (pthread_create(&m_threadID, NULL, MatchExchangeFunc, this) != 0)
	{
		LOG_FATAL<<"create CMacthEngine thread  failed";
		return false;
	}
	return true;
}

void* CMacthEngine::MatchExchangeFunc(void* pInfo)
{
	CMacthEngine* pMatchExch = (CMacthEngine*)pInfo;
	STSubmitOrderInfo stSubmitOrder;
	int iSubmitOrderLen = sizeof(STSubmitOrderInfo);
	//���С��255,����Ϊ�����׺���
	if (pMatchExch->m_iSetCpuID < 255)
	{
		cpu_set_t cpuSet;
		CPU_ZERO(&cpuSet);
		CPU_SET(pMatchExch->m_iSetCpuID, &cpuSet);
		int iRet = pthread_setaffinity_np(pthread_self(), sizeof(cpuSet), &cpuSet);
		if (iRet != 0)
		{
			LOG_ERROR << "set thread(MacthEngine) affinity failed.error = " << iRet;
			return ((void*)0);
		}
	}

	while (pMatchExch->m_bIsRunning)
	{
		//�鿴�Ƿ��˴�ϳɽ���ʱ��
		if (1 == pMatchExch->GetMatchTimeFlag())
		{
			pMatchExch->StartMatchExchange();
			pMatchExch->SetTimerEvent(EN_TIMER_MATCH, 0);
		}
		if (1 == pMatchExch->GetSnapShotFlag())
		{
			pMatchExch->WriteMarketSnapShot();
			pMatchExch->SetTimerEvent(EN_TIMER_MARKET_SNAPSHOT, 0);
		}
		DWORD dwReadBytes = pMatchExch->m_pInputRingBuf->getUsedSize();
		if (dwReadBytes == 0)//�������ȡ���ˣ�������5΢��
		{
			usleep(5);
			continue;
		}
		//�����ʱ���ֶ�ȡ�����ݲ��Ƕ�����������������������������ò��ֵ�����
		else if (dwReadBytes < iSubmitOrderLen)
		{
			LOG_ERROR << "ReadBytes is not integer multiples of submit order's length , readed bytes =  " << dwReadBytes;
			pMatchExch->m_pInputRingBuf->popData(dwReadBytes);
			continue;
		}
		else
		{
			if (!pMatchExch->m_pInputRingBuf->popData(&stSubmitOrder, iSubmitOrderLen, iSubmitOrderLen))
			{
				continue;
			}
			if (pMatchExch->m_lStartTime == 0)
			{
				pMatchExch->m_lStartTime = muduo::Timestamp::now().microSecondsSinceEpoch();
			}
			pMatchExch->AddSubmitOrder(&stSubmitOrder);
		}

	}
	return ((void*)0);
}
//��ʱ�Ļص�����
void CMacthEngine::SetTimerEvent(int iEvent, int iVal)
{
	muduo::MutexLockGuard mutexLockGuard(m_muteLock);
	switch (iEvent)
	{
	case EN_TIMER_MATCH:
		m_iMatchTimerFlag = iVal;
		break;
	case EN_TIMER_MARKET_SNAPSHOT:
		m_iSnapShotFlag = iVal;
		break;
	default:
		LOG_ERROR << "Unknow timer event val : " << iEvent;
		break;
	}
}