#pragma once
#include <string.h>
#include "XRingBuffer.h"
#include <vector>
//#include <c++\4.8\ext\hash_map>
#include <map>
#include <functional>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>

#define MAX_ORDER_INDEX   8388608 //8*1024*1024
#define MATCH_TIME_INTERVAL 0.01  //ƥ���ʱ����Ϊ10ms
#define MARKET_SNAPSHOT_TIME_INTERVAL 3//�г����յ�������Ϊ3��
#define SERVER_STATUS_TIME_INTERVAL  5
#define FLOAT_PRICE_TO_LONG   10000000 //���۸��float����ת��Ϊlong�͵�ϵ������λ�㹻��֤����
#define MARKET_MAGIC_WORDS    0xFF8899FF
#define MAX_USR_ORDERID_LEN   33
typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef muduo::net::EventLoop   MuduoEventLoop;
typedef muduo::net::EventLoopThread  MuduoEventLoopThread;

enum EN_TRANS_STATUS
{
	EN_TRANS_STATUS_SUBMIT = 0,
	EN_TRANS_STATUS_CPL_TRANS,
	EN_TRANS_STATUS_PART_TRANS,
	EN_TRANS_STATUS_CPL_CANCEL = 4
//	EN_TRANS_STATUS_PART_CANCEL
};

enum EN_TIMER_EVENT
{
	EN_TIMER_MATCH = 0,
	EN_TIMER_MARKET_SNAPSHOT,
	EN_TIMER_SERVER_STATUS

};

enum  EN_ORDER_TYPE
{
	EN_ORDER_BID = 0,
	EN_ORDER_ASK
};

typedef struct ST_SUBMIT_ORDER_INFO
{
	long lSubmitOrderID;    //����ID
	long lSubmitTime;       //�µ�ʱ�䣬��λΪ΢��
	long  lPrice;           //���׼۸�,������Ὣ���׵�����FLOAT_PRICE_TO_LONG����ת��Ϊ
	UINT  uiExchObjID;         //����Ʒ�ִ���
	UINT  uiPlatformID;      //�ͻ������ڵ�ƽ̨ע��ID�����ڱ�ʶ���ĸ�������������
	UINT  uiOrderIndex;     //���ն˷���������ţ�Ϊ˳����������0��ʼ
	long  lNumber;          //��������
	BYTE ucTransType;       //�������ͣ�0 ��ʾ�� 1��ʾ��
	BYTE ucOrderType;       //�������ͣ�0 ��ʾ�޼۶�����1��ʾ�г�����
	BYTE ucTransStatus;     //�ɽ�״̬�� 0����ί�У� 1:ȫ���ɽ� 2�����ֳɽ� 3��ȫ������ 4�����ֳ���
	BYTE ucIsCancelOrder;   //�Ƿ���г������� 0���������� 1������
	char chUsrOrderID[MAX_USR_ORDERID_LEN];
	BYTE chReservse[3];
	ST_SUBMIT_ORDER_INFO()
	{
		memset(this, 0, sizeof(ST_SUBMIT_ORDER_INFO));
	}
	~ST_SUBMIT_ORDER_INFO()
	{
		memset(this, 0, sizeof(ST_SUBMIT_ORDER_INFO));
	}
}STSubmitOrderInfo;


typedef struct ST_EXCHANGE_ORDER_INFO
{
	long lExchID;         //�ɽ����
	long lBidOrderID;     //�򵥱��
	long lAskOrderID;     //�������
	long lPrice;         //�۸�
	long lNumber;         //����
	UINT uiBidUsrID;
	UINT uiAskUsrID;
	UINT uiSymbolID;
	BYTE  ucExchType;     //��������  0:���� 1:�ɽ� 
	char chBidUsrOrderID[MAX_USR_ORDERID_LEN]; //�û�ƽ̨�еĶ���ID
	char chAskUsrOrderID[MAX_USR_ORDERID_LEN];
	char  chReservse[7];
	ST_EXCHANGE_ORDER_INFO()
	{
		memset(this, 0, sizeof(ST_EXCHANGE_ORDER_INFO));
	}
}STExechOrderinfo;



//ĳһ���۸�������Ӧ�Ķ�������
typedef struct ST_PRICE_ORDER_INFO
{
	long lTotalNumber;
	std::multimap<long, STSubmitOrderInfo*> mulmapOrder;  //��Ӧ����ʱ��Ϊ����Ķ���
	ST_PRICE_ORDER_INFO()
	{
		lTotalNumber = 0;
		mulmapOrder.clear();
	}
}STPriceOrderInfo;

typedef std::map<long, STPriceOrderInfo> MapOrderBook;

typedef struct ST_ORDER_BOOK_INFO
{
	MapOrderBook mapAskOrderBook;
	MapOrderBook mapBidOrderBook;
	ST_ORDER_BOOK_INFO()
	{
		mapAskOrderBook.clear();
		mapBidOrderBook.clear();
	}
}STOrderBookInfo;
//���ڹ�������ƽ̨�Ͷ�����
typedef std::map<UINT, STOrderBookInfo> MapPlatformOrderBook;

typedef std::function<void(int, int)> OnTimerCallBack;

typedef struct ST_SIG_ORDER_ITEM_INFO
{
	long lPrice;
	long lNumber; 
	ST_SIG_ORDER_ITEM_INFO()
	{
		lPrice = 0;
		lNumber = 0;
	}


}STSigOrderBookItem;
#pragma pack(4)
typedef struct ST_MARKET_HEADER_INFO
{
	unsigned int uiMagicWords;
	unsigned short usLen;
	unsigned char wMsgType; //0��ʾ�ɽ����ݣ�1��ʾ������
	unsigned char wTransType;//��ʾ�������Ľ������ͣ�0 ��ʾ�� 1��ʾ��
	ST_MARKET_HEADER_INFO()
	{
		memset(this, 0, sizeof(ST_MARKET_HEADER_INFO));
	}


}STMarketHeaderInfo;
#pragma pack()

#define MIN_FLOAT_PRECISE 0.000001
// inline bool IsFloatEqual(float fVal1, float fVal2)
// {
// 	return (fabs(fVal1 - fVal2) < MIN_FLOAT_PRECISE) ? true : false;
// }
// typedef struct ST_PRICE_ORDER_INFO
// {
// 	float fPrice;
// 	//std::vector<XRingBuffer> vtRingBuf;
// 	//mulmapSubmitOrder��һ������ʱ��Ͷ�����map,ʱ��ľ���Ϊ΢��
// 	std::multimap<long, STSubmitOrderInfo> mulmapSubmitOrder;
// 	ST_PRICE_ORDER_INFO()
// 	{
// 		fPrice = 0;
// 		mulmapSubmitOrder.clear();
// 	}
// }STPriceOrderInfo;
#define TAG_INTERVAL_BUF 0xFF8899FF
//#pragma pack(4)
typedef struct ST_INTERVAL_BUF_HEADER
{
	unsigned int uiMagicWords;
	int  ilen;
	unsigned int  uiMsgType;
	unsigned int  uiReserve;
	ST_INTERVAL_BUF_HEADER()
	{
		uiMagicWords = 0;
		uiMsgType = ilen = 0;
		uiReserve = 0;
	}
}STIntervalBufHeader;
//#pragma pack()

enum  EN_INTERVAL_CMD_INFO
{
	EN_INTERVAL_AUTH = 0,
	EN_INTERVAL_SUBMIT_ORDER,
	EN_INTERVAL_CANCEL_ORDER,
	EN_INTERVAL_QUERY_ORDER,
	EN_INTERVAL_MARKET_TRANS_DATA,
	EN_INTERVAL_MARKET_QUOTA_DATA,
	EN_INTERVAL_MARKET_ORDER_BOOK,
	EN_INTERVAL_QUERY_HISTORY_ORDER,

	EN_INTERVAL_AUTH_RESP = 20,
	EN_INTERVAL_SUBMIT_ORDER_RESP,
	EN_INTERVAL_CANCEL_ORDER_RESP,
	EN_INTERVAL_QUERY_ORDER_RESP

};