#pragma once
#include "StockExcDef.h"
//#include <c++\4.8\ext\hash_map>
#include "MemoryPool.h"
#include "XRingBuffer.h"
#include <muduo/base/Mutex.h>
#include <list>
#include <pthread.h>
#define RING_BUF_SIZE 8388608 //8M��
typedef struct ST_ORDER_CACHE_INFO
{
	long  lSubmitOrderID;
	uintptr_t pOrderAddr;
	ST_ORDER_CACHE_INFO()
	{
		lSubmitOrderID = 0;
		pOrderAddr = 0;
	}
	~ST_ORDER_CACHE_INFO()
	{
		lSubmitOrderID = 0;
		pOrderAddr = 0;
	}


}STOrderCache,*LPOrderCache;

class CMacthEngine
{
public:
	CMacthEngine();
	virtual ~CMacthEngine();
	XRingBuffer* GetInputRingBuffer() { return m_pInputRingBuf; }
	XRingBuffer* GetOutputRingBuffer() { return m_pOutputRingBuf; }
	void SetTimerEvent(int iEvent, int iVal);
	static void* MatchExchangeFunc(void* pInfo);
	void ExitWork() { m_bIsRunning = false; pthread_join(m_threadID, NULL); }
	//������������ʵ�ֵĸ�Ч���롣����uiMod������2��������
	inline UINT EffectiveMod(UINT uiParam, UINT uiMod) { return uiParam&(uiMod - 1); }
	inline int GetMatchTimeFlag() { return m_iMatchTimerFlag; }
	inline int GetSnapShotFlag() { return m_iSnapShotFlag; }
	void SetRunCpu(int iCpuID) { m_iSetCpuID = iCpuID; }
	bool StartWork();

protected:
	bool AddSubmitOrder(STSubmitOrderInfo* pSubmitOrder);
	bool AddAskOrBidOrder(STSubmitOrderInfo* pOrderInfo, STOrderBookInfo* pOrderBookInfo);
	bool CancelSubmitOrder(const STSubmitOrderInfo* pOrderInfo, STOrderBookInfo* pOrderBookInfo);
	bool ProcMarketOrder(STSubmitOrderInfo* pOrderInfo, STOrderBookInfo* pOrderBookInfo);
	bool ProcMarketBidOrder(STSubmitOrderInfo* pSubmitOrder, MapOrderBook* pOrderBook);
	bool ProcMarketAskOrder(STSubmitOrderInfo* pSubmitOrder, MapOrderBook* pOrderBook);
	bool WriteTransferOrder(const STExechOrderinfo* pTransOrder);
	bool StartMatchExchange(); //��ʼ���д�ϳɽ�
	bool WriteMarketSnapShot();
	bool MatchExchangeObj(STOrderBookInfo& stOrderBook);
	bool WriteOrderBook();
protected:
	//����������Ҷԣ�������Ʒ�� ��Ҳ����༸ʮ�֣�������Ҳ��û�б�Ҫ��hash_map
//	std::map<UINT, STOrderBookInfo> m_mapMatchExch; //����������
	std::map<UINT, MapPlatformOrderBook> m_mapMatchExch; //����������
	LPOrderCache m_pOrderCache;
	bool m_bIsRunning;
	XRingBuffer* m_pInputRingBuf;//XRingBuffer������һ��һд��ģ��Ƿ��̰߳�ȫ��
	XRingBuffer* m_pOutputRingBuf;
	int m_iMatchTimerFlag;  //1����ʱ�䵽�˴����� ����ֵ������û�д���
	int m_iSnapShotFlag;
	mutable muduo::MutexLock m_muteLock;
	MemoryPool<STSubmitOrderInfo> m_memPool; //����������ڴ��
	STSubmitOrderInfo*   m_pFirstOrder;
//	STSubmitOrderInfo*   m_pRemAskOrder;     //��������û�д������������Ҳ����˵һ�����������е��򵥶��������ʣ��
//	STSubmitOrderInfo*   m_pRemBidOrder;     //��������û�д�������򵥣�Ҳ����˵һ���򵥰����е��������������ʣ��
	unsigned long   m_ulTransID;            //����ID��˳������
	std::list<STSubmitOrderInfo*> m_listMarketBidOrder;
	std::list<STSubmitOrderInfo*> m_listMarketAskOrder;
	int m_iProcCnt;   //ͳ��ÿ�봦��Ľ�����
	int m_iWriteWaitCnt;//ͳ�������ʱ���������ݶ��������еĵȴ����Դ���
	int m_iSetCpuID;
	pthread_t m_threadID;
	long m_lStartTime;
	


};

