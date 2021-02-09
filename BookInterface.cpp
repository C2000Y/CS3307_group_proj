#include "BookInterface.h"

#include "BookingManager.h"
#include "UserGuest.h"
#include "Room.h"
#include "Booking.h"
#include "Hotel.h"
#include "PaymentInterface.h"

#include <ctype.h>
#include <stdlib.h>

CBookingInterface::CBookingInterface()
{
	//roomOptionsMap; // initialize options map
}
CBookingInterface::~CBookingInterface()
{
}
/*
Runs the booking interface after the user has made a selection of the hotel they want
*/
bool CBookingInterface::runInterface(CBookingManager* _pBookingManager, CHotel* hotel, std::string numBedsNeeded, CUserGuest* user)
{

	int room_Size = std::stoi(numBedsNeeded);
	// create an options map with only the rooms that are avaialble and of the desired bed capacity
	roomOptionsMap = initializeRoomOptionsMap(room_Size, hotel);

	// variable to hold user's room selection
	std::string userSelectedOption;
	std::vector<std::string> userSelectedOptions;


	while (true)
	{
		//system("clear");
		// show the rooms to the user
		showRooms(roomOptionsMap);

		// get the user to select a room
		std::cout << "------------------------------------------------------------------" << std::endl;
		std::cout << "Please enter an option number to select the room you want to book: ";
		std::cin >> userSelectedOption;
		std::cout << "\n";

		if (userSelectedOption.length() > 7)
		{
			continue;
		}
		if (!(stoi(userSelectedOption) < int(roomOptionsMap.size()) && stoi(userSelectedOption) >= 0))
		{
			continue;
		}
		userSelectedOptions.emplace_back(userSelectedOption);
		std::cout << "------------------------------------------------------------------" << std::endl;
		std::cout << "Do you want to book another room? (y or n): \n";
		std::cin >> userSelectedOption;
		// check if they entered yes or no
		if (confirmRoomSelection(userSelectedOption) == true)
		{
			continue;
		}
		break;
	}



	// select the room from the optionsMap using the user input
	//CRoom* selectedRoom = selectRoom(userSelectedOption, roomOptionsMap);
	std::vector<CRoom*> selectedRooms = selectMultipleRooms(userSelectedOptions, roomOptionsMap);
	std::vector<std::string> selectedRoomIDs;

	// prepare the string that tells the user which room they picked
	std::string userRoomSelectionString = "Rooms you selected: \n";
	for (int i = 0; i<selectedRooms.size(); i++)
	{
		CRoom* selectedRoom = selectedRooms[i];
		int selectedRoomID = selectedRoom->Get_RoomNumber();
		userRoomSelectionString = userRoomSelectionString + std::to_string(selectedRoomID) + "/n";
		selectedRoomIDs.emplace_back(std::to_string(selectedRoomID));
	}
	// print the string that tells user which rooms they picked
	std::cout << userRoomSelectionString;
	// ask them if they're sure
	std::string confirmSelection;
	std::cout << "Are you sure you want to book the room(s)? Enter yes or no." << std::endl;
	std::cin >> confirmSelection;

	// if they've confirmed they want this room
	if (confirmRoomSelection(confirmSelection) == true)
	{
		// ask user to enter details and store the details in the vector in the following order: firstname, lastname, city, streetname, housenumber, telephonenumber
		std::vector<std::string> userInfoVector = getUserInfo();
		std::string username = userInfoVector[0] + userInfoVector[1]; // for now i'll use this as the username (right now the user class doesn't have a function called getUserName())
		CBooking* confirmedBooking = confirmBookingMultipleRooms(_pBookingManager, selectedRoomIDs, std::to_string(hotel->Get_HotelRegID()), selectedRooms[0]->Get_Occupant(), username);

		// add the payment for the rooms to the payment system so that the user can pay later
		/*
		CPaymentInterface* _cPaymentInterface = new CPaymentInterface();
		for (int i =0; i<selectedRooms.size(); i++)
		{
		_cPaymentInterface->addPendingPayment(hotel->Get_HotelRegID(), selectedRooms[i]->Get_RoomNumber(), selectedRooms[i]->Get_Cost());
		}
		*/

		displayMultipleRoomsBookingInfo(confirmedBooking, selectedRooms);
		displayUserInfo(userInfoVector);

		return true;
	}

	// if the user wants to make a change to the number of people staying, or the wants to change the dates of check-in/check-out
	else
	{
		renderMainMenuOptions(_pBookingManager, hotel, numBedsNeeded, user);
	}
	return false;
}

void CBookingInterface::renderMainMenuOptions(CBookingManager* _pBookingManager, CHotel* hotel, std::string numBedsNeeded, CUserGuest* user)
{
	mainMenuOptions();
	std::string selectedMenuOption;
	std::cin >> selectedMenuOption;
	if (selectedMenuOption == "1")
	{
		cleanRoomOptionsMap();
		runInterface(_pBookingManager, hotel, numBedsNeeded, user);
	}
	else if (selectedMenuOption == "2")
	{
		std::string numBedsNeeded;
		std::cout << "How many beds do you need??" << std::endl;
		std::cin >> numBedsNeeded;
		cleanRoomOptionsMap();
		runInterface(_pBookingManager, hotel, numBedsNeeded, user);
	}
	else
	{
		renderMainMenuOptions(_pBookingManager, hotel, numBedsNeeded, user);
	}
}
void CBookingInterface::cleanRoomOptionsMap()
{
	roomOptionsMap.clear();
}

void CBookingInterface::displayBookingInfo(CBooking* _pBooking, CRoom* _pRoom)
{
	system("clear");
	std::string bookingID = std::to_string(_pBooking->getBookingID());
	std::string customerID = _pBooking->getCustomerID();
	std::string roomNumber = std::to_string(_pRoom->Get_RoomNumber());
	std::string numBeds = std::to_string(_pRoom->Get_BedNumber());
	std::string cost = std::to_string(_pRoom->Get_Cost());
	std::string roomsize = std::to_string(_pRoom->Get_RoomSize());
	if (roomsize == "0") roomsize = "Small";
	if (roomsize == "1") roomsize = "Medium";
	if (roomsize == "2") roomsize = "Large";
	if (roomsize == "3") roomsize = "Huge";

	std::cout << "BOOKING DETAILS:" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Booking ID    : " + bookingID << std::endl;
	std::cout << "Customer ID   : " + customerID << std::endl;
	std::cout << "Room Number   : " + roomNumber << std::endl;
	std::cout << "Number of Beds: " + numBeds << std::endl;
	std::cout << "Room Size     : " + roomsize << std::endl;

	std::cout << "Cost of Booking: " + cost << std::endl;
	std::cout << "----------------------------------------" << std::endl;


}

void CBookingInterface::displayMultipleRoomsBookingInfo(CBooking* _pBooking, std::vector<CRoom*> _pRooms)
{
	system("clear");
	std::string bookingID = std::to_string(_pBooking->getBookingID());
	std::string customerID = _pBooking->getCustomerID();
	int cost = 0;
	//std::string roomNumber = std::to_string(_pRoom->Get_RoomNumber());

	std::cout << "BOOKING DETAILS:" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Booking ID    : " + bookingID << std::endl;
	std::cout << "Customer ID   : " + customerID << std::endl;

	for (int i = 0; i<_pRooms.size(); i++)
	{
		int roomNum = _pRooms[i]->Get_RoomNumber();
		std::string str_roomNum = std::to_string(roomNum);
		CRoom* _pRoom = _pRooms[i];

		std::string numBeds = std::to_string(_pRoom->Get_BedNumber());
		cost = cost + _pRoom->Get_Cost();
		std::string roomsize = std::to_string(_pRoom->Get_RoomSize());
		if (roomsize == "0") roomsize = "Small";
		if (roomsize == "1") roomsize = "Medium";
		if (roomsize == "2") roomsize = "Large";
		if (roomsize == "3") roomsize = "Huge";
		std::cout << "Room Number : " + str_roomNum + " | ";
		std::cout << "Number of Beds: " + numBeds + " | ";
		std::cout << "Room Size : " + roomsize << std::endl;

	}

	std::cout << "Total Cost of Booking: " + std::to_string(cost) << std::endl;
	std::cout << "----------------------------------------" << std::endl;


}

void CBookingInterface::displayUserInfo(std::vector<std::string> userInfoVector)
{
	std::string fname = userInfoVector[0];
	std::string lname = userInfoVector[1];
	std::string city = userInfoVector[2];
	std::string street = userInfoVector[3];
	std::string houseNumber = userInfoVector[4];
	std::string telephoneNumber = userInfoVector[5];

	std::cout << "USER INFO:" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Name: " + fname + " " + lname << std::endl;
	std::cout << "City: " + city << std::endl;
	std::cout << "Address: " + houseNumber + " " + street << std::endl;
	std::cout << "Telephone: " + telephoneNumber << std::endl;
	std::cout << "----------------------------------------" << std::endl;

}
std::vector<std::string> CBookingInterface::getUserInfo()
{
	system("clear");
	std::vector<std::string> userInfoVector;

	std::cout << "Enter your first name: " << std::endl;
	std::string fname;
	std::cin >> fname;
	fname = getOnlyLetters(fname);
	userInfoVector.emplace_back(fname);

	std::cout << "Enter your last name: " << std::endl;
	std::string lname;
	std::cin >> lname;
	lname = getOnlyLetters(lname);
	userInfoVector.emplace_back(lname);

	std::cout << "Enter your city of residence: " << std::endl;
	std::string city;
	std::cin >> city;
	city = getOnlyLetters(city);
	userInfoVector.emplace_back(city);

	std::cout << "Enter your street name: " << std::endl;
	std::string street;
	std::cin >> street;
	street = getOnlyLetters(city);
	userInfoVector.emplace_back(street);

	std::cout << "Enter your house/building number: " << std::endl;
	std::string houseNumber;
	std::cin >> houseNumber;
	houseNumber = getValidHouseNumber(houseNumber);
	userInfoVector.emplace_back(houseNumber);

	/*
	std::cout << "Enter your unit number (if apartment), otherwise enter 0: " << std::endl;
	std::string unitNumber;
	std::cin >> unitNumber;
	userInfoVector.emplace_back(unitNumber);
	*/
	std::string telephoneNumber = getValidTelephoneNumber();
	userInfoVector.emplace_back(telephoneNumber);

	return userInfoVector;
}


/*
Checks the user input to see if they entered a valid house number (only digits). If not, prompts them to enter a valid house number.

@param std::string str_house_num - the user input string which represents the house number
@return std::string - the valid house number
*/
std::string CBookingInterface::getValidHouseNumber(std::string str_house_num)
{
	// while the input is not only digits, get new user input (for house num) and call the checkValidHouseNum() function on it
	while (!checkValidHouseNum(str_house_num))
	{
		std::cout << "Please enter a valid house number. You can only enter digits between 0-9 : " << std::endl;
		std::cin >> str_house_num;
	}
	return str_house_num;
}

/*
Checks the user input string to determine if it is only made up of digits.

@param std::string houseNum - the user input string representing the house number
@returns true - if only digits, else false
*/
bool CBookingInterface::checkValidHouseNum(std::string houseNum)
{
	// if any character is not a digit, return false
	for (int i = 0; i < houseNum.length(); i++)
	{
		if (!(isdigit(houseNum[i])))
		{
			return false;
		}
	}
	// return true if all characters are digits
	return true;
}


/*
Checks if the user entered string is composed of only alphabetical letters, if not, gets the user to correct the input

@param std::string str_user_input - the user-inputted string occurrence that needs to be checked (for if it is only composed of alphabetical letters)
@returns std::string str_user_input - the corrected user input (only comprised of letters)
*/
std::string CBookingInterface::getOnlyLetters(std::string str_user_input)
{
	// check if the string is only letters
	bool onlyAlphabets = checkOnlyLetters(str_user_input);

	// if not only lettrs, get the user to correct their input:
	if (onlyAlphabets == false)
	{
		// get the new user input
		std::string userinput;
		std::cout << "Please enter only letters from a-z (case in-sensitive): " << std::endl;
		std::cin >> userinput;
		str_user_input = userinput;

		// while the user doesn't enter the correct input:
		while (checkOnlyLetters(userinput) == false)
		{
			// prompt the user to correct their input
			str_user_input = getOnlyLetters(userinput);
		}
	}
	return str_user_input;
}

/*
Checks if the user entered string is composed of only alphabetical letters

@param std::string str - the string occurrence that needs to be checked (for if it is only composed of alphabetical letters)
@returns true if the string is made up of only letters, else returns false
*/
bool CBookingInterface::checkOnlyLetters(std::string str)
{
	//unsigned long length = str.length();
	int length = int(str.length());

	// for all the characters in the string
	for (int i = 0; i<length; i++)
	{
		// if the character is not an alphabet then return false
		if (!(isalpha(str[i])))
		{
			return false;
		}
	}
	return true;
}

std::string CBookingInterface::getValidTelephoneNumber()
{
	std::cout << "Enter your 9 or 10 digit telephone number: " << std::endl;
	std::string telephoneNumber;
	std::cin >> telephoneNumber;
	telephoneNumber = getOnlyDigits(telephoneNumber);
	telephoneNumber = getRightLength(telephoneNumber);
	return telephoneNumber;
}

std::string CBookingInterface::getOnlyDigits(std::string str)
{
	for (int i = 0; i<str.size(); i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9')
		{
			str = getValidTelephoneNumber();
		}
	}
	return str;
}

std::string CBookingInterface::getRightLength(std::string str)
{
	std::string newTelephoneNumber = str;
	bool correctLength = true;
	if ((str.size() < 9) || (str.size() > 10))
	{
		correctLength = false;
	}
	if (correctLength == false) newTelephoneNumber = getValidTelephoneNumber();
	return newTelephoneNumber;
}

void CBookingInterface::mainMenuOptions()
{
	std::cout << "BOOKING MENU: " << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "1. SHOW ROOMS" << std::endl;
	std::cout << "2. CHANGE NUMBER OF PEOPLE STAYING" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}

bool CBookingInterface::confirmRoomSelection(std::string yes_or_no)
{
	if (yes_or_no == "yes" || yes_or_no == "y" || yes_or_no == "Yes")
	{
		return true;
	}
	else if (yes_or_no == "no" || yes_or_no == "n" || yes_or_no == "No")
	{
		return false;
	}
	else
	{
		std::cout << "Please enter yes or no" << std::endl;
		std::cin >> yes_or_no;
		return confirmRoomSelection(yes_or_no);
	}
}


CBooking* CBookingInterface::confirmBookingMultipleRooms(CBookingManager *bookingman, std::vector<std::string> room_ids, std::string hotelID, std::string customerID, std::string userName)
{
	// convert room_ids to int vector
	std::vector<int> roomIDs;
	for (int i = 0; i<room_ids.size(); i++)
	{
		int id = std::stoi(room_ids[i]);
		roomIDs.emplace_back(id);
	}
	// Create the booking
	CBooking* _pBooking = bookingman->Create_Booking_Multiple_Rooms(roomIDs, hotelID, customerID, userName);
	return _pBooking;
}

void CBookingInterface::showRooms(std::map<std::string, CRoom*> room_options_map)
{
	std::cout << "AVAILABLE ROOMS:\n" << std::endl;
	std::map<std::string, CRoom*>::iterator iter;

	for (iter = room_options_map.begin(); iter != room_options_map.end(); iter++)
	{
		std::string optionNumber = iter->first;
		CRoom* room = iter->second;

		std::string roomInfo = getRoomInfo(room);

		std::cout << optionNumber + " : | " + roomInfo << std::endl;
	}

}

CRoom* CBookingInterface::selectRoom(std::string userSelectedNumber, std::map<std::string, CRoom*> roomOptionsMap)
{
	CRoom* selectedRoom = roomOptionsMap[userSelectedNumber];
	return selectedRoom;
}


std::vector<CRoom*> CBookingInterface::selectMultipleRooms(std::vector<std::string> userSelectedNumbers, std::map<std::string, CRoom*>  roomOptionsMap)
{
	std::vector<CRoom*> selectedRooms;
	int numRoomsSelected = int(userSelectedNumbers.size());
	for (int i = 0; i < numRoomsSelected; i++)
	{
		std::string selectedRoom = userSelectedNumbers[i];
		CRoom* selectedRoomObj = roomOptionsMap[selectedRoom];
		selectedRooms.emplace_back(selectedRoomObj);
	}
	return selectedRooms;
}

std::map<std::string, CRoom*> CBookingInterface::initializeRoomOptionsMap(int numBedsNeeded, CHotel* hotel) // passed INTO showRooms()
{
	// get the rooms from the hotel
	std::vector<CRoom*>* rooms = hotel->Get_RoomVector();
	int optionsCount = 0;
	for (int i = 0; i<(*rooms).size(); i++)
	{
		int bookingStatus = (*rooms)[i]->Get_BookingStatus();
		if (bookingStatus == 0)
		{
			int num_beds = (*rooms)[i]->Get_BedNumber();
			//std::cout << "room_size: " + num_beds <<std::endl;
			//std::cout << "roomSize: " + numBedsNeeded <<std::endl;
			//if (num_beds == numBedsNeeded)
			//{
			CRoom* room = (*rooms)[i];
			std::string optionNum = std::to_string(optionsCount);
			optionsCount++;
			roomOptionsMap.insert(std::make_pair(optionNum, room));
			//}
		}
	}
	return roomOptionsMap;
}

std::string CBookingInterface::getRoomInfo(CRoom* room)  // used by ShowRooms()
{
	std::string roomNum = std::to_string(room->Get_RoomNumber());
	std::string numBeds = std::to_string(room->Get_BedNumber());
	CRoom::eROOMSIZE room_size = room->Get_RoomSize(); // TOOD: FIX THS
	std::string roomSize;
	switch (room_size) {
	case CRoom::SIZE_SMALL:
		roomSize = "Small";
		break;
	case CRoom::SIZE_MID:
		roomSize = "Medium";
		break;
	case CRoom::SIZE_BIG:
		roomSize = "Big";
		break;
	case CRoom::SIZE_HUGE:
		roomSize = "Huge";
		break;

	default:
		roomSize = "Medium";
		break;
	}

	std::string cost = std::to_string(room->Get_Cost());

	std::string roominfo = "Room Number: " + roomNum + " | " + "Number of Beds: " + numBeds + " | " + "Room Size: " + roomSize + " | " + "Room Cost: " + cost + "\n";

	return roominfo;
}



