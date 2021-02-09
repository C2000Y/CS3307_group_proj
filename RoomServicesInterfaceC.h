////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  customer's room services Interface
////////////////////////////////////////////////////////////////////
#ifndef CRoomServicesInterfaceC_h__
#define CRoomServicesInterfaceC_h__
#include "Headers.h"
#include "RoomServices.h"
#include "RoomServicesManager.h"
#include "PaymentInterfaceC.h"
#include "PaymentManager.h"
#include "Payment.h"
#include "BookingManager.h"
#include "Booking.h"
#include "UserGuest.h"
#include <sstream>
using namespace std;

class CRoomServicesInterfaceC
{
private:
	vector<string> vAvServicesList;
	bool integerCheck(string);
	vector<string> vHotelServices;
	vector<string> vHotelServicesPrices;
	vector<string> vAvServices;
	vector<string> vAvServicesPrices;
	vector<string> vServicesList = { "Laundry", "Dry Clean", "Tea", "Coffee", "Bed Sheets", "Wake Up", "Room Clean", "Do Not Disturb", "Text Msg" };
	string sBookingID;
	string sMsg;
	int iHotelID = 1223;
	int iRoomNum = 207;
	string sUserInput;
	string sRoomNum;
	vector<int> vecMultipleRooms;
	vector<string> vSelectedServices;

	int iTotalPrice;
	int iCurrentPrice;
	int iNewPrice;
	string sPaymentChoice;
	bool hotelCheck(string, int); //file name and hotelID
	bool bHotelExistance;

public:
	CRoomServicesInterfaceC();
	~CRoomServicesInterfaceC();
	void servicesChoose();
};

#endif