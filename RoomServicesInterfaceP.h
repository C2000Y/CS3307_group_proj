////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  partner's room services Interface
////////////////////////////////////////////////////////////////////
#ifndef CRoomServicesInterfaceP_h__
#define CRoomServicesInterfaceP_h__
#include "Headers.h"
#include "RoomServices.h"
#include "RoomServicesManager.h"
#include "BookingManager.h"

using namespace std;

class CRoomServicesInterfaceP
{
private:
	vector<string> vecHotels;
	string sHotelID;
	int iHotelID = 1223;
	vector<string> vecRoomNum;
	string sUserInput;
	string sServiceInput;
	string sPriceSelect;
	string sPriceInput;
	string sRoomInput;
	vector<string> vSelectedServices;
	vector<string> vServicesList = { "Laundry", "Dry Clean", "Tea", "Coffee", "Bed Sheets", "Wake Up", "Room Clean", "Do Not Disturb", "Text Msg" };
	string sServiceInputChange;
	string sServiceNum;
	bool integerCheck(string);
	string sNotificationInput;
	bool hotelCheck(string, string); //file name and hotel name


public:
	void partner_display();
	CRoomServicesInterfaceP();
	~CRoomServicesInterfaceP();
};

#endif