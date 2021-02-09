////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  room services class and methods
////////////////////////////////////////////////////////////////////
#include "RoomServices.h"
using namespace std;

CRoomServices::CRoomServices(void)
{
}

CRoomServices::~CRoomServices(void)
{
	vAllStatus.clear();
	vAllNum.clear();
	vAllServices.clear();
}

CRoomServices::CRoomServices(int iLaunStatus, int iLaunNum, int iDCStatus, int iDCNum, int iTeaStatus, int iTeaNum, int iCoStatus, int iCoNum, int iBSStatus, int iBSNum, int iWUStatus, int iWUTime, int iRCStatus, int iDNDStatus, int iTMsgStatus, string sTMsg)
{
	iLaundryStatus = iLaunStatus;
	iDryCleanPrice = iDCStatus;
	iTeaStatus = iTeaStatus;
	iCoffeeStatus = iCoStatus;
	iBedSheetsStatus = iBSStatus;
	iWakeUpStatus = iWUStatus;
	iRoomCleanStatus = iRCStatus;
	iDoNotDisturbStatus = iDNDStatus;
	iTextMsgStatus = iTMsgStatus;

	iLaundryNum = iLaunNum;
	iDryCleanNum = iDCNum;
	iTeaNum = iTeaNum;
	iCoffeeNum = iCoNum;
	iBedSheetsNum = iBSNum;

	iWakeUpTime = iWUTime;
	sTextMsg = sTMsg;
}

/**
* laundry setter and getter
*/
void CRoomServices::setLaundryPrice(int laundryP)
{
	iLaundryPrice = laundryP;
}
void CRoomServices::displayLaundryPrice()
{
	cout << "Laundry Services Price: $" << iLaundryPrice << " per bucket" << endl;
}
void CRoomServices::changeLaundryStatus()
{
	iLaundryStatus = 1 - iLaundryStatus;
}
int CRoomServices::getLaundryPrice()
{
	return iLaundryPrice;
}

/**
* dry clean getter and setter
*/
void CRoomServices::setDryCleanPrice(int dryCleanP)
{
	iDryCleanPrice = dryCleanP;
}
void CRoomServices::displayDryCleanPrice()
{
	cout << "Dry Clean Services Price: $" << iDryCleanPrice << endl;
}
void CRoomServices::changeDryCleanStatus()
{
	iDryCleanStatus = 1 - iDryCleanStatus;
}
int CRoomServices::getDryCleanPrice()
{
	return iDryCleanPrice;
}

/**
* tea getter and setter
*/
void CRoomServices::setTeaPrice(int teaP)
{
	iTeaPrice = teaP;
}
void CRoomServices::displayTeaPrice()
{
	cout << "Tea price: $" << iTeaPrice << endl;
}
void CRoomServices::changeTeaStatus()
{
	iTeaStatus = 1 - iTeaStatus;
}
int CRoomServices::getTeaPrice()
{
	return iTeaPrice;
}

/**
* coffee setter & getter
*/
void CRoomServices::setCoffeePrice(int coffeeP)
{
	iCoffeePrice = coffeeP;
}
void CRoomServices::displayCoffeePrice()
{
	cout << "Coffee Price: $" << iCoffeePrice << endl;
}
void CRoomServices::changeCoffeeStatus()
{
	iCoffeeStatus = 1 - iCoffeeStatus;
}
int CRoomServices::getCoffeePrice()
{
	return iCoffeePrice;
}

/**
* bedsheets setter & getter
*/
void CRoomServices::setBedSheetsPrice(int bedSheetsP)
{
	iBedSheetsPrice = bedSheetsP;
}
void CRoomServices::displayBedSheetsPrice()
{
	cout << "Bed Sheets Change Services Price: $" << iBedSheetsPrice << endl;
}
void CRoomServices::changeBedSheetsStatus()
{
	iBedSheetsStatus = 1 - iBedSheetsStatus;
}
int CRoomServices::getBedSheetsPrice()
{
	return iBedSheetsPrice;
}

/**
* room clean
*/

void CRoomServices::changeRoomCleanStatus()
{
	iRoomCleanStatus = 1 - iRoomCleanStatus;
}

/**
* text
*/
void CRoomServices::setTextMsg(string textMsg)
{
	sTextMsg = textMsg;
}
void CRoomServices::changeTextMsgStatus()
{
	iTeaStatus = 1 - iTeaStatus;
}
string CRoomServices::getTextMsg()
{
	return sTextMsg;
}

//wake up
void CRoomServices::setWakeUpTime(int wakeUpT)
{
	iWakeUpTime = wakeUpT;
}
int CRoomServices::getWakeUpTime()
{
	return iWakeUpTime;
}
void CRoomServices::changeWakeUpStatus()
{
	iWakeUpStatus = 1 - iWakeUpStatus;
}

int CRoomServices::calculateTotalRoomServicesPrice()
{
	int iLaundryTotal = iLaundryPrice * iLaundryNum;
	int iDrinkTotal = iTeaPrice * iTeaNum + iCoffeePrice * iCoffeeNum;
	int iBedSheetsTotal = iBedSheetsPrice * iBedSheetsNum;
	return iLaundryTotal + iDryCleanPrice + iDrinkTotal + iBedSheetsTotal;
}

void CRoomServices::displayAllRequiredServices()
{
	vAllStatus = { iLaundryStatus, iDryCleanStatus, iTeaStatus, iCoffeeStatus, iBedSheetsStatus, iWakeUpStatus, iRoomCleanStatus, iDoNotDisturbStatus, iTextMsgStatus };

	vAllNum = { iLaundryNum, iDryCleanNum, iTeaNum, iCoffeeNum, iBedSheetsNum };
	for (int i = 0; i < 5; i++)
	{
		if (vAllStatus[i] == true)
		{
			cout << vAllServices[i] << ": " << vAllNum[i] << endl;
		}
	}
	//wake up
	if (vAllStatus[5] == true)
	{
		cout << vAllServices[5] << ":" << iWakeUpTime << endl;
	}

	for (int i = 6; i < vAllStatus.size() - 1; i++)
	{
		if (vAllStatus[i] == true)
		{
			cout << vAllServices[i] << endl;
		}
	}
	//text msg
	if (vAllStatus[8] == true)
	{
		cout << vAllServices[8] << ":" << sTextMsg << endl;
	}
}

int CRoomServices::calLaundryP()
{
	return iLaundryNum * iLaundryPrice;
}
int CRoomServices::calDryCleanP()
{
	return iDryCleanNum * iDryCleanPrice;
}
int CRoomServices::calTeaP()
{
	return iTeaNum * iTeaPrice;
}
int CRoomServices::calCoffeeP()
{
	return iCoffeeNum * iCoffeePrice;
}
int CRoomServices::calBedSheetsP()
{
	return iBedSheetsNum * iBedSheetsPrice;
}

void CRoomServices::setLaundryNum(int iNum)
{
	iLaundryNum = iNum;
}
void CRoomServices::setDryCleanNum(int iNum)
{
	iDryCleanNum = iNum;
}
void CRoomServices::setTeaNum(int iNum)
{
	iTeaNum = iNum;
}
void CRoomServices::setCoffeeNum(int iNum)
{
	iCoffeeNum = iNum;
}
void CRoomServices::setBedSheetsNum(int iNum)
{
	iBedSheetsNum = iNum;
}

void CRoomServices::changeDoNotDisturbStatus()
{
	iDoNotDisturbStatus = !iDoNotDisturbStatus;
}

int CRoomServices::getLaundryNum()
{
	return iLaundryNum;
}
int CRoomServices::getDryCleanNum()
{
	return iDryCleanNum;
}
int CRoomServices::getTeaNum()
{
	return iTeaNum;
}
int CRoomServices::getCoffeeNum()
{
	return iCoffeeNum;
}
int CRoomServices::getBedSheetsNum()
{
	return iBedSheetsNum;
}

string CRoomServices::RSFormating()
{
	vector<int> temp = { iLaundryStatus, iLaundryNum, iDryCleanStatus, iDryCleanNum, iTeaStatus, iTeaNum, iCoffeeStatus, iCoffeeNum, iBedSheetsStatus, iBedSheetsNum, iWakeUpStatus, iWakeUpTime, iRoomCleanStatus, 0, iDoNotDisturbStatus, 0, iTextMsgStatus };
	string result = to_string(iLaundryStatus);
	for (int i = 1; i < temp.size(); i++)
	{
		result.append(",");
		result.append(to_string(temp[i]));
	}
	result.append(",");
	result.append(sTextMsg);
	return result;
}

int CRoomServices::getRoomCleanStatus()
{
	return iRoomCleanStatus;
}
int CRoomServices::getDNDStatus()
{
	return iDoNotDisturbStatus;
}
int CRoomServices::getTextMsgStatus()
{
	return iTextMsgStatus;
}
int CRoomServices::getLaundryStatus()
{
	return iLaundryStatus;
}
int CRoomServices::getDryCleanStatus()
{
	return iDryCleanStatus;
}
int CRoomServices::getTeaStatus()
{
	return iTeaStatus;
}
int CRoomServices::getCoffeeStatus()
{
	return iCoffeeStatus;
}
int CRoomServices::getWakeUpStatus()
{
	return iWakeUpStatus;
}
int CRoomServices::getBedSheetsStatus()
{
	return iBedSheetsStatus;
}
