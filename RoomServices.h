////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  room services class and methods
////////////////////////////////////////////////////////////////////
#ifndef RoomServices_h__
#define RoomServices_h__

#include "Headers.h"
using namespace std;

class CRoomServices
{
public:
	CRoomServices(void);
	~CRoomServices(void);

public:
	CRoomServices(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, string);

private:
	//for customer
	int iLaundryStatus = 0;
	int iDryCleanStatus = 0;
	int iTeaStatus = 0;
	int iCoffeeStatus = 0;
	int iWakeUpStatus = 0;
	int iBedSheetsStatus = 0;
	int iRoomCleanStatus = 0;
	int iDoNotDisturbStatus = 0;
	int iTextMsgStatus = 0;
	//number of services
	int iLaundryNum = 0;
	int iDryCleanNum = 0;
	int iTeaNum = 0;
	int iCoffeeNum = 0;
	int iBedSheetsNum = 0;

	//price of services
	int iLaundryPrice = 0;
	int iDryCleanPrice = 0;
	int iTeaPrice = 0;
	int iCoffeePrice = 0;
	int iBedSheetsPrice = 0;
	const int iRoomCleanPrice = 0;
	const int iWakeUpPrice = 0;
	const int iDoNotDisturbPrice = 0;
	const int iTextMsgPrice = 0;
	//wake up service time
	int iWakeUpTime = 0;
	string sTextMsg = "None";

	vector<int> vAllStatus;
	vector<int> vAllNum;
	vector<string> vAllServices = { "Laundry", "Dry Clean", "Tea", "Coffee", "Bed Sheets", "Wake Up", "Room Clean", "Do Not Disturb", "Test Msg" };

public:
	void setLaundryPrice(int);
	void displayLaundryPrice();
	void changeLaundryStatus();
	int getLaundryPrice();

	void setDryCleanPrice(int);
	void displayDryCleanPrice();
	void changeDryCleanStatus();
	int getDryCleanPrice();

	void setTeaPrice(int);
	void displayTeaPrice();
	void changeTeaStatus();
	int getTeaPrice();

	void setCoffeePrice(int);
	void displayCoffeePrice();
	void changeCoffeeStatus();
	int getCoffeePrice();

	void setBedSheetsPrice(int);
	void displayBedSheetsPrice();
	void changeBedSheetsStatus();
	int getBedSheetsPrice();


	void displayRoomCleanPrice();
	void changeRoomCleanStatus();
	int getRoomCleanStatus();
	int getDNDStatus();
	int getTextMsgStatus();
	void setTextMsg(string);
	void changeTextMsgStatus();
	string getTextMsg();

	void changeDoNotDisturbStatus();
	void setWakeUpTime(int);
	void changeWakeUpStatus();
	int getWakeUpTime();

	int calculateTotalRoomServicesPrice();

	void displayAllRequiredServices();

	void setLaundryAv();
	void setDryCleanAv();
	void setTeaAv();
	void setCoffeeAv();
	void setWakeUpAv();
	void setBedSheetsAv();
	void setRoomCleanAv();
	void setDoNotDisturbAv();

	int calLaundryP(); //customer use
	int calDryCleanP();
	int calTeaP();
	int calCoffeeP();
	int calBedSheetsP();

	void setLaundryNum(int); //customer use
	void setDryCleanNum(int);
	void setTeaNum(int);
	void setCoffeeNum(int);
	void setBedSheetsNum(int);

	int getLaundryNum(); //customer use
	int getDryCleanNum();
	int getTeaNum();
	int getCoffeeNum();
	int getBedSheetsNum();
	string RSFormating();
	int getLaundryStatus();
	int getDryCleanStatus();
	int getTeaStatus();
	int getCoffeeStatus();
	int getWakeUpStatus();
	int getBedSheetsStatus();

};

#endif
