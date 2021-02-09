////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#include "Payment.h"
using namespace std;

CPayment::CPayment(int iRPayment, int iRStatus, int iRSPayment, int iRSStatus, int iESPayment, int iESStatus)
{
	iRoomPayment = iRPayment;
	iRoomStatus = iRStatus;
	iRoomServicesPayment = iRSPayment;
	iRoomServicesStatus = iRSStatus;
	iExtraServicesPayment = iESPayment;
	iExtraServicesStatus = iESStatus;
}
CPayment::~CPayment()
{
}
//payment types
int CPayment::getRoomPayment()
{
	return iRoomPayment;
}
int CPayment::getRoomServicesPayment()
{
	return iRoomServicesPayment;
}
int CPayment::getExtraServicesPayment()
{
	return iExtraServicesPayment;
}
void CPayment::setRoomPayment(int iRPayment)
{
	iRoomPayment = iRPayment;
}
void CPayment::setRoomServicesPayment(int iRSPayment)
{
	iRoomServicesPayment = iRSPayment;
}
void CPayment::setExtraServicesPayment(int iESPayment)
{
	iExtraServicesPayment = iESPayment;
}

//status
int CPayment::getRoomStatus()
{
	return iRoomStatus;
}
int CPayment::getRoomServicesStatus()
{
	return iRoomServicesStatus;
}
int CPayment::getExtraServicesStatus()
{
	return iExtraServicesStatus;
}
void CPayment::setRoomStatus(int iStatus)
{
	iRoomStatus = iStatus;
}
void CPayment::setRoomServicesStatus(int iStatus)
{
	iRoomServicesStatus = iStatus;
}
void CPayment::setExtraServicesStatus(int iStatus)
{
	iExtraServicesStatus = iStatus;
}
//, iRoomPayment, iRoomStatus, iRoomServicesPayment, iRoomServicesStatus, iExtraServicesPayment, iExtraServicesStatus
string CPayment::paymentFormatting()
{
	vector<int> rtrVal = { iRoomPayment, iRoomStatus, iRoomServicesPayment, iRoomServicesStatus, iExtraServicesPayment, iExtraServicesStatus };
	string rtrStr = "";
	for (int i = 0; i < rtrVal.size(); i++)
	{
		rtrStr.append(",");
		rtrStr.append(to_string(rtrVal[i]));
	}

	return rtrStr;
}