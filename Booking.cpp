#include "Booking.h"

CBooking::CBooking(void)
{
}

CBooking::~CBooking(void)
{
}
void CBooking::NewBooking()
{
	hotelID = 0;
	roomID = 0;
	bookingID = 0;
	customerID = "";
	userName = "";


}
/*
void CBooking::NewBooking(int hotel_id, int room_id, int booking_id, int customer_id, std::string user)
{
hotelID = hotel_id;
roomID = room_id;
bookingID = booking_id;
customerID = customer_id;
userName = user;
}
*/
void CBooking::setBookingID(int id)
{
	bookingID = id;
}
int CBooking::getBookingID()
{
	return bookingID;
}
void CBooking::setBookingStatus(int booking_status)
{
	status = booking_status;
}
int CBooking::getBookingStatus()
{
	return status;
}
void CBooking::setRoomID(int room_id)
{
	roomID = room_id;
}
int CBooking::getRoomID()
{
	return roomID;
}

// sets multiple room IDs for this booking
void CBooking::setMultipleRoomIDs(std::vector<int> IDs)
{
	// note: IDs vector must contain the room ids of all the rooms that want to be reserved under this booking.
	int len = int(IDs.size());
	for (int i = 0; i < len; i++)
	{
		// store all room ids in the private instance variable "multipleRoomIDs" (vector)
		multipleRoomIDs.emplace_back(IDs[i]);
	}
}

// gets all the room IDs associated with this booking
std::vector<int> CBooking::getMultipleRoomIDs(void)
{
	return multipleRoomIDs;
}

void CBooking::sethotelID(int id)
{
	hotelID = id;
}
int CBooking::gethotelID()
{
	return hotelID;
}
void CBooking::setLastUpdate(std::string str)
{
	lastUpdate = str;
}
std::string CBooking::getLastUpdate()
{
	return lastUpdate;
}
void CBooking::setUserName(std::string str_name)
{
	userName = str_name;
}
std::string CBooking::getUserName()
{
	return userName;
}
void CBooking::setCustomerID(std::string strCustomerID)
{
	customerID = strCustomerID;
}
std::string CBooking::getCustomerID()
{
	return customerID;
}
//..


