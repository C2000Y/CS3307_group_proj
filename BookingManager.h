#ifndef BookingManager_h__
#define BookingManager_h__

#include "Headers.h"

class CBooking;
class CHotelManager;
class CBookingManager
{
public:
	CBookingManager(void);
	~CBookingManager(void);

public:
	void Init_Manager(CHotelManager* _pHotelMan);

public:
	CBooking* Retrieve_Booking(std::string _strBookingID);
	//CBooking Find_Booking(std::string _strBookingID);
	//int getGlobalBookingNum();
	CBooking* Create_Booking_Multiple_Rooms(std::vector<int> roomIDs, std::string hotelID, std::string customerID, std::string userName);
	void Cancel_Booking_Multiple_Rooms(std::string bookingIDs);

private:
	//void Load_Bookings(std::ifstream* _fp);
	void Load_Bookings(void);
	void Save_Bookings();

	void Delete_Single_Booking(std::string _strBookingID);
	void Store_Single_Booking_Multiple_Rooms(CBooking* _pBooking);
	void Clean_Booking_File();
	// void SendInfo_ToHotelmanager(int roomID, int hotelID, std::string username, std::string command);
	void SendInfo_ToHotelmanager_MultipleRooms(std::vector<int> multipleRoomIDs, int hotelID, std::string username, std::string command);
	bool Find_RoomID_In_Vector(int, std::vector<int>);
	void Tokenize_Comma(std::ifstream* _fp, std::string* _strToken);
	int generateBookingID();
private:

	//int bookingManSize; // added
	int gBookingID; // added
	std::map<std::string, CBooking*> m_mapBookings;
	CHotelManager*    m_pHotelMan;
	CBooking*    m_pBookingShell;

};
#endif



