////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  methods that used by customer or partner to manage the roomserives
////////////////////////////////////////////////////////////////////
#ifndef RoomServicesManager_h__
#define RoomServicesManager_h__

#include "Headers.h"
#include "RoomServices.h"
#include <sstream>
using namespace std;
class CRoomServices;
class CRoomServicesManager
{
private:

	map<int, CRoomServices *> mapRoomNumAndRoomServices;
	map<int, CRoomServices *> mapNewRoomNumAndRoomServices;
	vector<string> vServicesList = { "Laundry", "Dry Clean", "Tea", "Coffee", "Bed Sheets", "Wake Up", "Room Clean", "Do Not Disturb", "Text Msg" };

	vector<string> getServicesString(int, int);
	vector<string> vecHotelServices;
	vector<string> vecHotelServicesPrices;

	void getRoomServices(int, int);
	void priceInit(int);//iHotelID


public:
	CRoomServicesManager(void);
	CRoomServicesManager(int, int);
	~CRoomServicesManager(void);


	void checkRoomServices(int, int);
	void displayRoomServicesAv();
	// update when service is provided
	void modifyRoomServicesP(int, int, int, int, string); //hotelID,Room#,Services ID,Service#
	void addRoomServicesC(int, int, int, int, string);
	void modifyRoomServicesC(int, int, int, int, string); //hotelname,Room#,Services ID,Service#
	int calculateTotalPrice(int, int);
	void updateCSIFile(int, int, string);
	void modifyRoomServicesAv(int, int);
	void modifyRoomServicesPrice(int, int, int);
	void updateRSAvFile(int);
	void updateNotificationFile(int, int);
	void addToNotificationFile();
	void displayNotification(int);
	void removeNotification();
	bool checkRoomExistance(string, string);
	void createAnEntryInNRSInfoFile(int, int);
	void deleteIfNoServicesAdded(int, int);
	int getCurrentPrice(int, int);
	int getNewAddedPrice(int, int);
};

#endif