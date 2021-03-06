/*************************************************************************
	> File Name: define.h
	> Author: xyz
	> Mail: xiao13149920@foxmail.com 
	> Created Time: Fri 03 Feb 2017 11:33:28 AM CST
 ************************************************************************/
#ifndef SOLUTIONGATEWAY_DEFINE_H_
#define SOLUTIONGATEWAY_DEFINE_H_

#include<uv.h>
#include<chrono>

#include"xlogger.h"
#include <chrono>

// for uv_tcp connection
#define SOLUTIONGATEWAY_BACKLOG	128

// for SolutionGateway xlogger
#define SOLUTIONGATEWAY_LOGGER		"SolutionGateway"
//#define SOLUTIONGATEWAY_LOGGER_DIR	"/home/leaker/tmp/logger/solutiongateway"
#define SOLUTIONGATEWAY_LOGGER_DIR	"./tmp/logger/SolutionGateway"

// for Position Management xlogger
#define POSITIONMANAGEME_LOGGER		"PositionManagement"
//#define SOLUTIONGATEWAY_LOGGER_DIR	"/home/leaker/tmp/logger/PostionManagement"
#define POSITIONMANAGEME_LOGGER_DIR	"./tmp/logger/PositionManagement"


//#define SOLUTIONGATEWAY_REQUEST_ID_LEN	16
#define SOLUTIONGATEWAY_REQUEST_ID_LEN	33
#define REQUEST_ID_LEN	33
#define SESSION_ID_LEN	33
#define MAX_HTTP_HEADERS 20

#define MODEL_NAME_LEN 16

#if defined(KEEP_ALIVE_TEST)
#define SOLUTIONGATEWAY_PORT	5002
#define RESPONSE \
	"Connection: Keep-Alive\r\n" \
	"Content-Length: "
#else
#define SOLUTIONGATEWAY_PORT	5002
#define RESPONSE \
	"Content-Length: "
#endif

#define SOLUTIONGATEWAY_CHANNEL_SIZE	5

//for CM
#define SOLUTIONGATEWAY_PUBLISH_LOGIN_NAME	"LOGIN"
#define	SOLUTIONGATEWAY_PUBLISH_CMTRECONNECT_NAME "CMTRECONNECT"
#define SOLUTIONGATEWAY_PUBLISH_LOGOUT_NAME	"LOGOUT"
#define SOLUTIONGATEWAY_PUBLISH_CHANGEPASSWORD_NAME "CHANGEPASSWORD"        
#define SOLUTIONGATEWAY_PUBLISH_CHANGEBALANCE_NAME "CHANGEBALANCE"        
#define SOLUTIONGATEWAY_PUBLISH_UPDATETRADER_NAME "UPDATETRADER"        
#define SOLUTIONGATEWAY_PUBLISH_GETMANAGERS_NAME "GETMANAGERS"        
#define SOLUTIONGATEWAY_PUBLISH_GETTRADERS_NAME "GETTRADERS"        
#define SOLUTIONGATEWAY_PUBLISH_INSERTUPDATEMANAGERRIGHTS_NAME "INSERTUPDATEMANAGERRIGHTS"        
#define SOLUTIONGATEWAY_PUBLISH_GETMANAGERACCESS_NAME "GETMANAGERACCESS"        
#define SOLUTIONGATEWAY_PUBLISH_USERDELETECHECKREQ_NAME "USERDELETECHECKREQ"        
#define SOLUTIONGATEWAY_PUBLISH_USERDELETEREQ_NAME "USERDELETEREQ"  
#define SOLUTIONGATEWAY_PUBLISH_CREATETRADER_NAME "CREATETRADER" 
#define SOLUTIONGATEWAY_PUBLISH_GETONLINETRADER_NAME "GETONLINETRADER" 	

#define SOLUTIONGATEWAY_PUBLISH_DISABLETRADER_NAME "DISABLETRADER"
#define SOLUTIONGATEWAY_PUBLISH_KICKOUTTRADER_NAME "KICKOUTTRADER"
#define SOLUTIONGATEWAY_PUBLISH_GETTRADERBYTRADERID_NAME "GETTRADERBYTRADERID"
#define SOLUTIONGATEWAY_PUBLISH_GETALLGROUPBYMANAGERID_NAME "GETALLGROUPBYMANAGERID"

#define SOLUTIONGATEWAY_PUBLISH_CMT_EVENT "CM"
#define SOLUTIONGATEWAY_SUBSCRIBE_LOGINANS_NAME "LOGINANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_LOGOUTANS_NAME "LOGOUTANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_CHANGEPASSWORDANS_NAME "CHANGEPASSWORDANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_CHANGEBALANCEANS_NAME "CHANGEBALANCEANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATETRADERANS_NAME "UPDATETRADERANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_GETMANAGERSANS_NAME "GETMANAGERSANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_GETTRADERSANS_NAME "GETTRADERSANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_INSERTUPDATEMANAGERRIGHTSANS_NAME "INSERTUPDATEMANAGERRIGHTSANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_GETMANAGERACCESSANS_NAME "GETMANAGERACCESSANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_USERDELETECHECKANS_NAME "USERDELETECHECKREQANS"    
#define SOLUTIONGATEWAY_SUBSCRIBE_USERDELETEANS_NAME "USERDELETEREQANS"  
#define SOLUTIONGATEWAY_SUBSCRIBE_CREATETRADERANS_NAME "CREATETRADERANS" 
#define SOLUTIONGATEWAY_SUBSCRIBE_GETONLINETRADERANS_NAME "GETONLINETRADERANS" 

#define SOLUTIONGATEWAY_SUBSCRIBE_DISABLETRADERANS_NAME "DISABLETRADERANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_KICKOUTTRADERANS_NAME "KICKOUTTRADERANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETTRADERBYTRADERIDANS_NAME "GETTRADERBYTRADERIDANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETALLGROUPBYMANAGERIDANS_NAME "GETALLGROUPBYMANAGERIDANS"

//For RM
#define SOLUTIONGATEWAY_PUBLISH_GETPOSITIONSREQ_NAME "GETPOSITIONSREQ"
#define SOLUTIONGATEWAY_PUBLISH_GETTOP5BOREQ_NAME "GETTOP5BOREQ"
#define SOLUTIONGATEWAY_PUBLISH_GETCUSTMBOREQ_NAME "GETCUSTMBOREQ"
#define SOLUTIONGATEWAY_PUBLISH_GETSYMBOLBOREQ_NAME "GETSYMBOLBOREQ"
#define SOLUTIONGATEWAY_PUBLISH_GETTOP5BOREMOVEREQ_NAME "GETTOP5BOREMOVEREQ"
#define SOLUTIONGATEWAY_PUBLISH_GETCUSTMBOREMOVEREQ_NAME "GETCUSTMBOREMOVEREQ"
#define SOLUTIONGATEWAY_PUBLISH_GETSYMBOLBOREMOVEREQ_NAME "GETSYMBOLBOREMOVEREQ"
#define SOLUTIONGATEWAY_PUBLISH_RM_EVENT "RM"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETPOSITIONSANS_NAME "GETPOSITIONSANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETTOP5BOANS_NAME "GETTOP5BOANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETCUSTOMIZEBOANS_NAME "GETCUSTOMIZEBOANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETSYMBOLMONITORANS_NAME "GETSYMBOLMONITORANS"
// #define SOLUTIONGATEWAY_SUBSCRIBE_RISKMANAGEMENT_NAME "RISKMANAGEMENT"
// #define SOLUTIONGATEWAY_SUBSCRIBE_RISKMANAGEMENT_TOP5BO_EVENT_NAME "TOP5BO"	
// #define SOLUTIONGATEWAY_SUBSCRIBE_RISKMANAGEMENT_CUSTOMBO_EVENT_NAME "CUSTOMBO"	
// #define SOLUTIONGATEWAY_SUBSCRIBE_RISKMANAGEMENT_SYMBOLBO_EVENT_NAME "SYMBOLBO"

#define SOLUTIONGATEWAY_SUBSCRIBE_RISKMANAGEMENTTOP5BO_NAME "RISKMANAGEMENTTOP5BO"
#define SOLUTIONGATEWAY_SUBSCRIBE_RISKMANAGEMENTCUSTOMBO_NAME "RISKMANAGEMENTCUSTOMBO"
#define SOLUTIONGATEWAY_SUBSCRIBE_RISKMANAGEMENTSYMBOLBO_NAME "RISKMANAGEMENTSYMBOLBO"
#define SOLUTIONGATEWAY_SUBSCRIBE_RMUPDATETRADERBALANCE_NAME "RMUPDATETRADERBALANCE"

#define SOLUTIONGATEWAY_SUBSCRIBE_ONLINETRADERONROOT_NAME "ONLINETRADERONROOT"	
#define SOLUTIONGATEWAY_SUBSCRIBE_LOGOUTTRADERONROOT_NAME "LOGOUTTRADERONROOT"
#define SOLUTIONGATEWAY_SUBSCRIBE_NEWTRADERONROOT_NAME "NEWTRADERONROOT"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATETRADERONROOT_NAME "UPDATETRADERONROOT"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEOPENTRADEONROOT_NAME "UPDATEOPENTRADEONROOT"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATECLOSEDTRADEONROOT_NAME "UPDATECLOSEDTRADEONROOT"
#define SOLUTIONGATEWAY_SUBSCRIBE_DELETETRADERONROOT_NAME "DELETETRADERONROOT"

//for RMX
#define SOLUTIONGATEWAY_PUBLISH_GETPOSITIONSREQX_NAME "GETPOSITIONSREQX"
//#define SOLUTIONGATEWAY_PUBLISH_RMX_EVENT "RMX"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETPOSITIONSANSX_NAME "GETPOSITIONSANSX"
#define SOLUTIONGATEWAY_SUBSCRIBE_RMUPDATETRADERBALANCEX_NAME "RMUPDATETRADERBALANCEX"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEPOSITIONSANSX_NAME "UPDATEPOSITIONSANSX"
#define SOLUTIONGATEWAY_SUBSCRIBE_ORDERCHANGEBALANCE_NAME "ORDERCHANGEBALANCE"

//for Admin service
#define SOLUTIONGATEWAY_PUBLISH_ADMINLOGINREQ_NAME "ADMINLOGINREQ"
#define	SOLUTIONGATEWAY_PUBLISH_ADMINRECONNECT_NAME "ADMINRECONNECT"
#define SOLUTIONGATEWAY_PUBLISH_ADMINLOGOUTREQ_NAME "ADMINLOGOUTREQ"
#define SOLUTIONGATEWAY_PUBLISH_ADMINGCHANGEPASSWORDREQ_NAME "ADMINGCHANGEPASSWORDREQ"
#define SOLUTIONGATEWAY_PUBLISH_CREATEMANAGERREQ_NAME "CREATEMANAGERREQ"
#define SOLUTIONGATEWAY_PUBLISH_UPDATEMANAGERREQ_NAME "UPDATEMANAGERREQ"
#define SOLUTIONGATEWAY_PUBLISH_DELETEMANAGERREQ_NAME "DELETEMANAGERREQ"
#define SOLUTIONGATEWAY_PUBLISH_UPDATEMANAGERRIGHTREQ_NAME "UPDATEMANAGERRIGHTREQ"
#define SOLUTIONGATEWAY_PUBLISH_GETMANAGERRIGHTREQ_NAME "GETMANAGERRIGHTREQ"
#define SOLUTIONGATEWAY_PUBLISH_GETADMINS_NAME "GETADMINS"
#define SOLUTIONGATEWAY_PUBLISH_GETMANAGERSREQ_NAME "GETMANAGERSREQ"
#define SOLUTIONGATEWAY_PUBLISH_ENABLEDISABLEMANAGER_NAME  "ENABLEDISABLEMANAGER"
#define SOLUTIONGATEWAY_PUBLISH_DELETEADMIN_NAME "DELETEADMIN"
#define SOLUTIONGATEWAY_PUBLISH_CREATEADMIN_NAME "CREATEADMIN"
#define SOLUTIONGATEWAY_PUBLISH_UPDATEADMIN_NAME "UPDATEADMIN"

//for account
#define SOLUTIONGATEWAY_PUBLISH_CREATEACCOUNT_NAME "CREATEACCOUNT"
#define SOLUTIONGATEWAY_PUBLISH_UPDATEACCOUNT_NAME "UPDATEACCOUNT"
#define SOLUTIONGATEWAY_PUBLISH_GETALLACCOUNTS_NAME "GETALLACCOUNTS"
#define SOLUTIONGATEWAY_PUBLISH_GETACCOUNTSBYACCOUNTID_NAME "GETACCOUNTSBYACCOUNTID"
//for group
#define SOLUTIONGATEWAY_PUBLISH_CREATEGROUP_NAME "CREATEGROUP" 
#define SOLUTIONGATEWAY_PUBLISH_UPDATEGROUP_NAME "UPDATEGROUP" 
#define SOLUTIONGATEWAY_PUBLISH_GETGROUPDETAILSBYID_NAME "GETGROUPDETAILSBYID" 
#define SOLUTIONGATEWAY_PUBLISH_GETALLGROUPFORGATEWAY_NAME "GETALLGROUPFORGATEWAY" 
#define SOLUTIONGATEWAY_PUBLISH_GETALLGROUP_NAME "GETALLGROUP" 
#define SOLUTIONGATEWAY_PUBLISH_DELETEGROUP_NAME "DELETEGROUP" 
#define SOLUTIONGATEWAY_PUBLISH_UPDATEGROUPSECURITY_NAME "UPDATEGROUPSECURITY" 
#define SOLUTIONGATEWAY_PUBLISH_UPDATEGROUPREPORT_NAME "UPDATEGROUPREPORT" 
#define SOLUTIONGATEWAY_PUBLISH_SAVEMANAGERAGAINSTGROUPS_NAME "SAVEMANAGERAGAINSTGROUPS"
#define SOLUTIONGATEWAY_PUBLISH_GETALLGROUPSBYMANAGERID_NAME "GETALLGROUPSBYMANAGERID"
//for security and symbol
#define SOLUTIONGATEWAY_PUBLISH_CREATESECURITY_NAME "CREATESECURITY"
#define SOLUTIONGATEWAY_PUBLISH_UPDATESECURITY_NAME "UPDATESECURITY"
#define SOLUTIONGATEWAY_PUBLISH_GETALLSECURITY_NAME "GETALLSECURITY"
#define SOLUTIONGATEWAY_PUBLISH_DELETESECURITY_NAME "DELETESECURITY"
#define SOLUTIONGATEWAY_PUBLISH_CREATESYMBOL_NAME "CREATESYMBOL"
#define SOLUTIONGATEWAY_PUBLISH_UPDATESYMBOL_NAME "UPDATESYMBOL"
#define SOLUTIONGATEWAY_PUBLISH_GETALLSYMBOL_NAME "GETALLSYMBOL"
#define SOLUTIONGATEWAY_PUBLISH_GETSYMBOLBYID_NAME "GETSYMBOLBYID"
#define SOLUTIONGATEWAY_PUBLISH_DELETESYMBOL_NAME "DELETESYMBOL"
#define SOLUTIONGATEWAY_PUBLISH_ADT_EVENT "ADT"
#define SOLUTIONGATEWAY_SUBSCRIBE_ADMINLOGINANS_NAME "ADMINLOGINANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_ADMINLOGOUTANS_NAME "ADMINLOGOUTANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_ADMINCHANGEPASSWORDANS_NAME "ADMINCHANGEPASSWORDANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_CREATEMANAGERANS_NAME "CREATEMANAGERANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEMANAGERANS_NAME "UPDATEMANAGERANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_DELETEMANAGERANS_NAME "DELETEMANAGERANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEMANAGERRIGHTANS_NAME "UPDATEMANAGERRIGHTANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETMANAGERRIGHTANS_NAME "GETMANAGERRIGHTANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETADMINSANS_NAME "GETADMINSANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETMANAGERSANS_NAME "GETMANAGERSANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_ENABLEDISABLEMANAGERANS_NAME "ENABLEDISABLEMANAGERANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_DELETEADMINANS_NAME "DELETEADMINANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_CREATEADMINANS_NAME "CREATEADMINANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEADMINANS_NAME "UPDATEADMINANS"

#define	SOLUTIONGATEWAY_PUBLISH_SYNCHDATA_NAME "SYNCHDATA"
#define	SOLUTIONGATEWAY_SUBSCRIBE_SYNCHDATAANS_NAME "SYNCHDATAANS"


//for account
#define SOLUTIONGATEWAY_SUBSCRIBE_CREATEACCOUNTANS_NAME "CREATEACCOUNTANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEACCOUNTANS_NAME "UPDATEACCOUNTANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETALLACCOUNTSANS_NAME "GETALLACCOUNTSANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETACCOUNTSBYACCOUNTIDANS_NAME "GETACCOUNTSBYACCOUNTIDANS"
//for group
#define SOLUTIONGATEWAY_SUBSCRIBE_CREATEGROUPANS_NAME "CREATEGROUPANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEGROUPANS_NAME "UPDATEGROUPANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETGROUPDETAILSBYIDANS_NAME "GETGROUPDETAILSBYIDANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETALLGROUPFORGATEWAYANS_NAME "GETALLGROUPFORGATEWAYANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETALLGROUPANS_NAME "GETALLGROUPANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_DELETEGROUPANS_NAME "DELETEGROUPANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEGROUPSECURITYANS_NAME "UPDATEGROUPSECURITYANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATEGROUPREPORTANS_NAME "UPDATEGROUPREPORTANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_SAVEMANAGERAGAINSTGROUPS_NAME "SAVEMANAGERAGAINSTGROUPSANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETALLGROUPSBYMANAGERID_NAME "GETALLGROUPSBYMANAGERIDANS"
//for security and symbol
#define SOLUTIONGATEWAY_SUBSCRIBE_CREATESECURITYANS_NAME "CREATESECURITYANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATESECURITY_NAME "UPDATESECURITYANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETALLSECURITYANS_NAME "GETALLSECURITYANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_DELETESECURITYANS_NAME "DELETESECURITYANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_CREATESYMBOLANS_NAME "CREATESYMBOLANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_UPDATESYMBOLANS_NAME "UPDATESYMBOLANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETALLSYMBOLANS_NAME "GETALLSYMBOLANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_GETSYMBOLBYIDANS_NAME "GETSYMBOLBYIDANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_DELETESYMBOLANS_NAME "DELETESYMBOLANS"


//common	
#define SOLUTIONGATEWAY_PUBLISH_FORCELOGOUT_NAME "FORCELOGOUT"
#define SOLUTIONGATEWAY_SUBSCRIBE_FORCELOGOUT_NAME "FORCELOGOUT"
#define SOLUTIONGATEWAY_SUBSCRIBE_ADMINFORCELOGOUT_NAME "ADFORCELOGOUT"
#define SOLUTIONGATEWAY_PUBLISH_MONITORANS_NAME "MONITORANS"
#define SOLUTIONGATEWAY_SUBSCRIBE_MONITOR_NAME "MONITOR"
	

enum ETag {	
	//for common
	EMONITOR = 0xA001,
	EMONTORANS = 0xA002,

	//for CM
	ESUBSCRIBE = 0x0063,
	ESUBSCRIBEANS = 0x0064,
	ELOGIN = 0x0065,
	ELOGINANS = 0x0066,
	ELOGOUT = 0x0067,
	ELOGOUTANS = 0x0068,
	ECHANGEPASSWORD = 0x0069,
	ECHANGEPASSWORDANS = 0x006a,
	ECHANGEBALANCE = 0x006b,
	ECHANGEBALANCEANS = 0x006c,
	EUPDATETRADER = 0x0071,
	EUPDATETRADERANS = 0x0072,
	ECREATETRADER = 0x0073,
	ECREATETRADERANS = 0x0074,
	EGETTRADERS = 0x0077,
	EGETTRADERSANS = 0x0078,
	ECMTFORCELOGOUT = 0x0079,
	ECMFORCELOGOUTANS = 0x007A,
	EINSERTUPDATEMANAGERRIGHTS = 0x007d,
	EINSERTUPDATEMANAGERRIGHTSANS = 0x007e,
	EGETMANAGERACCESS = 0x007F,	
	EGETMANAGERACCESSANS = 0x0080,
	EGETONLINETRADER = 0x0081,
	EGETONLINETRADERANS = 0x0082,
	EUSERDELETECHECKREQ = 0x0083,
	EUSERDELETECHECKANS= 0x0084,
	EUSERDELETEREQ = 0x0085,
	EUSERDELETEANS= 0x0086,
	ECMTRECONNECT = 0x0087,

	//new reverse
	BatchUpdateByTicket = 0x0087,//
	//**=0x0088,
	EDISABLETRADER = 0x0089,
	EDISABLETRADERANS = 0x008A,
	EKICKOUTTRADER = 0x008B,
	EKICKOUTTRADERANS = 0x008C,
	EGETTRADERBYTRADERID = 0x008D,
	EGETTRADERBYTRADERIDANS = 0x008E,
	EGETALLGROUPBYMANAGERID = 0x008F,
	EGETALLGROUPBYMANAGERIDANS = 0x0090,

	//CM broadcasting tag/5
	EONLINETRADERONROOT = 0x0316,
	ELOGOUTTRADERONROOT = 0x0318,
	ENEWTRADERONROOT = 0x031A,
	EUPDATETRADERONROOT = 0x031C,
	EDELETETRADERONROOT = 0x0322,

 	//for RM 
	EGETPOSITIONSREQ  = 0x0301,
	GETPOSITIONSANS = 0x0302,
	EGETTOP5BOREQ  = 0x0303,
	GETTOP5BOANS = 0x0304,
	EGETCUSTMBOREQ  = 0x0305,
	GETCUSTOMIZEBOANS = 0x0306,
	EGETSYMBOLBOREQ  = 0x0307,
	GETSYMBOLMONITORANS = 0x0308,
	EGETTOP5BOREMOVEREQ  = 0X0309,
	EGETCUSTMBOREMOVEREQ  = 0X0311,
	EGETSYMBOLBOREMOVEREQ  = 0X0313,

	//RM broadcasting tag
	RISKMANAGEMENTTOP5BO = 0x030A,
	RISKMANAGEMENTCUSTOMBO = 0x030C,
	RISKMANAGEMENTSYMBOLBO = 0x030E,
	RMUPDATETRADERBALANCE = 0x0310,
	EUPDATEOPENTRADEONROOT = 0X031E,
	EUPDATECLOSEDTRADEONROOT = 0x0320,

	//for report server and RMX /6
	EGETPOSITIONSREQX  = 0x0323,
	EGETPOSITIONSANSX = 0x0324,
	//RM broadcasting for reportserver
	ERMUPDATETRADERBALANCEX = 0x0326,// removed?
	EUPDATEPOSITIONSANSX = 0x0328, // removed?
	ERISKMANAGEMENT = 0x032A,// removed?
	EORDERCHANGEBALANCE = 0x032C,

	//new reverse
	OrderTransfer = 0X0331,
	//OrderSymbolUpdate = 0X0333,
	OrderGet = 0X0335,
	OrderDelete = 0X0337,
	OrderNew = 0X0339,
	//OrderClose = 0X033B,
	OrderModify = 0X033D,

 	//for ADT normal
 	EADMINRECONNECT = 0x03FF,
	EADMINLOGINREQ = 0x0401,
	EADMINLOGINANS = 0x0402,
	EADMINLOGOUTREQ = 0x0403,
	EADMINLOGOUTANS = 0x0404,
	EADMINGCHANGEPASSWORDREQ = 0x0405,
	EADMINCHANGEPASSWORDANS = 0x0406,
	ECREATEMANAGERREQ = 0x0407,
	ECREATEMANAGERANS = 0x0408,
	EUPDATEMANAGERREQ = 0x0409,
	EUPDATEMANAGERANS = 0x040A,
	EDELETEMANAGERREQ = 0x040B,
	EDELETEMANAGERANS = 0x040C,
	EUPDATEMANAGERRIGHTREQ = 0x040D,
	EUPDATEMANAGERRIGHTANS = 0x040E,

	EGETADMINS = 0x040F,
	EGETADMINSANS = 0x0410,
	EDELETEADMIN = 0x0411,
	EDELETEADMINANS = 0x0412,  
	ECREATEADMIN = 0x413,
	ECREATEADMINANS = 0x414,
	EUPDATEADMIN = 0x415,
	EUPDATEADMINANS = 0x416,

	EGETMANAGERSREQ = 0x0475,
	EGETMANAGERSANS = 0x0476,
	EADFORCELOGOUT = 0x0479,
	EADFORCELOGOUTANS = 0x047A,
	EENABLEDISABLEMANAGER = 0x047B,
	EENABLEDISABLEMANAGERANS = 0x047C,
	EGETMANAGERRIGHTREQ = 0x047F,
	EGETMANAGERRIGHTANS = 0x0480,
	//new reverse
	UserSetGroup = 0x0411,
	GroupsListGet = 0x0413,

	//for ADT account
	ECREATEACCOUNT = 0x07CF,
	ECREATEACCOUNTANS = 0X07D0,
	EUPDATEACCOUNT = 0x07D1,
	EUPDATEACCOUNTANS = 0X07D2,
	EGETALLACCOUNTS = 0x07D3,
	EGETALLACCOUNTSANS = 0X07D4,
	EGETACCOUNTSBYACCOUNTID = 0x07D5,
	EGETACCOUNTSBYACCOUNTIDANS = 0X07D6,

	//for ADT group
	ECREATEGROUP = 0x07f5,
	ECREATEGROUPANS = 0x07f6,
	EUPDATEGROUP  = 0x07f7,
	EUPDATEGROUPANS  = 0x07f8,
	EGETGROUPDETAILSBYID = 0x07f9,
	EGETGROUPDETAILSBYIDANS = 0x07fA,
	EGETALLGROUPFORGATEWAY = 0x07fb,
	EGETALLGROUPFORGATEWAYANS = 0x07fC,
	EGETALLGROUP = 0x07fd,
	EGETALLGROUPANS = 0x07fE,
	EDELETEGROUP = 0x07ff,
	EDELETEGROUPANS = 0x0800,
	EUPDATEGROUPSECURITY = 0x0801,
	EUPDATEGROUPSECURITYANS = 0x0802,
	EUPDATEGROUPREPORT = 0x0803,
	EUPDATEGROUPREPORTANS = 0x0804,

	ESAVEMANAGERAGAINSTGROUPS = 0x0805,
	ESAVEMANAGERAGAINSTGROUPSANS = 0x0806,
	EGETALLGROUPSBYMANAGERID = 0x0807,
	EGETALLGROUPSBYMANAGERIDANS = 0x0808,

	//for ADT security
	ECREATESECURITY = 0x0815,
	ECREATESECURITYANS = 0x0816,
	EUPDATESECURITY = 0x0817,
	EUPDATESECURITYANS = 0x0818,
	EGETALLSECURITY = 0x0819,
	EGETALLSECURITYANS = 0x081A,
	EDELETESECURITY = 0x081B,
	EDELETESECURITYANS = 0x081C,

	//for ADT symbol
	ECREATESYMBOL = 0x0831,
	ECREATESYMBOLANS = 0x0832,
	EUPDATESYMBOL = 0x0833,
	EUPDATESYMBOLANS = 0x0834,
	EGETALLSYMBOL = 0x0835,
	EGETALLSYMBOLANS = 0x0836,
	EGETSYMBOLBYID = 0x0837,
	EGETSYMBOLBYIDANS = 0x0838,
	EDELETESYMBOL = 0x0839,
	EDELETESYMBOLANS = 0x083A,

	ESYNCHDATA = 0x83F,
	ESYNCHDATAANS = 0x840,
};

enum ELogin {
	ELOGINDEFAULT = 0x00,
	ELOGINSUCCESS = 0x01,
	ELOGININVALID = 0x02,
	ELOGINUNWRITE = 0x04,
	ELOGINCLOSE = 0x08,
	ELOGINLOGOUT = 0x10,
	ELOGINREJECT = 0x20,
	ELOGINEXIT = 0x40,
};

enum EPullType {
	EPDEFAULT = 0x00,
	EPINIT = 0x01,  /* login: CM->PM*/
	EPDEPOSITE = 0x02,
	EPWITHDRAWAL = 0x04,
	EPFEEDBACK = 0x08,
	EPUSERINFO = 0x10, /* login CM->SG*/
	EPLOGOUT = 0x20, /* logout (CM->PM) */
	EPFORCELOGOUT = 0x40, /* forcelogout(CM->PM) */
};

struct HeaderTag {
	HeaderTag();
	unsigned char head;
	unsigned char reserved;
	unsigned short tag;
	unsigned int length;
};

//namespace snetwork_xservice_solutiongateway {
/* from hex to binary */
extern char DecLookupTable[];
void HexToBinary(char* dst, char* src, size_t len);
/* from dec to hex string */
extern char HexLookupTable[513];
extern char hexLookupTable[513];
//void DecToHex(char* dst, char* src, size_t len = 16, bool lower = true);
void DecToHex(char* dst, char* src, size_t len = 10, bool lower = true);

#if 0
typedef struct {
	uv_tcp_t handle;
	http_parser parser;
	struct sockaddr_in peer_name;
	//http_request request;
} client_t;
#endif

extern const char* POSITION_DB_NAME;
extern const char* PM_SEND_ORDER_FORMAT;
extern const char* POSITION_DELETE_PULL_FORMAT;
extern const char* SG_SEND_ORDER_FORMAT;
extern const char* SELECT_VALID_FORMAT;
extern const char* PM_ORDER_ANS_FORMAT;
extern const char* SG_ORDER_ANS_FORMAT;
extern const char* POSITION_UPDATE_VALID_FORMAT;
extern const char* POSITION_UPDATE_PULL_FORMAT;
extern const char* PM_VALIDATE_ORDER_FORMAT;
extern const char* SG_VALIDATE_ORDER_FORMAT;
extern const char* POSITION_UPDATE_VALID_WIN_FORMAT;
extern const char* POSITION_UPDATE_VALID_LOSS_FORMAT;
extern const char* POSITION_UPDATE_VALID_REJECT_FORMAT;
extern const char* INSERT_POSITION_LOG_FORMAT; 
extern const char* INSERT_POSITION_INIT_FORMAT;

extern const char* SG_CLIENT_LOGIN_FORMAT;
extern const char* SG_CLIENT_LOGOUT_FORMAT;
template<typename T>
inline void FREE(T** t) {
	if (*t != nullptr)
	{
		free(*t);
		*t = nullptr;
	}
}

template<typename T>
inline void DELETE(T** t) {
	delete(*t);
	*t = nullptr;
}

inline long GetMicroSecond(void) {
	return std::chrono::system_clock::now().time_since_epoch()/std::chrono::microseconds(1);
}

/***MonitorReq start***/
struct  MonitorReq {
public:
	MonitorReq();
	MonitorReq(char* reqID, 
			uint32_t mid, 
			uint64_t timeStamp);
	~MonitorReq();
	MonitorReq(const MonitorReq& r);
	MonitorReq& operator=(const MonitorReq& r);
	MonitorReq(MonitorReq&& r);
	MonitorReq& operator=(MonitorReq&& r);

public:
	const char* ToJson(void);

public:
	char* Json;
	char* ReqID; //[32]; //
	uint32_t Mid;
	uint64_t TimeStamp;//long
};

/***MonitorReq end***/

/***MonitorAns start***/
struct MonitorAns {
public:
	MonitorAns();
	MonitorAns(const char* reqID, 
			char status, 
			const char* name,
			uint32_t pid,
			uint32_t mid,
			uint64_t timeStamp,
			uint64_t startTimes);
	~MonitorAns();
	MonitorAns(const MonitorAns& r);
	MonitorAns& operator=(const MonitorAns& r);
	MonitorAns(MonitorAns&& r);
	MonitorAns& operator=(MonitorAns&& r);

public:
	const char* ToJson(void);

public:	
	char* Json;
	char* ReqID; //[32];
	char  Status;
//	cha	  pad[2] // don't worry about this for now
	char* Name; //[16];
	uint32_t 	Pid;
	uint32_t 	Mid;
	uint64_t	TimeStamp;
	uint64_t	StartTimes;	
};
/***MonitorAns end***/
// status { unknown=0, initiate,  booting,  running,  stopping,  stopped}

void InitDaemon();

#endif 
