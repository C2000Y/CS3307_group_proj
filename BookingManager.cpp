#include "BookingManager.h"
#include "Booking.h"
#include "Hotel.h"
#include "Room.h"
#include "HotelManager.h"
#include <fstream>
#include <iostream>


// DONE: constructor, destructor, Init_Manager(), Create_Booking(), Cancel_Booking(), Retreive_Booking(), SendInfo_ToHotelManager()
// Load_Bookings(), Save_Bookings(), Store_Single_Booking(), Delete_Single_Booking(), Clean_File(), Load_Single_Booking()

/*
Class constructor.
*/
CBookingManager::CBookingManager(void)
	: m_pHotelMan(NULL)
	, m_pBookingShell(NULL)
	, gBookingID(0)
	//, globalBookingNum(0)
	//, bookingManSize(0)
{
	//Load_Bookings();
}


/*
Class destructor.
*/
CBookingManager::~CBookingManager(void)
{
}

/*
Initializes the Hotel Manager using a pointer to the Hotel Manager
*/
void CBookingManager::Init_Manager(CHotelManager * _pHotelMan)
{
	m_pHotelMan = _pHotelMan;
}

/*
Creates and adds a booking to the booking manager and the booking database.
@param std::vector<int> roomIDs - the rooms booked under the booking
@param std::string hotelID - the hotel id
@param std::string customerID - the customer id
@param std::string userName - the user name of the guest who wants to make this books
*/
CBooking* CBookingManager::Create_Booking_Multiple_Rooms(std::vector<int> roomIDs, std::string hotelID, std::string customerID, std::string userName)
//vector contents example:    < '41', '42', '21' >
{
	std::vector<CBooking*> booked_rooms_vector;
	CBooking* _pBooking = new CBooking();
	_pBooking->setMultipleRoomIDs(roomIDs);
	_pBooking->setBookingStatus(1);
	_pBooking->setBookingID(gBookingID);
	_pBooking->sethotelID(std::stoi(hotelID));
	_pBooking->setCustomerID(customerID);
	_pBooking->setUserName(userName);

	std::string str_bookingID = std::to_string(gBookingID);

	// insert the booking id and booking into the map
	m_mapBookings.insert(std::make_pair(str_bookingID, _pBooking));

	// store the booking in the booking database
	Store_Single_Booking_Multiple_Rooms(_pBooking);

	// send the info to the hotel manager to occupy the room at the hotel where the booking was made
	SendInfo_ToHotelmanager_MultipleRooms(_pBooking->getMultipleRoomIDs(), _pBooking->gethotelID(), _pBooking->getUserName(), "reserved"); // let the hotel manager know

	gBookingID++;
	return _pBooking;
	//return booked_rooms_vector;
}

/*
Cancels a booking. Requires the bookingID in string format as a parameter.
@param std::string _strBookingID - the booking id of the the booking that we want to cancel
*/
void CBookingManager::Cancel_Booking_Multiple_Rooms(std::string _strBookingID)
{
	CBooking *_pBooking = Retrieve_Booking(_strBookingID);
	// remove the booking from the map if it exists
	if (_pBooking != NULL)
	{
		// get the hotel id, room id, and username
		int hotelID = _pBooking->gethotelID();
		std::vector<int> roomIDs = _pBooking->getMultipleRoomIDs();
		std::string username = _pBooking->getUserName();

		//delete m_mapBookings[_strBookingID]; // to free up memory....is this correct???

		// send the info to the hotel manager to unoccupy the room at the hotel where the booking was made
		SendInfo_ToHotelmanager_MultipleRooms(roomIDs, hotelID, username, "cancelled"); // let the hotel manager know the booking is cancelled
																						// delete the booking from the booking database
		Delete_Single_Booking(_strBookingID);
	}
}

/*
Returns a booking object from the bookings map
@param std::string - the booking id of the booking object we're trying to retrieve

*/
CBooking* CBookingManager::Retrieve_Booking(std::string _strBookingID)
{
	CBooking *_pBooking = m_mapBookings[_strBookingID];
	return _pBooking;
}

/*
Loads all bookings from the booking database into the bookings map
*/
void CBookingManager::Load_Bookings()
{

	std::string line = "";
	std::ifstream _fp("BookingDatabase.txt");

	//open file
	if (_fp.is_open())
	{
		// for each line in the file
		while (std::getline(_fp, line))
		{
			std::cout << line << '\n';


			// get booking id
			std::string bookingID = "";
			Tokenize_Comma(&_fp, &bookingID);
			std::cout << "BookingID: " + bookingID << std::endl;
			// get hotel id
			std::string hotelID = "";
			Tokenize_Comma(&_fp, &hotelID);
			std::cout << "HotelID: " + hotelID << std::endl;

			// get number of rooms
			std::string numRooms = "";
			Tokenize_Comma(&_fp, &numRooms);
			std::cout << "Num Rooms: " + numRooms << std::endl;
			int numberOfRooms = std::stoi(numRooms);

			// create room id vector
			std::vector<int> roomsIDs;
			std::string res = "";
			for (int i = 0; i<numberOfRooms; i++)
			{

				Tokenize_Comma(&_fp, &res);
				roomsIDs.emplace_back(std::stoi(res));
				std::cout << "Room ID: " + res << std::endl;
				res = "";
			}

			std::string customerID = "";
			Tokenize_Comma(&_fp, &customerID);
			std::string username = "";
			Tokenize_Comma(&_fp, &username);
			std::string bookingStatus = "";
			Tokenize_Comma(&_fp, &bookingStatus);

			// create booking object
			CBooking* _pBooking = new CBooking();
			_pBooking->setBookingID(std::stoi(bookingID));
			_pBooking->sethotelID(std::stoi(hotelID));
			_pBooking->setMultipleRoomIDs(roomsIDs);
			_pBooking->setUserName(username);
			_pBooking->setCustomerID(customerID);
			_pBooking->setBookingStatus(std::stoi(bookingStatus));

			//_pBooking->setNumPeople(<#int#>)
			m_mapBookings.insert(std::make_pair(bookingID, _pBooking));


		}

		_fp.close(); // when done close fp
		_fp.clear();

	}
}

/*
Saves all the bookings from the bookings map into the booking database file
*/

void CBookingManager::Save_Bookings()
{

	std::map<std::string, CBooking*> bookings = m_mapBookings;

	// clear all data from the file using Clean_Booking_File()
	Clean_Booking_File();


	std::map<std::string, CBooking*>::iterator iter;

	// for each element in the bookings map
	for (iter = bookings.begin(); iter != bookings.end(); iter++)
	{
		// get the booking id
		std::string str_bookingID = iter->first;
		CBooking* _pBooking = iter->second;
		// store a string representation of this booking in the booking database file
		Store_Single_Booking_Multiple_Rooms(_pBooking);
	}

}


/*
Deletes the specified booking from the booking database file.
*/
void CBookingManager::Delete_Single_Booking(std::string _strBookingID)
{
	std::string line = "";
	// for all the lines in the file: **
	std::ifstream *_fp = new std::ifstream();
	_fp->open("BookingDatabase.txt");

	// get the first word of each line (note the first word of each line represents the booking id)
	while (*(_fp) >> line)
	{

		std::string idInFile = "";
		Tokenize_Comma(_fp, &idInFile);
		// if the token is equal to _strBookingID: **
		if (idInFile == _strBookingID)
		{
			// make the room unoccupied? if so how? **
			m_mapBookings.erase(_strBookingID);
			Clean_Booking_File(); //clear the booking file
			Save_Bookings(); // save the updated (post-deletion) bookings map into the file
		}

	}

	_fp->close(); // when done close fp
	_fp->clear();

	delete _fp;

	return;
}

/*
Stores a single booking in the database given a pointer to the booking object as a parameter
*/
void CBookingManager::Store_Single_Booking_Multiple_Rooms(CBooking* _pBooking)
{
	// get the booking information and convert it to string format
	int bookingID = _pBooking->getBookingID();
	std::string booking_id = std::to_string(bookingID);
	int hotelID = _pBooking->gethotelID();
	std::string hotel_id = std::to_string(hotelID);
	std::vector<int> multipleRooms = _pBooking->getMultipleRoomIDs();
	std::string room_id_string = "";
	int numRooms = int(multipleRooms.size());
	// room ids should be stored in the following format in the booking database file: ....numRooms, room1, room2, .....
	for (int i = 0; i < numRooms; i++)
	{
		std::string id = std::to_string(multipleRooms[i]);
		room_id_string = room_id_string + id + ",";

	}
	std::string customerID = _pBooking->getCustomerID();
	std::string customer_id = customerID;
	std::string username = _pBooking->getUserName();
	int bookingStatus = _pBooking->getBookingStatus();
	std::string booking_status = std::to_string(bookingStatus);

	// store the booking information as a single, comma-separated string
	std::string strToken = "";
	strToken = booking_id + "," + hotel_id + "," + std::to_string(numRooms) + "," + room_id_string + "," + customer_id + "," + username + "," + booking_status + "\n";

	// open the booking database file and go to the first empty space in the file (would be at the bottom of the file if the file is already filled)
	std::string file_name = "BookingDatabase.txt";
	std::ofstream bookingFile(file_name, std::ios::app);
	if (!bookingFile.is_open())
	{
		std::cout << "Error. Could not open " + file_name + "\n" << std::endl;
	}
	// if the file opened, then
	else
	{
		//write the string to the file
		bookingFile << strToken;
		//close the file
		bookingFile.close();
		//bookingFile.clear();
	}

	return;
}


/*
Deletes all data from the booking database file
*/
void CBookingManager::Clean_Booking_File()
{
	// delete all the text in the BookingDatase **
	std::ofstream file;
	file.open("BookingDatabase.txt", std::ofstream::out | std::ofstream::trunc);
	file.close();
	return;
}

/*
Gets the hotel manager to update the occupancy details of the room that was booked or cancelled by the booking manager.
*/
void CBookingManager::SendInfo_ToHotelmanager_MultipleRooms(std::vector<int> roomIDs, int hotelID, std::string username, std::string command)
{
	std::string hotel_id = std::to_string(hotelID);
	CHotel* hotel = m_pHotelMan->Find_Hotel(hotel_id);
	std::vector<CRoom*>* rooms = hotel->Get_RoomVector();

	// find the room in the hotel
	for (int i = 0; i < (*rooms).size(); i++)
	{
		int room_id = (*(rooms))[i]->Get_RoomNumber();
		if (Find_RoomID_In_Vector(room_id, roomIDs) == true) // if the room in the hotel is contained in our rooms vector for the booking:
		{
			if (command == "reserved") // if we want to reserve the room
			{
				(*(rooms))[i]->Set_BookingStatus(1); // set booking status to 1 (in other words, the room is booked)
				(*(rooms))[i]->Set_Occupant(username); // set occupant
			}
			else if (command == "cancelled") // if we want to cancel the room
			{
				(*(rooms))[i]->Set_BookingStatus(0); // set booking status to 0 (in other words, the room is un-booked)
				(*(rooms))[i]->Set_Occupant(""); // set occupant to no one
			}
			else {}
		}
	}
}

bool CBookingManager::Find_RoomID_In_Vector(int id, std::vector<int> roomIDs)
{
	bool contained = false;
	contained = std::find(roomIDs.begin(), roomIDs.end(), id) != roomIDs.end(); // true if the id is present in the vector
	return contained;
}

void CBookingManager::Tokenize_Comma(std::ifstream* _fp, std::string* _strToken)
{
	char chGet = '\0';
	*_strToken = ""; // reset per new
	while (true)
	{
		_fp->get(chGet);
		if (EOF == chGet || '\n' == chGet) // if commna got end
		{
			std::cout << "ERROR while tokenizing... file has reached end of file or has met newline" << std::endl;
			break;
		}
		if (',' == chGet) // if commna got end
		{
			break;
		}
		// if not a comma then continue concatinating
		*_strToken += chGet;
	}
}



