#ifndef Booking_h__
#define Booking_h__

#include "Headers.h"

class CBooking
{
public:
	CBooking(void);
	~CBooking(void);
public:
	void NewBooking();
	void NewBooking(int hotel_id, int room_id, int booking_id, int customer_id, std::string user);
	void setBookingID(int ID);
	int getBookingID();
	void setBookingStatus(int);
	int getBookingStatus();
	void setRoomID(int);
	int getRoomID();
	void sethotelID(int id);
	int gethotelID();
	void setLastUpdate(std::string);
	std::string getLastUpdate();
	void setUserName(std::string);
	std::string getUserName();
	void setCustomerID(std::string strCustomerID);
	std::string getCustomerID();

	void setNumPeople(int);
	void setNumRoomsBooked(int);
	void setMultipleRoomIDs(std::vector<int>);
	std::vector<int> getMultipleRoomIDs(void);


private:
	int bookingID;
	std::string customerID;
	int hotelID;
	int roomID;
	std::string userName;
	std::string lastUpdate;
	int status;
	//CUser user;  // temporary, not needed

	std::vector<int> multipleRoomIDs;


};
#endif










