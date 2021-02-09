////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  services Interface to manage all the interfaces related to services
////////////////////////////////////////////////////////////////////
#ifndef ServicesInterface_h__
#define ServicesInterface_h__
#include "Headers.h"
#include "RoomServicesInterfaceC.h"
#include "RoomServicesInterfaceP.h"
#include "ExtraServicesInterfaceC.h"
#include "ExtraServicesInterfaceP.h"
#include "RoomServicesManager.h"
#include "ExtraServicesManager.h"
#include "RoomServices.h"
#include "Gym.h"
#include "Dining.h"
#include "Arcade.h"
using namespace std;

class CServicesInterface
{
private:
	string sBookingID;
	string sHotelID;
	int iHotelID;


	string sRoomNum;
	vector<int> vecMultipleRooms;
	bool integerCheck(string);
	string sUserInput;
	string sUserIdentity;

public:
	CServicesInterface();
	~CServicesInterface();
	bool services_display();
};
#endif