#include "PartnerAddListInterface.h"

#include "Room.h"
#include "Hotel.h"
#include "HotelSpecContainer.h"
#include "HotelManager.h"
#include "HotelSearchInterface.h"


using namespace std;

CPartnerAddListInterface::CPartnerAddListInterface(CHotelManager* _pHotelManager)
	: m_pHotelManager(_pHotelManager)
	, m_strLocation("none")
	, m_strUserInput("")
	, m_iPageNum(0)
	, m_iIndexForPage(0)
	, m_eEnter(MODE_END)
	, price{ 0,0,0,0 }
	, m_numRoom{ 0,0,0,0 }
	, parkingspot(0)
	, HotelName("none")
	, HotelID(0)
	, SmokeFriendly(false)
	, PetFriendly(false)
	, rating(0)
{
	if (nullptr != _pHotelManager)
	{
		m_pHotelManager = _pHotelManager;
	}
}

CPartnerAddListInterface::~CPartnerAddListInterface() {}

/**
* display the main menu for the hotel listing interface
*/
void CPartnerAddListInterface::Show_Display(void)
{
	system("clear");
	std::cout << "*******************************************************************" << endl;
	std::cout << "*********************** Hotel Management **************************" << endl;
	std::cout << endl;
	std::cout << "                     [1] Create a Hotel" << endl;
	std::cout << "                     [2] Edit an Existing Hotel" << endl;
	std::cout << "                     [3] View all Hotels " << endl;
	std::cout << "                     [4] Back to the Last Page " << endl;
	std::cout << endl;
	std::cout << "*******************************************************************" << endl;
	std::cout << "*******************************************************************" << endl;
}

/**
* help the user select from the main menu, allow them to create list, edit list and view the list, return false when the user wish to quit
* @param a PartnerID an integer argument
*/
bool CPartnerAddListInterface::Run_Interface(int PartnerID)
{
	while (true)
	{
		Show_Display();
		if (!Prompt_User(1, 4))
		{
			continue;
		}
		switch (stoi(m_strUserInput))
		{
		case eMAINMENU::OPT_ADDLIST:
			Menu_createList(PartnerID);
			break;
		case eMAINMENU::OPT_UPDATELIST:
			Menu_updateList(PartnerID);
			break;
		case eMAINMENU::OPT_ViewList:
			Menu_viewList(PartnerID);
			break;
		case eMAINMENU::OPT_EXIT:
			return false;
		default:
			std::cout << "Error" << endl;
			system("pause");
			break;
		}
	}
	return false;
}

/**
* Createlist menu is here for the users to create hotel, the user has to enter every element of the hotel before make the creation
* @param a PartnerID an integer argument
*/
void CPartnerAddListInterface::Menu_createList(int ParnertID) {
	while (true) {
		system("clear");
		std::cout << "********************************************************************" << endl;
		std::cout << "***********************  Create a Hotel  ***************************" << endl;
		std::cout << "                                                                    " << endl;
		std::cout << "                      [1] Enter Hotel Name                          " << endl;
		std::cout << "                      [2] Choose Location                           " << endl;
		std::cout << "                      [3] Edit Rooms                                " << endl;
		std::cout << "                      [4] Edit Prices                               " << endl;
		std::cout << "                      [5] Edit Parking spot                         " << endl;
		std::cout << "                      [6] Confirm                                   " << endl;
		std::cout << "                                                                    " << endl;
		std::cout << "********************************************************************" << endl;
		std::cout << "---------------------   Hotel Information   ------------------------" << endl;
		std::cout << "\t\t Hotel Name\t==>";
		std::cout << HotelName << endl;
		std::cout << "\t\t Location\t==>";
		std::cout << m_strLocation << endl;
		std::cout << "\t\t Total  Rooms\t==>";
		if (!hasroom()) { std::cout << "0" << endl; }
		else {
			std::cout << totalrooms();
			std::cout << " room(s)" << endl;
			for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
				if (m_numRoom[i] != 0) {
					std::cout << "\tCost of ";
					SizetoString(i + 1);
					std::cout << "room\t=> $" << setprecision(2) << fixed << price[i] << endl;
				}
			}
		}
		std::cout << "\t\tParking Spot\t==>";
		std::cout << parkingspot << endl;
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "********************************************************************" << endl;
		if (!Prompt_User(1, 6))
		{
			continue;
		}
		switch (stoi(m_strUserInput))
		{
		case 1:
		{
			system("clear");
			Menu_HotelName();
			break;
		}
		case 2:
		{
			system("clear");
			Menu_Location();
			break;
		}
		case 3:
		{
			system("clear");
			Menu_addRoom();
			break;
		}
		case 4:
		{
			system("clear");
			Menu_EditPrice();
			break;
		}
		case 5:
		{
			Menu_Parkingspot();
			break;
		}
		case 6:
		{

			if (HotelName != "none" && m_strLocation != "none" && hasroom() && ifroomhasprice()) {
			}
			else { break; }
			bool back = false;
			PetFriendly = false;
			SmokeFriendly = false;
			while (true) {
				system("clear");
				std::cout << "********************************************************************" << endl;
				std::cout << "************************* Hotel Policy *****************************" << endl;
				std::cout << "                # v means allow, x means not allow#" << endl;
				std::cout << endl;
				std::cout << "                      1.Allow pet      [";
				if (PetFriendly) std::cout << "v"; else std::cout << "x";
				std::cout << "]" << endl;
				std::cout << "                      2.Allow Smoking  [";
				if (SmokeFriendly) std::cout << "v"; else std::cout << "x";
				std::cout << "]" << endl;
				std::cout << "                      3.Confirm" << endl;
				std::cout << "                      4.Back" << endl;
				std::cout << "********************************************************************" << endl;
				std::cout << "********************************************************************" << endl;
				if (!Prompt_User(1, 4)) continue;
				switch (stoi(m_strUserInput)) {
				case 1:
					PetFriendly = true;
					break;
				case 2:
					SmokeFriendly = true;
					break;
				case 3:
					back = false;
					break;
				case 4:
					back = true;
					break;
				}
				if (stoi(m_strUserInput) == 3 || stoi(m_strUserInput) == 4) {
					break;
				}
			}
			if (back) break;
			system("clear");
			std::cout << "********************************************************************" << endl;
			std::cout << "--------------------------Confirm Page-------------------------" << endl;
			std::cout << "-----------Please make sure you have the right input-----------" << endl;
			std::cout << "\t\t Hotel Name\t==>";
			std::cout << HotelName << endl;
			std::cout << "\t\t Location\t==>";
			std::cout << m_strLocation << endl;
			std::cout << "\t\t Total  Rooms\t==>";
			if (!hasroom()) { std::cout << "0" << endl; }
			else {
				std::cout << totalrooms();
				std::cout << " room(s)" << endl;
				for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
					if (m_numRoom[i] != 0) {
						std::cout << "\tCost of ";
						SizetoString(i + 1);
						std::cout << "room\t=> $" << setprecision(2) << fixed << price[i] << endl;
					}
				}
			}
			std::cout << "\t\tParking Spot\t==>";
			std::cout << parkingspot << endl;
			std::cout << "\t\tAllow Pet\t==>";
			if (PetFriendly) std::cout << "Yes" << endl; else std::cout << "No" << endl;
			std::cout << "\t\tAllow Smoking\t==>";
			if (SmokeFriendly) std::cout << "Yes" << endl; else std::cout << "No" << endl;
			std::cout << "--------------------------------------------------------------------" << endl;
			std::cout << "********************************************************************" << endl;
			std::cout << "----                1. Finish Creating the Hotel            --------" << endl;
			std::cout << "-----                2. Back to Edit                         -------" << endl;
			std::cout << "--------------------------------------------------------------------" << endl;
			if (!Prompt_User(1, 2))
			{
				continue;
			}
			if (stoi(m_strUserInput) == 2) {
				break;
			}
			else {
				//*************
				//Write to file 
				SaveCreation(ParnertID);
				ResetVariable();
				return;
			}
		}
		}
	}
}

/**
* Sub menu for the user to change the name variable
*/
void CPartnerAddListInterface::Menu_HotelName() {
	while (true) {
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "---             Enter the Name of the Hotel :               --------" << endl;
		std::cout << "--------------------------------------------------------------------" << endl;
		cin >> m_strUserInput;
		if (!hascomma(m_strUserInput) && m_strUserInput.size() < 100) {
			HotelName = m_strUserInput;
			break;
		}
		else {
			system("clear");
			std::cout << "Input cannot be comma and must be less than 100 characters" << endl;
		}
	}
}

/**
* Sub menu for the user to change the location variable
*/
void CPartnerAddListInterface::Menu_Location(void) {
	int iIndex = 1;
	m_iPageNum = 0;
	while (true)
	{
		iIndex = 1;
		system("clear");
		std::cout << "-------------------------------------------------------------------" << endl;
		std::cout << "                                             Page "; N_Format(m_iPageNum + 1); std::cout << " of " << int(m_vecCities2.size() / LIST_PER_PAGE) << endl;
		std::cout << "-------------------------------------------------------------------" << endl;
		for (int i = 0 + (m_iPageNum * LIST_PER_PAGE); i < ((m_iPageNum * LIST_PER_PAGE) + LIST_PER_PAGE); ++i)
		{
			std::cout << "--------\t"; N_Format(iIndex++); std::cout << ".\t" << m_vecCities2[i] << endl;
		}
		std::cout << "-------------------------------------------------------------------" << endl;
		if (m_iPageNum > 0)
		{
			std::cout << "        " << "16. Prev Page" << endl;
		}
		else
		{
			std::cout << endl;
		}
		if (m_iPageNum < 9)
		{
			std::cout << "        " << "17. Next Page" << endl;
		}
		else
		{
			std::cout << endl;
		}
		std::cout << "        " << "18. Go Back" << endl;
		std::cout << "-------------------------------------------------------------------" << endl;

		if (!Prompt_User(1, LOC_BACK))
		{
			continue;
		}

		switch (stoi(m_strUserInput))
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			m_strLocation = m_vecCities2[stoi(m_strUserInput) + (m_iPageNum * LIST_PER_PAGE) - 1];
			return;
		case LOC_PREV:
			if (m_iPageNum == 0)
			{
				continue;
			}
			else
			{
				m_iPageNum--; // prev page
			}
			break;
		case LOC_NEXT:
			if (m_iPageNum == 9)
			{
				continue;
			}
			else
			{
				m_iPageNum++; // next page
			}
			break;
		case LOC_BACK:
			return;
		default:
			break;
		}
	}
}

/**
* Sub menu for the user to add rooms, they can choose small,medium,big,huge size and number of each size
*/
void CPartnerAddListInterface::Menu_addRoom(void) {
	while (true) {
		system("clear");
		std::cout << "********************************************************************" << endl;
		std::cout << "********************************************************************" << endl;
		std::cout << "                           Add New Type					         " << endl;
		std::cout << "                                                                    " << endl;
		std::cout << "                          [1] Size SMALL                            " << endl;
		std::cout << "                          [2] Size MEDIUM                           " << endl;
		std::cout << "                          [3] Size BIG                              " << endl;
		std::cout << "                          [4] Size HUGE                             " << endl;
		std::cout << "                          [5] BACK                                  " << endl;
		std::cout << "********************************************************************" << endl;
		std::cout << "--------------------------    ROOM LIST  ---------------------------" << endl;
		std::cout << "\t\t\tTotal Rooms\t==>";
		if (hasroom()) {
			std::cout << totalrooms();
			std::cout << " Room(s)" << endl;
			std::cout << endl;
			for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
				if (m_numRoom[i] != 0) {
					std::cout << "\t\t\t-";
					SizetoString(i + 1);
					std::cout << "rooms\t==>" << m_numRoom[i] << " room(s)" << endl;
				}
			}
		}
		else {
			std::cout << "0" << endl;
		}
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "********************************************************************" << endl;
		if (!Prompt_User(1, 5)) {
			continue;
		}
		int input = stoi(m_strUserInput);
		if (input == 5) break;
		while (input < 5 && input>0) {
			system("clear");
			std::cout << "********************************************************************" << endl;
			std::cout << "********************************************************************" << endl;
			std::cout << "                                                                    " << endl;
			std::cout << "               Enter the Number of ";
			SizetoString(stoi(m_strUserInput));
			std::cout << "Room";
			std::cout << "                                                                    " << endl;
			std::cout << "********************************************************************" << endl;
			if (!Prompt_User(1, 99999)) {
				continue;
			}
			signtoarr(m_numRoom, input, stoi(m_strUserInput));
			break;
		}
	}
}

/**
* Sub menu for the user to change the number of parkingspots
*/
void CPartnerAddListInterface::Menu_Parkingspot(void) {
	while (true) {
		system("clear");
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "---             Enter number of Parking spots:              --------" << endl;
		std::cout << "--------------------------------------------------------------------" << endl;
		if (!Prompt_User(0, 99999))
		{
			continue;
		}
		parkingspot = stoi(m_strUserInput);
		break;
	}
}

/**
* Updatelist menu allows users to change the element in an existing hotel
* @param a PartnerID an integer argument
*/
void CPartnerAddListInterface::Menu_updateList(int PartnerID) {
	bool update = true;
	Menu_SelectList(PartnerID);
	if (m_vecHotelID.size() == 0) update = false;
	if (m_strUserInput == "8") update = false;
	GetAllHotelElement(PartnerID, HOTELFILE, HotelID);
	while (update) {
		system("clear");
		std::cout << "*********************************************************************" << endl;
		std::cout << "*********************************************************************" << endl;
		std::cout << endl;
		std::cout << "\t\t\t[0]\t*Delete Hotel*" << endl;
		std::cout << "\t\t\t[1]\tEnter Hotel Name" << endl;
		std::cout << "\t\t\t[2]\tChoose Location" << endl;
		std::cout << "\t\t\t[3]\tEdit Rooms" << endl;
		std::cout << "\t\t\t[4]\tEdit Parking Spot" << endl;
		std::cout << "\t\t\t[5]\tEdit Price" << endl;
		std::cout << "\t\t\t[6]\tEdit Rule" << endl;
		std::cout << "\t\t\t[7]\t*Confirm*" << endl;
		std::cout << endl;
		std::cout << "*********************************************************************" << endl;
		std::cout << "*********************************************************************" << endl;
		std::cout << "\t\t Hotel Name\t==>";
		std::cout << HotelName << endl;
		std::cout << "\t\t Location\t==>";
		std::cout << m_strLocation << endl;
		std::cout << "\t\t Total  Rooms\t==>";
		if (!hasroom()) { std::cout << "0" << endl; }
		else {
			std::cout << totalrooms();
			std::cout << " room(s)" << endl;
			for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
				if (m_numRoom[i] != 0) {
					std::cout << "\tCost of ";
					SizetoString(i + 1);
					std::cout << "room\t=> $" << setprecision(2) << fixed << price[i] << endl;
				}
			}
		}
		std::cout << "\t\tParking Spot\t==>";
		std::cout << parkingspot << endl;
		std::cout << "\t\tPet ";
		if (PetFriendly) std::cout << "Allowed"; else std::cout << "Not Allowed";
		std::cout << "\t\tSmoking ";
		if (SmokeFriendly) std::cout << "Allowed" << endl; else std::cout << "Not Allowed" << endl;
		std::cout << "--------------------------------------------------------------------" << endl;
		std::cout << "********************************************************************" << endl;
		if (!Prompt_User(0, 7))
		{
			continue;
		}
		switch (stoi(m_strUserInput))
		{
		case 0:
			system("clear");
			std::cout << "*********************************************************************" << endl;
			std::cout << "*********************************************************************" << endl;
			std::cout << "                                                                     " << endl;
			std::cout << "           Are you sure you want to remove this hotel?               " << endl;
			std::cout << "                                                                     " << endl;
			std::cout << "               1.YES					2.NO                           " << endl;
			std::cout << "                                                                     " << endl;
			std::cout << "*********************************************************************" << endl;
			std::cout << "*********************************************************************" << endl;
			if (!Prompt_User(1, 2)) continue;
			if (m_strUserInput == "1") {
				DeleteHotel(PartnerID, HotelID, HOTELFILE);
				ResetVariable();
				update = false;
				break;
			}
			else break;
		case 1:
			system("clear");
			Menu_HotelName(); /** change hotel name */
			m_pHotelManager->Partner_ChangeHotelName(PartnerID, HotelID, HotelName);
			break;
		case 2:
			system("clear");
			Menu_Location(); /** change location */
			m_pHotelManager->Partner_ChangeLocation(PartnerID, HotelID, m_strLocation);
			break;
		case 3:
			system("clear");
			Menu_addRoom(); /** change room */
			m_pHotelManager->Partner_ChangeRooms(PartnerID, HotelID,
				m_numRoom[0], m_numRoom[1], m_numRoom[2], m_numRoom[3],
				price[0], price[1], price[2], price[3],
				PetFriendly, SmokeFriendly);
			break;
		case 4:
			Menu_Parkingspot();
			break;
		case 5:
			Menu_EditPrice();
			m_pHotelManager->Partner_ChangePrice(PartnerID, HotelID,
				price[0], price[1], price[2], price[3]);
			break;
		case 6: /** edit room */
			PetFriendly = false;
			SmokeFriendly = false;
			m_pHotelManager->Partner_ChangePet(PartnerID, HotelID, PetFriendly);
			m_pHotelManager->Partner_ChangeSmoke(PartnerID, HotelID, SmokeFriendly);
			while (true) {
				system("clear");
				std::cout << "********************************************************************" << endl;
				std::cout << "************************* Hotel Policy *****************************" << endl;
				std::cout << "                # v means allow, x means not allow#" << endl;
				std::cout << endl;
				std::cout << "                      1.Allow pet      [";
				if (PetFriendly) std::cout << "v"; else std::cout << "x";
				std::cout << "]" << endl;
				std::cout << "                      2.Allow Smoking  [";
				if (SmokeFriendly) std::cout << "v"; else std::cout << "x";
				std::cout << "]" << endl;
				std::cout << "                      3.Confirm" << endl;
				std::cout << "********************************************************************" << endl;
				std::cout << "********************************************************************" << endl;
				if (!Prompt_User(1, 3)) continue;
				switch (stoi(m_strUserInput)) {
				case 1:
					PetFriendly = true;
					m_pHotelManager->Partner_ChangePet(PartnerID, HotelID, PetFriendly);
					break;
				case 2:
					SmokeFriendly = true;
					m_pHotelManager->Partner_ChangeSmoke(PartnerID, HotelID, SmokeFriendly);
					break;
				case 3:
					break;
				}
				if (stoi(m_strUserInput) == 3) break;
			}
			break;
		case 7:
			if (HotelName != "none" && m_strLocation != "none" && hasroom() && ifroomhasprice()) {
				SaveEdition(PartnerID);
				ResetVariable();
				update = false;
			}
			else break;
		default:
			break;
		}
	}

}

/**
* a sub menu that allows the user to select one of the hotels they own
* @param a PartnerID an integer argument
*/
void CPartnerAddListInterface::Menu_SelectList(int PartnerID) {
	createHotelList(PartnerID, HOTELFILE);
	m_iPageNum = 0;
	int iIndex = 1, size = m_vecHotelID.size();
	while (true)
	{
		system("clear");
		iIndex = 1;
		std::cout << "-------------------------------------------------------------------" << endl;
		std::cout << "                                             Page "; N_Format(m_iPageNum + 1); std::cout << " of " << ceil(double(size) / double(HOTEL_PER_PAGE)) << endl;
		std::cout << "-------------------------------------------------------------------" << endl;
		for (int i = 0 + (m_iPageNum * HOTEL_PER_PAGE); i < ((m_iPageNum * HOTEL_PER_PAGE) + HOTEL_PER_PAGE); ++i)
		{
			if (i < size) {
				std::cout << "--------\t"; N_Format(iIndex++); std::cout << ".\tHotel: " << m_vecHotelName[i] << endl;
				std::cout << "--------\t\tID: " << m_vecHotelID[i] << "\tLocation: " << m_vecHotelLocation[i] << endl;
				std::cout << endl;
			}
			else break;
		}
		std::cout << "-------------------------------------------------------------------" << endl;
		if (m_iPageNum > 0 && (m_iPageNum + 1) * HOTEL_PER_PAGE > size)
		{
			std::cout << "        ";
			std::cout << (size % HOTEL_PER_PAGE) + 1;
			std::cout << ". Prev Page" << endl;
		}
		else if (m_iPageNum > 0)
		{
			std::cout << "        " << "6. Prev Page" << endl;
		}
		else {
			std::cout << endl;
		}

		if (m_iPageNum < ceil(double(size) / double(HOTEL_PER_PAGE)) - 1)
		{
			std::cout << "        " << "7. Next Page" << endl;
		}
		else
		{
			std::cout << endl;
		}
		if (m_iPageNum >= 0 && (m_iPageNum + 1) * HOTEL_PER_PAGE > size)
		{
			std::cout << "        ";
			std::cout << (size % HOTEL_PER_PAGE) + 2;
			std::cout << ". Go Back" << endl;
		}
		else {
			std::cout << "        " << "8. Go Back" << endl;
		}
		std::cout << "-------------------------------------------------------------------" << endl;

		if (!Prompt_User(1, 8)) continue;
		if ((m_iPageNum + 1) * HOTEL_PER_PAGE > size && stoi(m_strUserInput) > (size % HOTEL_PER_PAGE) + 2) continue;


		if ((m_iPageNum == ceil(double(size) / double(HOTEL_PER_PAGE)) - 1) && (m_iPageNum + 1) * HOTEL_PER_PAGE > size)
		{
			if (stoi(m_strUserInput) == (size % HOTEL_PER_PAGE) + 1)
				m_strUserInput = "6";
			else if (stoi(m_strUserInput) == (size % HOTEL_PER_PAGE) + 2)
				m_strUserInput = "8";
		}
		int idx = stoi(m_strUserInput) + (m_iPageNum * HOTEL_PER_PAGE) - 1;
		switch (stoi(m_strUserInput))
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			if (idx < size)
				HotelID = m_vecHotelID[idx];
			return;
		case 6:
			if (m_iPageNum == 0)
			{
				continue;
			}
			else
			{
				m_iPageNum--; /** prev page */
			}
			break;
		case 7:
			if (m_iPageNum == ceil(double(size) / double(HOTEL_PER_PAGE)) - 1)
			{
				continue;
			}
			else
			{
				m_iPageNum++; /** next page */
			}
			break;
		case 8:
			return;
		default:
			break;
		}
	}

}

/**
* View List menu allows user to take a look of the information of a hotel and the booking status of it
* @param a PartnerID an integer argument
*/
void CPartnerAddListInterface::Menu_viewList(int PartnerID) {
	bool loop = true;
	Menu_SelectList(PartnerID);
	if (m_vecHotelID.size() == 0) loop = false;
	if (m_strUserInput == "8") loop = false;
	GetAllHotelElement(PartnerID, HOTELFILE, HotelID);
	while (loop) {
		system("clear");
		std::cout << "*********************************************************************" << endl;
		std::cout << "*************************  Hotel Status  ****************************" << endl;
		std::cout << "\t\t  Hotel ID        \t==> ";
		std::cout << HotelID << endl;
		std::cout << "\t\t  Hotel Name      \t==> ";
		std::cout << HotelName << endl;
		std::cout << "\t\t  Location        \t==> ";
		std::cout << m_strLocation << endl;;
		std::cout << "\t\tBooked Rooms      \t==> ";
		if (!hasroom()) std::cout << "0" << endl;
		else {
			std::cout << "0 /";/** booked room */
			std::cout << totalrooms();
			std::cout << " room(s)" << endl;
			for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
				if (m_numRoom[i] != 0) {
					std::cout << "\t\t--";
					SizetoString(i + 1);
					std::cout << "rooms\t\t==> ";
					std::cout << "0";
					std::cout << " /" << m_numRoom[i] << " room(s)" << endl;
				}
			}
		}

		for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
			if (m_numRoom[i] != 0) {
				std::cout << "\t\tCost of ";
				SizetoString(i + 1);
				std::cout << "room\t=> $" << setprecision(2) << fixed << price[i] << endl;
			}
		}
		std::cout << "\t\tParking Spot Using\t==> ";
		std::cout << "0 /";
		std::cout << parkingspot << endl;
		std::cout << "\t\tPet ";
		if (PetFriendly) std::cout << "Allowed"; else std::cout << "Not Allowed";
		std::cout << "\t\tSmoking ";
		if (SmokeFriendly) std::cout << "Allowed" << endl; else std::cout << "Not Allowed" << endl;
		std::cout << "\t\tRating:\t";
		if (rating == 0) std::cout << "not avaliable" << endl; else std::cout << "==>" << rating << endl;
		std::cout << "*********************************************************************" << endl;
		std::cout << "*********************************************************************" << endl;
		std::cout << "                            0.exit                                   " << endl;
		std::cout << "---------------------------------------------------------------------" << endl;
		cin >> m_strUserInput;
		if (stoi(m_strUserInput) != 0) {
			continue;
		}
		else {
			ResetVariable();
			break;
		}
	}
}

/**
* sub menu that allows the user to change the price of the room
*/
void CPartnerAddListInterface::Menu_EditPrice() {

	//Enter price of each size of hotel
	int sizenum = 0;
	while (sizenum < NUM_OF_ROOMSIZE) {
		if (m_numRoom[sizenum] != 0) {
			system("clear");
			std::cout << "--------------------------------------------------------------------" << endl;
			std::cout << "--------------------------------------------------------------------" << endl;
			std::cout << "--------------------------------------------------------------------" << endl;
			std::cout << "                Enter the Price of ";
			SizetoString(sizenum + 1);
			std::cout << "Size Room:             " << endl;
			std::cout << "--------------------------------------------------------------------" << endl;
			if (!FPrompt_User(1.00, 99999.00))
			{
				continue;
			}
			price[sizenum] = stof(m_strUserInput);
		}
		sizenum++;
	}
}


/**=====================================useful helper functions======================================*/

/**
* return an integer of the sum room number
*/
int CPartnerAddListInterface::totalrooms() {
	int Total = 0;
	for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
		Total += m_numRoom[i];
	}
	return Total;
}

/**
* return true if the partner enters rooms during creation
*/
bool CPartnerAddListInterface::hasroom() {
	for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
		if (m_numRoom[i] != 0)
			return true;
	}
	return false;
}

/**
* Save every element that is changed after confirm editing
* @param a PartnerID an integer argument
*/
void CPartnerAddListInterface::SaveEdition(int PartnerID) {
	string lineStr, wordStr, input, strHotelID;
	vector<string> line;
	ifstream HotelListFile(HOTELFILE, ios::in);
	int line_index = 0;
	while (getline(HotelListFile, lineStr)) {
		stringstream Str(lineStr);
		if (getline(Str, wordStr, ',') && stoi(wordStr) == PartnerID) {
			getline(Str, wordStr, ',');
			if (stoi(wordStr.c_str()) == HotelID) {
				break;
			}
		}
		line.push_back(lineStr);
		line_index++;
	}
	input = to_string(PartnerID) + "," + to_string(HotelID) + "," + m_strLocation + "," + HotelName + ",";
	for (int room = 0; room < NUM_OF_ROOMSIZE; room++) {
		input += (to_string(m_numRoom[room]) + ",");
	}
	for (int pricenum = 0; pricenum < NUM_OF_ROOMSIZE; pricenum++) {
		input += (to_string(price[pricenum]) + ",");
	}
	input += to_string(parkingspot) + ",";
	if (PetFriendly) input += "1,"; else input += "0,";
	if (SmokeFriendly) input += "1,"; else input += "0,";
	input += to_string(rating);
	line.push_back(input);
	while (getline(HotelListFile, lineStr)) {
		line.push_back(lineStr);
	}
	HotelListFile.close();

	fstream file(HOTELFILE, ios::out);

	for (int i = 0; i < line.size(); i++) {
		file << line[i] << "\n";
	}

	file.close();
}

/**
* get hotel for list selection
* @param a PartnerID an integer argument
* @param b FileName an string argument
*/
void CPartnerAddListInterface::createHotelList(int PartnerID, string FileName) {
	m_vecHotelID.clear();
	m_vecHotelLocation.clear();
	m_vecHotelName.clear();
	string lineStr, wordStr;
	ifstream HotelListFile(FileName, ios::in);
	while (getline(HotelListFile, lineStr)) {
		stringstream Str(lineStr);
		if (getline(Str, wordStr, ',') && stoi(wordStr) == PartnerID) {
			int count = 0;
			while (getline(Str, wordStr, ',')) {
				if (count == 0) {
					m_vecHotelID.push_back(stoi(wordStr.c_str()));
				}
				else if (count == 1) {
					m_vecHotelLocation.push_back(wordStr.c_str());
				}
				else if (count == 2) {
					m_vecHotelName.push_back(wordStr.c_str());
				}
				else {
					break;
				}
				count++;
			}
		}
	}
	HotelListFile.close();
}

/**
* get all the element of one hotel
* @param a PartnerID an integer argument
* @param b FileName a string argument
* @param c HotelID an integer argument
*/
void CPartnerAddListInterface::GetAllHotelElement(int PartnerID, string FileName, int HotelID) {
	string lineStr, wordStr;
	ifstream HotelListFile(FileName, ios::in);
	while (getline(HotelListFile, lineStr)) {
		stringstream Str(lineStr);
		if (getline(Str, wordStr, ',') && stoi(wordStr) == PartnerID) {
			int count = 0;
			getline(Str, wordStr, ',');
			if (count == 0 && stoi(wordStr.c_str()) == HotelID) {
				while (getline(Str, wordStr, ',')) {
					switch (count) {
					case 0:
						m_strLocation = wordStr.c_str();
						break;
					case 1:
						HotelName = wordStr.c_str();
						break;
					case 2:
						m_numRoom[0] = stoi(wordStr.c_str());
						break;
					case 3:
						m_numRoom[1] = stoi(wordStr.c_str());
						break;
					case 4:
						m_numRoom[2] = stoi(wordStr.c_str());
						break;
					case 5:
						m_numRoom[3] = stoi(wordStr.c_str());
						break;
					case 6:
						price[0] = stof(wordStr.c_str());
						break;
					case 7:
						price[1] = stof(wordStr.c_str());
						break;
					case 8:
						price[2] = stof(wordStr.c_str());
						break;
					case 9:
						price[3] = stof(wordStr.c_str());
						break;
					case 10:
						parkingspot = stoi(wordStr.c_str());
						break;
					case 11:
						if (stoi(wordStr.c_str()) == 1) {
							PetFriendly = true;
						}
						else PetFriendly = false;
						break;
					case 12:
						if (stoi(wordStr.c_str()) == 1) {
							SmokeFriendly = true;
						}
						else SmokeFriendly = false;
						break;
					case 13:
						rating = m_pHotelManager->Find_Hotel(to_string(HotelID))->Get_HotelRating();
						break;
					default:
						break;
					}
					count++;
				}

			}
		}
	}
	HotelListFile.close();
}

/**
* save every element after user confirm creation
* @param a PartnerID an integer argument
*/
void CPartnerAddListInterface::SaveCreation(int PartnerID) {

	int hotelIdenti = GenerateHotelID(HOTELFILE);

	ofstream HotelFile;
	HotelFile.open(HOTELFILE, ios::out | ios::app);
	HotelFile << PartnerID << "," << hotelIdenti << "," << m_strLocation << "," << HotelName << ",";
	for (int room = 0; room < NUM_OF_ROOMSIZE; room++) {
		HotelFile << m_numRoom[room] << ",";
	}
	for (int pircenum = 0; pircenum < NUM_OF_ROOMSIZE; pircenum++) {
		HotelFile << setprecision(2) << fixed << price[pircenum] << ",";
	}
	HotelFile << parkingspot << ",";
	if (PetFriendly) HotelFile << "1,"; else HotelFile << "0,";
	if (SmokeFriendly) HotelFile << "1,"; else HotelFile << "0,";
	HotelFile << rating << ",";
	HotelFile << "\n";
	HotelFile.close();


	int iNumRoom = 0;

	for (int room = 0; room < NUM_OF_ROOMSIZE; room++)
	{
		iNumRoom += m_numRoom[room];
	}

	if (nullptr != m_pHotelManager)
	{
		m_pHotelManager->Partner_CreateHotel(m_strLocation, HotelName, iNumRoom,
			m_numRoom[0], m_numRoom[1], m_numRoom[2], m_numRoom[3],
			price[0], price[1], price[2], price[3],
			hotelIdenti, PartnerID, PetFriendly, SmokeFriendly);
	}

}

/**
* Reset the variable to initial stage
*/
void CPartnerAddListInterface::ResetVariable() {
	HotelID = 0;
	m_strLocation = "none";
	HotelName = "none";
	SmokeFriendly = false;
	PetFriendly = false;

	for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
		m_numRoom[i] = 0;
		price[i] = 0;
	}
	parkingspot = 0;
	rating = 0;
	m_strUserInput = "";
}


int CPartnerAddListInterface::GenerateHotelID(string FileName) {
	int id;
	vector<int> HotelIdArray;
	string lineStr, wordStr;
	ifstream HotelListFile(FileName, ios::in);
	while (getline(HotelListFile, lineStr)) {
		stringstream Str(lineStr);
		int count = 0;
		while (getline(Str, wordStr, ',')) {
			count++;
			if (count == 2) {
				HotelIdArray.push_back(stoi(wordStr.c_str()));
				break;
			}
		}
	}
	HotelListFile.close();
	if (HotelIdArray.size() != 0) {
		id = HotelIdArray[HotelIdArray.size() - 1] + 1;
	}
	else {
		id = 1;
	}
	return id;
}

void CPartnerAddListInterface::DeleteHotel(int PartnerID, int HotelID, std::string FileName) {
	string lineStr, wordStr;
	ifstream HotelListFile(FileName, ios::in);
	int line_index = 0;
	while (getline(HotelListFile, lineStr)) {
		stringstream Str(lineStr);
		if (getline(Str, wordStr, ',') && stoi(wordStr) == PartnerID) {
			getline(Str, wordStr, ',');
			if (stoi(wordStr.c_str()) == HotelID) {
				break;
			}
		}
		line_index++;
	}
	if (line_index >= count(istreambuf_iterator<char>(ifstream(FileName).rdbuf()), istreambuf_iterator<char>(), '\n'))
		return;
	string s(istreambuf_iterator<char>(ifstream(FileName).rdbuf()), istreambuf_iterator<char>());
	string::iterator it1 = s.begin();
	while (line_index-- > 0)
	{
		it1 = find(it1, s.end(), '\n') + 1;
	}
	string::iterator it2 = find(it1, s.end(), '\n') + 1;
	s.erase(it1, it2);
	copy(s.begin(), s.end(), ostreambuf_iterator<char>(ofstream(FileName).rdbuf()));

	m_pHotelManager->Partner_DeleteHotel(PartnerID, HotelID);
}

bool CPartnerAddListInterface::ifroomhasprice() {
	for (int i = 0; i < NUM_OF_ROOMSIZE; i++) {
		if (price[i] == 0 && m_numRoom[i] != 0) {
			return false;
		}
	}
	return true;
}

bool CPartnerAddListInterface::Prompt_User(int _iMin, int _iMax, size_t _imaxstrlen)
{
	std::cout << "Enter your choice (" << _iMin << " to " << _iMax << "): ";
	cin >> m_strUserInput;

	if (m_strUserInput.length() > _imaxstrlen)
	{
		return false;
	}

	if (!Check_IfNumber(m_strUserInput))
	{
		return false;
	}

	if (stoi(m_strUserInput) >= _iMin && stoi(m_strUserInput) <= _iMax)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CPartnerAddListInterface::FPrompt_User(float _iMin, float _iMax, size_t _imaxstrlen)
{

	std::cout << "Enter your choice (" << setprecision(2) << fixed << _iMin << " to " << _iMax << "): ";
	cin >> m_strUserInput;

	if (m_strUserInput.length() > _imaxstrlen)
	{
		return false;
	}

	if (!Check_IfNumberF(m_strUserInput))
	{
		return false;
	}

	if (stof(m_strUserInput) >= _iMin && stof(m_strUserInput) <= _iMax)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CPartnerAddListInterface::N_Format(int _iDigit)
{
	if (_iDigit < 10)
	{
		std::cout << "0" << _iDigit;
	}
	else
	{
		std::cout << _iDigit;
	}
}

bool CPartnerAddListInterface::Check_IfNumber(std::string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}

bool CPartnerAddListInterface::Check_IfNumberF(std::string str)
{
	bool isnum = false;
	int dotcount = 0;
	int nonnum = 0;
	for (int i = 0; i < str.length(); i++) {
		if (isdigit(str[i]) && nonnum == 0 && dotcount <= 1) {
			isnum = true;
		}
		else if (str[i] == '.') {
			isnum = false;
			dotcount++;
		}
		else {
			isnum = false;
			nonnum++;
		}
	}
	return isnum;
}
/**
*to display the choice of size the partner added.
*/
void CPartnerAddListInterface::SizetoString(int size) {
	switch (size) {
	case 1:
		std::cout << "Small ";
		break;
	case 2:
		std::cout << "Medium ";
		break;
	case 3:
		std::cout << "Big ";
		break;
	case 4:
		std::cout << "Huge ";
		break;
	default:
		break;
	}
}
/**
* if the input is already exist in the array
*/
bool CPartnerAddListInterface::ifexist(int arr[], int size, int input) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == input)
			return true;
	}
	return false;
}

void CPartnerAddListInterface::signtoarr(int arr[4], int input, int num) {
	switch (input) {
	case 1:
		arr[0] = num;
		break;
	case 2:
		arr[1] = num;
		break;
	case 3:
		arr[2] = num;
		break;
	case 4:
		arr[3] = num;
		break;
	}
}

bool CPartnerAddListInterface::hascomma(std::string str) {
	string::size_type index = str.find(",");
	if (index != string::npos) {
		return true;
	}
	else {
		return false;
	}

}

