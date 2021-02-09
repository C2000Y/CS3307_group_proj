#ifndef BookingInterface_h__
#define BookingInterface_h__

#include "Headers.h"

class CBookingManager;
class CUserGuest;
class CRoom;
class CBooking;
class CHotel;

class CBookingInterface
{
public:
	CBookingInterface();
	~CBookingInterface();

public:
	bool runInterface(CBookingManager* _pBookingManager, CHotel* hotel, std::string roomSize, CUserGuest* user); // pointer to vector of hotels (the options) and the time of their check-in and check-out

private:
	//void showHotels(std::vector<CHotel*> search_results); // shows the hotels that were searched
	void showRooms(std::map<std::string, CRoom*> roomOptionsMap); // shows the rooms in the hotel
	CBooking* confirmBookingMultipleRooms(CBookingManager* bookingman, std::vector<std::string> roomIDs, std::string hotelID, std::string customerID, std::string userName);
	// confirms the booking

	std::map<std::string, CRoom*> initializeRoomOptionsMap(int roomSize, CHotel*);
	CRoom* selectRoom(std::string userSelectedNumber, std::map<std::string, CRoom*>); // selects the room from the roomOptionsMap
	std::vector<CRoom*> selectMultipleRooms(std::vector<std::string> userSelectedNumbers, std::map<std::string, CRoom*>);

	std::string getRoomInfo(CRoom* room);
	bool confirmRoomSelection(std::string yes_or_no);
	void cleanRoomOptionsMap();
	void mainMenuOptions();
	std::vector<std::string> getUserInfo();
	void displayUserInfo(std::vector<std::string>);
	void displayBookingInfo(CBooking* _pBooking, CRoom* _pRoom);
	void displayMultipleRoomsBookingInfo(CBooking* _pBooking, std::vector<CRoom*> _pRoomsVec);

	std::string getValidTelephoneNumber();
	std::string getOnlyDigits(std::string str);
	std::string getRightLength(std::string str);
	std::string getOnlyLetters(std::string word);
	bool checkOnlyLetters(std::string word);
	std::string getValidHouseNumber(std::string);
	bool checkValidHouseNum(std::string houseNum);


	void renderMainMenuOptions(CBookingManager*, CHotel*, std::string, CUserGuest* user);

private:
	std::map<std::string, CRoom*> roomOptionsMap;
};


#endif


