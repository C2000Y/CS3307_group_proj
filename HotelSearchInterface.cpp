//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// Mostly Displayingstuff here.
//////////////////////////////////////////////////////////////
#include "HotelSearchInterface.h"

//#include "Cities.h"
#include "Room.h"
#include "Hotel.h"
#include "HotelSpecContainer.h"
#include "HotelManager.h"
// sugg
#include "HotelSuggestedInterface.h"


using namespace std;

CHotelSearchInterface::CHotelSearchInterface(CHotelManager * _pHotelManager)
	:m_pHotelManager(nullptr)
	, m_strUserInput("")
	, m_strLocation("London")
	, m_iCheckInYear(DEFAULT_YEAR)
	, m_iCheckInMonth(DEFAULT_MONTH)
	, m_iCheckInDay(DEFAULT_DAY)
	, m_iCheckInHour(DEFAULT_HOUR)
	, m_iCheckInMinute(DEFAULT_MINUTE)
	, m_iCheckOutYear(DEFAULT_YEAR)
	, m_iCheckOutMonth(DEFAULT_MONTH)
	, m_iCheckOutHour(DEFAULT_HOUR)
	, m_iCheckOutMinute(DEFAULT_MINUTE)
	, m_iPageNum(0)
	, m_iIndexForPage(0)
	, m_eCheckMode(MODE_END)
	, m_pHotelThatIsSelected(nullptr)
	, m_pSuggInterface(nullptr)
	, m_bCheckIfWeAreUsingSuggested(false)
	, m_bSearchPetAllowed(false)
	, m_bSearchSmokeAllowed(false)
	, m_bSearchRatingAllowed(false)
	, m_iCurrMinRating(3)
	, m_bCheckUseAdvfilters(false)
	, m_bUsedAdvOption(false)
{
	if (_pHotelManager != nullptr)
	{
		m_pHotelManager = _pHotelManager;
		// sugg
		m_pSuggInterface = new CHotelSuggInterface(m_pHotelManager, this);
	}

	m_vecNumPeoplePerRoom.emplace_back(1);
	Recalc_num_people();

	Default_CheckOutDay();
}

CHotelSearchInterface::~CHotelSearchInterface(void)
{
	m_pHotelManager = nullptr;
	m_vecNumPeoplePerRoom.clear();
	m_vecNumPeoplePerRoom.shrink_to_fit();

	// since its only a referencing map of vectors
	Clear_ResultVector();

	m_pHotelThatIsSelected = nullptr;
	
	if (nullptr != m_pSuggInterface)
	{
		delete m_pSuggInterface;
		m_pSuggInterface = nullptr;
	}

}

bool CHotelSearchInterface::Run_Interface(void)
{
	while (true)
	{
		system("clear");
		m_bCheckIfWeAreUsingSuggested = false; // resett everytime
		// while it's running it should display suggested rooms
		if (nullptr != m_pSuggInterface && (!m_pHotelManager->Get_HotelContainer()->empty()))
		{
			m_pSuggInterface->Display_Sugg();
		}
		Show_SearchDisplay();
		if (!Prompt_User(1, 8))
		{
			continue;
		}
		switch (stoi(m_strUserInput))
		{
		case eMAINMENU::OPT_LOCATION:
			Menu_Location();
			break;
		case eMAINMENU::OPT_CHECKIN:
			Menu_CheckIn();
			break;
		case eMAINMENU::OPT_CHECKOUT:
			Menu_CheckOut();
			break;
		case eMAINMENU::OPT_NUMROOM:
			Menu_NumRoom();
			break;
		case eMAINMENU::OPT_NUMPEOPLE:
			Menu_NumPeople();
			break;
		case eMAINMENU::OPT_CONFIRM:
			// then we run search 
			m_bCheckIfWeAreUsingSuggested = false;
			return true;
		case eMAINMENU::OPT_SUGG:
			// we skip search and confirm using suggested room
			m_bCheckIfWeAreUsingSuggested = true;
			return true;
		case eMAINMENU::OPT_EXIT:
			return false;
		default:
			cout << "Error" << endl;
			//system("pause");
			break;
		}
	}

	return false;
}

bool CHotelSearchInterface::Run_Search(void)
{
	if (Search_Hotel_Interface_SameHotel()) // true means it has results
	{
		// display hotel results
		if (Display_Results())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else // found no results
	{
		// display no result display
		Display_NoResult();
		return false;
	}
}

bool CHotelSearchInterface::Search_Hotel_Interface_SameHotel(void)
{
	// now that user has confirmed search with information provided
	// use the search with that information

	// can look into the map in hour hotel manager with location

	// clear currently containing info just because it might be used more than once.
	Clear_ResultVector();
	Clear_ResultMap();

	// grabs the all the hotels that belongs to the user specified location
	vector<CHotel*>* pvecHotels = m_pHotelManager->Get_HotelsBasedOnLocation(m_strLocation);

	if (nullptr == pvecHotels)
	{
		return false;
	}
	 int isize = m_vecNumPeoplePerRoom.size();

	int iNumRooms = int(isize); // will use for search
	int iNumRoomSize[CRoom::eROOMSIZE::SIZE_END]; // upto 4 people


	for (int i = 0; i < CRoom::eROOMSIZE::SIZE_END; ++i)
	{
		iNumRoomSize[i] = 0;
	}

	for ( int i = 0; i < isize; ++i)
	{
		++iNumRoomSize[m_vecNumPeoplePerRoom[i] - 1]; // collects how many numbers of sized rooms there are.
	}

	std::vector<CRoom*>* pvecRooms = nullptr;

	int iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_END]; // upto 4 people

	// auto == for local copy, not changing value in real
	// auto&  == original and want to modify
	for (auto iter_vec = pvecHotels->begin(); iter_vec != pvecHotels->end(); ++iter_vec)
	{
		for (int i = 0; i < CRoom::eROOMSIZE::SIZE_END; ++i) // need to reset so we can check per hotel.
		{
			iNumRoomSizeFound[i] = 0;
		}

		// check to see if regarding hotel matches number of rooms required.
		// number of rooms
		if ((*iter_vec)->Get_NumberofRooms() >= iNumRooms)
		{
			// number of people per rooms
			// has to match all the num room size requirements
			if ((*iter_vec)->Get_NumberofSizedRooms(CRoom::eROOMSIZE::SIZE_SMALL) < iNumRoomSize[CRoom::eROOMSIZE::SIZE_SMALL])
			{
				continue;
			}
			if ((*iter_vec)->Get_NumberofSizedRooms(CRoom::eROOMSIZE::SIZE_MID) < iNumRoomSize[CRoom::eROOMSIZE::SIZE_MID])
			{
				continue;
			}
			if ((*iter_vec)->Get_NumberofSizedRooms(CRoom::eROOMSIZE::SIZE_BIG) < iNumRoomSize[CRoom::eROOMSIZE::SIZE_BIG])
			{
				continue;
			}
			if ((*iter_vec)->Get_NumberofSizedRooms(CRoom::eROOMSIZE::SIZE_SMALL) < iNumRoomSize[CRoom::eROOMSIZE::SIZE_SMALL])
			{
				continue;
			}
			// if all num room conditions match

			//std::vector<CRoom*> m_vecRooms;
			pvecRooms = (*iter_vec)->Get_RoomVector();

			for (auto pRoom : *pvecRooms)
			{
				// at this point of our code
				// we know that it satisified all the rooms size and room number conditions
				// so just get the required amount since one hotel can have 100000 rooms and we dont want to check all of them.

				// lets check first if we found all of our rooms

				//if (iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_SMALL] == iNumRoomSize[CRoom::eROOMSIZE::SIZE_SMALL] &&
				//	iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_MID] == iNumRoomSize[CRoom::eROOMSIZE::SIZE_MID] &&
				//	iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_BIG] == iNumRoomSize[CRoom::eROOMSIZE::SIZE_BIG] &&
				//	iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_HUGE] == iNumRoomSize[CRoom::eROOMSIZE::SIZE_HUGE])
				//{
				//	// we found all rooms 
				//	m_vecResultHotels.emplace_back((*iter_vec));// then we get this hotel as a result
				//	break;
				//}

				if (iNumRoomSizeFound[pRoom->Get_RoomSize()] == iNumRoomSize[pRoom->Get_RoomSize()]) // we found all for that size
				{
					continue;
				}

				// check in / check out date for each room
				if (Compare_Dates
				(
					m_iCheckInYear,
					m_iCheckInMonth,
					m_iCheckInDay,
					pRoom->Get_CheckInYear(),
					pRoom->Get_CheckInMonth(),
					pRoom->Get_CheckInDay()
				) >= 0) // if Check in date from user search is older or equal 
				{
					if (Compare_Dates
					(
						m_iCheckOutYear,
						m_iCheckOutMonth,
						m_iCheckOutDay,
						pRoom->Get_CheckOutYear(),
						pRoom->Get_CheckOutMonth(),
						pRoom->Get_CheckOutDay()
					) <= 0) // if Check Out date from user search is younger or equal 
					{
						// it satsifies all the requirements by user search
						++iNumRoomSizeFound[pRoom->Get_RoomSize()];// found that sized room
						m_mapvecRoomNumbers[(*iter_vec)->Get_HotelName()].emplace_back(pRoom->Get_RoomNumber()); // get the room number

						if (iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_SMALL] == iNumRoomSize[CRoom::eROOMSIZE::SIZE_SMALL] &&
							iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_MID] == iNumRoomSize[CRoom::eROOMSIZE::SIZE_MID] &&
							iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_BIG] == iNumRoomSize[CRoom::eROOMSIZE::SIZE_BIG] &&
							iNumRoomSizeFound[CRoom::eROOMSIZE::SIZE_HUGE] == iNumRoomSize[CRoom::eROOMSIZE::SIZE_HUGE])
						{
							// we found all rooms 
							m_vecResultHotels.emplace_back((*iter_vec));// then we get this hotel as a result
							break;
						}

					}
				}
			}
		}
	}
	
	// have to make condtion where if we found at least 1 room then its true
	// if not false;
	if (!m_vecResultHotels.empty())
	{
		return true;
	}
	else
	{
		return false; // we go through all the hotel listings and we did not find result
	}
}

void CHotelSearchInterface::Display_NoResult(void)
{
	while (true)
	{

		system("clear");

		cout << "##      ##     #####      " << endl;
		cout << "####    ##  ##       ##   " << endl;
		cout << "## ###  ## ##         ##   " << endl;
		cout << "##   ##### ##         ##   " << endl;
		cout << "##     ###  ##       ##    " << endl;
		cout << "##      ##     #####       " << endl;
		cout << endl;
		cout << "#######   #######  #########  ##      ##  ##    ########## #########  " << endl;
		cout << "##    ### ##      ###         ##      ##  ##        ##    ###           " << endl;
		cout << "##   ###  ######   #######    ##      ##  ##        ##     #######    " << endl;
		cout << "######    ##             #### ##      ##  ##        ##           ####  " << endl;
		cout << "##   ###  ##      ###     ###  ##    ##   ##        ##    ###     ### " << endl;
		cout << "#     ### #######    #####       ####     ########  ##       #####    " << endl;
		cout << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "NO results were found..." << endl;
		cout << "Type 1 to go back to search again." << endl;
		cout << "-------------------------------------------------------------------" << endl;

		if (!Prompt_User(1, 1))
		{
			continue;
		}
		return;
	}
}

bool CHotelSearchInterface::Display_Results(void)
{
	// and need room numbers that are selected.
	//std::vector<CHotel*> m_vecResultHotels;
	//std::map<std::string, vector<int>>  m_mapvecRoomNumbers;

	// what i need to use rating as this will be refreshed when we consult that advanced option
	// check if we are using it

	if (m_bCheckUseAdvfilters)
	{
		if (m_bSearchRatingAllowed)
		{
			// this means we are excluding the stuff  for that 
			// have to see their ratings and exclude them from the vector
			for (auto pHotels = m_vecResultHotels.begin(); pHotels != m_vecResultHotels.end(); )
			{
				if ((*pHotels)->Get_HotelRating() < m_iCurrMinRating)
				{
					pHotels = m_vecResultHotels.erase(pHotels);
				}
				else
				{
					++pHotels;
				}
			}
			// have to see if its empty
			// then we have to display  
		}
	}

	if (!m_vecResultHotels.empty())
	{


		int _iNumResults = m_vecResultHotels.size();
		m_iPageNum = 0;

		auto iter_vec = m_vecResultHotels.begin(); // going to be using this as the pages

		string strHotelName = "";
		float fTotalCost = 0.0f;
		float fTempCost = 0.0f;

		int iNumSizeRoom[CRoom::eROOMSIZE::SIZE_END]; // 4 sizes
		int isize = m_vecNumPeoplePerRoom.size();

		while (true)
		{
			strHotelName = (*iter_vec)->Get_HotelName();
			fTotalCost = 0.0f;

			system("clear");
			cout << "-------------------------------------------------------------------" << endl;
			cout << "				      "; N_Format(_iNumResults); cout << " Results" << endl;
			cout << "                                                    Page "; N_Format(m_iPageNum + 1); cout << " of "; N_Format(_iNumResults); cout << endl;
			cout << "-------------------------------------------------------------------" << endl;

			// display hotel info
			// display hotel name
			// display hotel rating  
			cout << "        " << "Hotel : " << strHotelName << endl;
			cout << "        " << "Location : " << m_strLocation << endl;
			cout << "        " << "Rating: " << (*iter_vec)->Get_HotelRating() << endl;



			// and room numbers
			// to show the pet and smoking options
			// we have to grab  
			for (auto pvec : m_mapvecRoomNumbers[strHotelName])
			{
				cout << "--------------        Room ["; N_Format(pvec); cout << "]";

				if (m_bCheckUseAdvfilters)
				{
					if (m_bSearchPetAllowed)
					{
						if ((*((*iter_vec)->Get_RoomVector()))[pvec - 1]->Get_PetAllowed())
						{
							cout << "  Pets [O]";
						}
						else
						{
							cout << "  Pets [ ]";
						}
					}
					if (m_bSearchSmokeAllowed)
					{
						if (!m_bSearchPetAllowed)
						{
							cout << "          ";
						}
						if ((*((*iter_vec)->Get_RoomVector()))[pvec - 1]->Get_SmokeAllowed())
						{
							cout << "  Smoke [O]";
						}
						else
						{
							cout << "  Smoke [ ]";
						}
					}
				}
				cout << endl;
			}

			for (int i = 0; i < CRoom::eROOMSIZE::SIZE_END; ++i)
			{
				iNumSizeRoom[i] = 0;
			}

			for (int i = 0; i < isize; ++i)
			{
				++iNumSizeRoom[m_vecNumPeoplePerRoom[i] - 1]; // collects how many numbers of sized rooms there are.
			}

			// display pet
			// display smoke
			// display num of rooms per size
			for (int i = 0; i < CRoom::eROOMSIZE::SIZE_END; ++i)
			{
				fTempCost = (*iter_vec)->Get_RoomCost(i);

				cout << "        "; N_Format(iNumSizeRoom[i]);
				cout << " With " << i + 1 << " people: ";
				cout << "        " << "$" << fTempCost << " x "; N_Format(iNumSizeRoom[i]); cout << " = $" << (fTempCost *  iNumSizeRoom[i]) << endl; 
				fTotalCost += (fTempCost *  iNumSizeRoom[i]);
			}
			cout << "-------------------------------------------------------------------" << endl;
			// total cost 
			cout << "        " << "Total Cost: $" << fTotalCost << endl;
			//for (auto pRoom : iter_map->second)
			//{
			//	cout << "--------------        Room ["; N_Format(iRoomNum); cout << "]        " << endl;
			//}

			if (m_iPageNum > 0)
			{
				cout << "        " << "1. Prev Page" << endl;
			}
			else
			{
				cout << endl;
			}
			if (m_iPageNum < (_iNumResults - 1))
			{
				cout << "        " << "2. Next Page" << endl;
			}
			else
			{
				cout << endl;
			}
			cout << "        " << "3. Select This Hotel" << endl;
			cout << "        " << "4. Select Search Filters" << endl;
			cout << "        " << "5. Go Back" << endl;
			cout << "-------------------------------------------------------------------" << endl;

			if (!Prompt_User(1, 5))
			{
				continue;
			}

			switch (stoi(m_strUserInput))
			{
			case 1: // prev
				if (m_iPageNum == 0)
				{
					continue;
				}
				else
				{
					m_iPageNum--; // prev page
					--iter_vec; // for the resulted hotels
				}
				break;
			case 2: // next
				if (m_iPageNum == (_iNumResults - 1))
				{
					continue;
				}
				else
				{
					m_iPageNum++; // next page
					++iter_vec; // for the resulted hotels
				}
				break;
			case 3: // select hotel
				m_pHotelThatIsSelected = (*iter_vec); // set the selected hotel so the booking interface can use it.
				return true;
			case 4:
				MoreSearchOptions();
				// if this is selected
				// then we have to go back and run the function where it grabs gets the result again
				m_bUsedAdvOption = true; // this.
				return false;
			case 5: // go back
				return false;
			default:
				break;
			}
		}
	}
	else
	{
		// will come here when there are no  results due to rating too high
		system("clear");
		cout << "NO RESULTS" << endl;
		cout << "PLEASE SELECT LOWER RATING" << endl;
		int itemp = 0;
		for (int i = 0; i < 99999; ++i)
		{
			itemp++;
			for (int j = 0; j < 9999; ++j)
			{
			itemp--;
			itemp++;
			}
		}
		MoreSearchOptions();
		m_bUsedAdvOption = true; // this.
		return false;
	}
}

void CHotelSearchInterface::Menu_Location(void)
{
	int iIndex = 1;
	m_iPageNum = 0;
	while (true)
	{
		iIndex = 1;
		system("clear");
		cout << "-------------------------------------------------------------------" << endl;
		cout << "                                             Page "; N_Format(m_iPageNum + 1); cout  << " of " << int(m_vecCities.size() / LIST_PER_PAGE) << endl;
		cout << "-------------------------------------------------------------------" << endl;
		for (int i = 0 + (m_iPageNum * LIST_PER_PAGE); i < ((m_iPageNum * LIST_PER_PAGE) + LIST_PER_PAGE); ++i)
		{
			cout << "--------\t"; N_Format(iIndex++); cout << ".\t" << m_vecCities[i] << endl;
		}
		cout << "-------------------------------------------------------------------" << endl;
		if (m_iPageNum > 0)
		{
			cout << "        " << "16. Prev Page" << endl;
		}
		else
		{
			cout << endl;
		}
		if (m_iPageNum < 9)
		{
			cout << "        " << "17. Next Page" << endl;
		}
		else
		{
			cout << endl;
		}
		cout << "        " << "18. Go Back" << endl;
		cout << "-------------------------------------------------------------------" << endl;

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
			m_strLocation = m_vecCities[stoi(m_strUserInput) + (m_iPageNum * LIST_PER_PAGE) - 1];
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

void CHotelSearchInterface::Menu_CheckIn(void)
{
	m_eCheckMode = MODE_YEAR;

	while (true)
	{
		system("clear");
		cout << "-------------------------------------------------------------------" << endl;
		switch (m_eCheckMode)
		{
		case eCheckMode::MODE_YEAR:
			cout << "                                                    Change Year" << endl;
			break;
		case eCheckMode::MODE_MONTH:
			cout << "                                                    Change Month" << endl;
			break;
		case eCheckMode::MODE_DAY:
			cout << "                                                    Change Day" << endl;
			break;
		}
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "                  Current Check In Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout <<  "        " <<"1. Change Year" << endl;
		cout <<  "        " <<"2. Change Month" << endl;
		cout <<  "        " <<"3. Change Day" << endl;
		cout <<  "        " <<"4. Go Back" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;

		if (!Prompt_User(1, 4))
		{
			continue;
		}

		switch (stoi(m_strUserInput))
		{
		case 1: // change year
			m_eCheckMode = eCheckMode::MODE_YEAR;
			break;
		case 2: // change month
			m_eCheckMode = eCheckMode::MODE_MONTH;
			break;
		case 3: // change day
			m_eCheckMode = eCheckMode::MODE_DAY;
			break;
		case 4: // go back
				// before going back must set default 48 hrs
			Default_CheckOutDay();
			return;
		default:
			break;
		}

		switch (m_eCheckMode)
		{
		case eCheckMode::MODE_YEAR:
			while (true)
			{
				system("clear");
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "                  Current Check In Year: " << m_iCheckInYear << " ==> ????" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;

				if (!Prompt_User(2020, 2120))
				{
					continue;
				}
				else
				{
					m_iCheckInYear = stoi(m_strUserInput);
					break;
				}
			}
			break;
		case eCheckMode::MODE_MONTH:
			while (true)
			{
				system("clear");
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "                  Current Check In Month: "; N_Format(m_iCheckInMonth); cout << " ==> ????" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;

				if (!Prompt_User(1, 12))
				{
					continue;
				}
				else
				{
					// have to check if they have over 28 when its feb or the other 4 over 30
					m_iCheckInMonth = stoi(m_strUserInput);
					switch (stoi(m_strUserInput))
					{
					case 1:
					case 3:
					case 5:
					case 7:
					case 8:
					case 10:
					case 12: // 31 
							 // no need to check
						break;
					case 2: //28
						if (m_iCheckInDay > 28)
						{
							m_iCheckInDay = 28;
						}
						break;
					case 4: //30
					case 6:
					case 9:
					case 11:
						if (m_iCheckInDay > 30)
						{
							m_iCheckInDay = 30;
						}
						break;
					}
					break;
				}
			}
			break;
		case eCheckMode::MODE_DAY:
			switch (m_iCheckInMonth)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				while (true)
				{
					system("clear");
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "                  Current Check In Day: "; N_Format(m_iCheckInDay); cout  << " ==> ????" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;

					if (!Prompt_User(1, 31))
					{
						continue;
					}
					else
					{
						m_iCheckInDay = stoi(m_strUserInput);
						break;
					}
				}
				break;
			case 2:
				while (true)
				{
					system("clear");
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "                  Current Check In Day: "; N_Format(m_iCheckInDay); cout << " ==> ????" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;

					if (!Prompt_User(1, 28))
					{
						continue;
					}
					else
					{
						m_iCheckInDay = stoi(m_strUserInput);
						break;
					}
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				while (true)
				{
					system("clear");
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "                  Current Check In Day: "; N_Format(m_iCheckInDay); cout << " ==> ????" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;

					if (!Prompt_User(1, 30))
					{
						continue;
					}
					else
					{
						m_iCheckInDay = stoi(m_strUserInput);
						break;
					}
				}
				break;
			}
			break;
		}
	}
}

void CHotelSearchInterface::Menu_CheckOut(void)
{
	m_eCheckMode = MODE_YEAR;

	while (true)
	{
		system("clear");
		cout << "-------------------------------------------------------------------" << endl;
		switch (m_eCheckMode)
		{
		case eCheckMode::MODE_YEAR:
			cout << "                                                    Change Year" << endl;
			break;
		case eCheckMode::MODE_MONTH:
			cout << "                                                    Change Month" << endl;
			break;
		case eCheckMode::MODE_DAY:
			cout << "                                                    Change Day" << endl;
			break;
		}
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout  << "-"; N_Format(m_iCheckInDay); cout  << endl;
		cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout  << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout <<  "        " <<"1. Change Year" << endl;
		cout <<  "        " <<"2. Change Month" << endl;
		cout <<  "        " <<"3. Change Day" << endl;
		cout <<  "        " <<"4. Go Back" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;

		if (!Prompt_User(1, 4))
		{
			continue;
		}

		switch (stoi(m_strUserInput))
		{
		case 1: // change year
			m_eCheckMode = eCheckMode::MODE_YEAR;
			break;
		case 2: // change month
			m_eCheckMode = eCheckMode::MODE_MONTH;
			break;
		case 3: // change day
			m_eCheckMode = eCheckMode::MODE_DAY;
			break;
		case 4: // go back
			return;
		default:
			break;
		}

		switch (m_eCheckMode)
		{
		case eCheckMode::MODE_YEAR:
			while (true)
			{
				system("clear");
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
				cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout << endl;
				cout << endl;
				cout << "                  Current Check Out Year: " << m_iCheckOutYear << " ==> ????" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;

				if (!Prompt_User(2020, 2120))
				{
					continue;
				}
				else
				{
					// have to make sure the years are the same or higher
					if (m_iCheckInYear > stoi(m_strUserInput))
					{
						continue;
					}
					if (m_iCheckInYear == stoi(m_strUserInput))
					{
						// if month is bigger than --fail
						// if month is same but day is bigger or equal to -- fail.

						if (m_iCheckInMonth > m_iCheckOutMonth)
						{
							continue;
						}
						if (m_iCheckInMonth == m_iCheckOutMonth)
						{
							if (m_iCheckInDay >= m_iCheckOutDay)
							{
								continue;
							}
						}
					}

					m_iCheckOutYear = stoi(m_strUserInput);
					break;
				}
			}
			break;
		case eCheckMode::MODE_MONTH:
			while (true)
			{
				system("clear");
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
				cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout << endl;
				cout << endl;
				cout << "                  Current Check Out Month: "; N_Format(m_iCheckOutMonth); cout << " ==> ????" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;

				if (!Prompt_User(1, 12))
				{
					continue;
				}
				else
				{
					// if the year is higher than current year then anything goes.
					if (m_iCheckInYear == m_iCheckOutYear)
					{
						// have to check if the month is the same,
						// or if the month is less.
						if (m_iCheckInMonth > stoi(m_strUserInput))
						{
							continue;
						}
						else if (m_iCheckInMonth == stoi(m_strUserInput))
						{
							// have to check the day
							// if day is the same. nono
							// if day is smaller nono
							if (m_iCheckInDay >= m_iCheckOutDay)
							{
								continue;
							}

							switch (stoi(m_strUserInput))
							{
							case 1:
							case 3:
							case 5:
							case 7:
							case 8:
							case 10:
							case 12: // 31 
									 // no need to check
								m_iCheckOutMonth = stoi(m_strUserInput);
								break;
							case 2: //28
								if (m_iCheckOutDay > 28)
								{
									if (m_iCheckInDay >= 28)
									{
										continue;
									}
									m_iCheckOutMonth = stoi(m_strUserInput);
									m_iCheckOutDay = 28;
								}
								break;
							case 4: //30
							case 6:
							case 9:
							case 11:
								if (m_iCheckOutDay > 30)
								{
									if (m_iCheckInDay >= 30)
									{
										continue;
									}
									m_iCheckOutMonth = stoi(m_strUserInput);
									m_iCheckOutDay = 30;
								}
								break;
							}
							break;
						}
						// if its lower, then its fine.
						// if input month is lower than check in month
						else
						{
							m_iCheckOutMonth = stoi(m_strUserInput);
							switch (stoi(m_strUserInput))
							{
							case 1:
							case 3:
							case 5:
							case 7:
							case 8:
							case 10:
							case 12: // 31 
									 // no need to check
								break;
							case 2: //28
								if (m_iCheckOutDay > 28)
								{
									m_iCheckOutDay = 28;
								}
								break;
							case 4: //30
							case 6:
							case 9:
							case 11:
								if (m_iCheckOutDay > 30)
								{
									m_iCheckOutDay = 30;
								}
								break;
							}
							break;
						}
					}
					// have to make sure if its the same year, then month hast to be higher
					else if (m_iCheckInYear < m_iCheckOutYear)
					{
						// have to check if they have over 28 when its feb or the other 4 over 30
						m_iCheckOutMonth = stoi(m_strUserInput);
						switch (stoi(m_strUserInput))
						{
						case 1:
						case 3:
						case 5:
						case 7:
						case 8:
						case 10:
						case 12: // 31 
								 // no need to check
							break;
						case 2: //28
							if (m_iCheckOutDay > 28)
							{
								m_iCheckOutDay = 28;
							}
							break;
						case 4: //30
						case 6:
						case 9:
						case 11:
							if (m_iCheckOutDay > 30)
							{
								m_iCheckOutDay = 30;
							}
							break;
						}
						break;
					}
				}
			}
			break;
		case eCheckMode::MODE_DAY:

			// need to check if month is the same -- than  if day bigger or fail
			// need to chec if month is bigger than anything goes.
			if (m_iCheckInMonth == m_iCheckOutMonth)
			{
				switch (m_iCheckOutMonth)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					while (true)
					{
						system("clear");
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
						cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout << endl;
						cout << endl;
						cout << "                  Current Check Out Day: "; N_Format(m_iCheckOutDay); cout << " ==> ????" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;

						if (!Prompt_User(1, 31))
						{
							continue;
						}
						else
						{
							if (m_iCheckInDay >= stoi(m_strUserInput))
							{
								continue;
							}
							m_iCheckOutDay = stoi(m_strUserInput);
							break;
						}
					}
					break;
				case 2:
					while (true)
					{
						system("clear");
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
						cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout << endl;
						cout << endl;
						cout << "                  Current Check Out Day: "; N_Format(m_iCheckOutDay); cout << " ==> ????" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;

						if (!Prompt_User(1, 28))
						{
							continue;
						}
						else
						{
							if (m_iCheckInDay >= stoi(m_strUserInput))
							{
								continue;
							}
							m_iCheckOutDay = stoi(m_strUserInput);
							break;
						}
					}
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					while (true)
					{
						system("clear");
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
						cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout << endl;
						cout << endl;
						cout << "                  Current Check Out Day: "; N_Format(m_iCheckOutDay); cout << " ==> ????" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;

						if (!Prompt_User(1, 30))
						{
							continue;
						}
						else
						{
							if (m_iCheckInDay >= stoi(m_strUserInput))
							{
								continue;
							}
							m_iCheckOutDay = stoi(m_strUserInput);
							break;
						}
					}
					break;
				}
			}
			else if (m_iCheckInMonth < m_iCheckOutMonth)
			{
				switch (m_iCheckOutMonth)
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					while (true)
					{
						system("clear");
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
						cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout << endl;
						cout << endl;
						cout << "                  Current Check Out Day: "; N_Format(m_iCheckOutDay); cout << " ==> ????" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;

						if (!Prompt_User(1, 31))
						{
							continue;
						}
						else
						{
							m_iCheckOutDay = stoi(m_strUserInput);
							break;
						}
					}
					break;
				case 2:
					while (true)
					{
						system("clear");
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
						cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout << endl;
						cout << endl;
						cout << "                  Current Check Out Day: "; N_Format(m_iCheckOutDay); cout << " ==> ????" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;

						if (!Prompt_User(1, 28))
						{
							continue;
						}
						else
						{
							m_iCheckOutDay = stoi(m_strUserInput);
							break;
						}
					}
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					while (true)
					{
						system("clear");
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "                  Current Check In  Date: " << m_iCheckInYear << "-"; N_Format(m_iCheckInMonth); cout << "-"; N_Format(m_iCheckInDay); cout << endl;
						cout << "                  Current Check Out Date: " << m_iCheckOutYear << "-"; N_Format(m_iCheckOutMonth); cout << "-"; N_Format(m_iCheckOutDay); cout << endl;
						cout << endl;
						cout << "                  Current Check Out Day: "; N_Format(m_iCheckOutDay); cout << " ==> ????" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;
						cout << "-------------------------------------------------------------------" << endl;

						if (!Prompt_User(1, 30))
						{
							continue;
						}
						else
						{
							m_iCheckOutDay = stoi(m_strUserInput);
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
}

void CHotelSearchInterface::Menu_NumRoom(void)
{
	//number of rooms -- change num of rooms + if more than 1 room than automatically add 1 more person... room cannot be empty

	while (true)
	{
		system("clear");
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "                    Current Number of Rooms: "; N_Format(m_vecNumPeoplePerRoom.size()); cout  << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "        " << "1. Change Number of Rooms " << endl;
		cout << "        " << "2. Go Back" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;

		if (!Prompt_User(1, 2))
		{
			continue;
		}

		switch (stoi(m_strUserInput))
		{
		case 1:
		{
			while (true)
			{
				system("clear");
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "                    Current Number of Rooms: "; N_Format(m_vecNumPeoplePerRoom.size()); cout << "==> ????" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;

				if (!Prompt_User(1, 20))
				{
					continue;
				}

				if (m_vecNumPeoplePerRoom.size() == ( int(stoi(m_strUserInput))))
				{
					// dont do anyhting 
					return;
				}
				else if (m_vecNumPeoplePerRoom.size() > ( int(stoi(m_strUserInput)))) // subtract rooms
				{
					int iHowManyTimes = m_vecNumPeoplePerRoom.size() -  int(stoi(m_strUserInput));
					for (int i = 0; i < iHowManyTimes; ++i)
					{
						m_vecNumPeoplePerRoom.pop_back();
					}
					m_vecNumPeoplePerRoom.shrink_to_fit();
					Recalc_num_people();
					return;
				}
				else if (m_vecNumPeoplePerRoom.size() <  int(stoi(m_strUserInput))) // add rooms
				{
					int iHowManyTimes =  int(stoi(m_strUserInput)) - m_vecNumPeoplePerRoom.size();
					for (int i = 0; i < iHowManyTimes; ++i)
					{
						m_vecNumPeoplePerRoom.emplace_back(1); // has to have at least 1 person in a room
					}
					Recalc_num_people();
					return;
				}
			}
		}
		break;
		case 2:
			return;
		default:
			break;
		}
	}

}

void CHotelSearchInterface::Menu_NumPeople(void)
{
	//number of people -- change number of people per room, cannot have 0 or more than 4 people in room.

	while (true)
	{
		system("clear");
		cout << "-------------------------------------------------------------------" << endl;
		cout << "                    Current Number of Rooms: "; N_Format(m_vecNumPeoplePerRoom.size()); cout << endl;
		cout << "-------------------------------------------------------------------" << endl;
		for ( int i = 0; i < m_vecNumPeoplePerRoom.size(); ++i)
		{
			cout << "--------------        Room ["; N_Format(i + 1); cout << "]         : " << m_vecNumPeoplePerRoom[i] << " People" << endl;
		}
		cout << "-------------------------------------------------------------------" << endl;
		cout << "        " <<"1. Change Number of Rooms " << endl;
		cout << "        " <<"2. Go Back" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;

		if (!Prompt_User(1, 2))
		{
			continue;
		}

		switch (stoi(m_strUserInput))
		{
		case 1:
		{
			while (true)
			{
				system("clear");
				cout << "-------------------------------------------------------------------" << endl;
				cout << "                    Current Number of Rooms: "; N_Format(m_vecNumPeoplePerRoom.size()); cout << endl;
				cout << "-------------------------------------------------------------------" << endl;
				for ( int i = 0; i < m_vecNumPeoplePerRoom.size(); ++i)
				{
					cout << "--------------        Room ["; N_Format(i + 1); cout << "]         : " << m_vecNumPeoplePerRoom[i] << " People" << endl;
				}
				cout << "-------------------------------------------------------------------" << endl;
				cout << "        " << "Select Room to change:" << endl;
				cout << "-------------------------------------------------------------------" << endl;
				cout << "-------------------------------------------------------------------" << endl;

				if (!Prompt_User(1, int(m_vecNumPeoplePerRoom.size())))
				{
					continue;
				}
				int iRoomNum = stoi(m_strUserInput);
				while (true)
				{
					system("clear");
					cout << "-------------------------------------------------------------------" << endl;
					cout << "                    Current Number of Rooms: "; N_Format(m_vecNumPeoplePerRoom.size()); cout << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "            Room["; N_Format(iRoomNum); cout << "] " << m_vecNumPeoplePerRoom[stoi(m_strUserInput) - 1] << " people ==> ???? people" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "        " << "How many?" << endl;
					cout << "-------------------------------------------------------------------" << endl;
					cout << "-------------------------------------------------------------------" << endl;

					if (!Prompt_User(1, 4))
					{
						continue;
					}

					m_vecNumPeoplePerRoom[iRoomNum - 1] = stoi(m_strUserInput);

					Recalc_num_people();
					return;
				}
			}
		}
		break;
		case 2:
			return;
		default:
			break;
		}
	}



}

void CHotelSearchInterface::Show_SearchDisplay(void)
{
	//system("clear");

	 int iNumOfRooms = m_vecNumPeoplePerRoom.size();
	cout << "-------------------------------------------------------------------" << endl;
	cout << "-                                                          --------" << endl;
	cout << "--        1. Choose Location                                -------" << endl;
	cout << "---        2. Choose Check-In Date                           ------" << endl;
	cout << "----        3. Choose Check-Out Date                          -----" << endl;
	cout << "-----        4. Choose Number of Rooms                         ----" << endl;
	cout << "------        5. Choose Number of People                        ---" << endl;
	cout << "-------        6. Confirm Choice                                 --" << endl;
	cout << "--------        7. Choose Suggested Room                          -" << endl;
	cout << "---------        8. Go Back Login Page                             " << endl;
	cout << "----------        " << endl;
	cout << "-----------        Location             : ";
	cout << m_strLocation;
	cout << endl;
	cout << "------------        Check-In Date       : ";
	cout << m_iCheckInYear << "-"; 
	N_Format(m_iCheckInMonth);
	cout << "-" ;
	N_Format(m_iCheckInDay); 
	cout << " " << m_iCheckInHour << ":" << m_iCheckInMinute << "A.M.";
	cout << endl;
	cout << "-------------        Check-Out Date     : ";
	cout << m_iCheckOutYear << "-" ; 
	N_Format(m_iCheckOutMonth);
	cout << "-" ; 
	N_Format(m_iCheckOutDay); 
	cout << " " << m_iCheckOutHour << ":" << m_iCheckOutMinute << "A.M.";
	cout << endl;
	cout << "--------------        Number of Rooms   : ";
	N_Format(iNumOfRooms);
	cout << endl;
	cout << "--------------        Number of People : ";
	N_Format(m_iNumberOfPeople);
	cout << endl;
	cout << "--------------       " << endl;
	for ( int i = 0; i < iNumOfRooms; ++i)
	{
		cout << "--------------        Room ["; N_Format(i + 1); cout << "]         : " << m_vecNumPeoplePerRoom[i] << " People" << endl;
	}

}

bool CHotelSearchInterface::Prompt_User(int _iMin, int _iMax,  int _imaxstrlen)
{
	//(*_pfunc)(); 

	// take user choice until valid number from min to max
	cout << "Enter your choice (" << _iMin << " to " << _iMax << "): ";
	cin >> m_strUserInput;

	if (m_strUserInput.length() > _imaxstrlen)
	{
		return false;
	}

	if (!Check_IfNumber(m_strUserInput))
	{
		return false;
	}

	// check if from min to max
	if (stoi(m_strUserInput) >= _iMin && stoi(m_strUserInput) <= _iMax)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CHotelSearchInterface::Check_IfNumber(std::string str)
{
	for ( int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}

void CHotelSearchInterface::Default_CheckOutDay(void)
{
	// default checkout day 48hours later
	// months that have 31 days 
	// 1, 3, 5, 7,8, 10, 12
	// months that have 28
	// 2
	// months that have 30 days
	bool bMonthChanged = false;

	switch (m_iCheckInMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if ((m_iCheckInDay + 2) > 31)
		{
			m_iCheckOutDay = (m_iCheckInDay + 2) - 31;
			bMonthChanged = true;
		}
		else
		{
			m_iCheckOutDay = m_iCheckInDay + 2;
		}
		break;
	case 2:
		if ((m_iCheckInDay + 2) > 28)
		{
			m_iCheckOutDay = (m_iCheckInDay + 2) - 28;
			bMonthChanged = true;
		}
		else
		{
			m_iCheckOutDay = m_iCheckInDay + 2;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if ((m_iCheckInDay + 2) > 30)
		{
			m_iCheckOutDay = (m_iCheckInDay + 2) - 30;
			bMonthChanged = true;
		}
		else
		{
			m_iCheckOutDay = m_iCheckInDay + 2;
		}
		break;
	default:
		cout << "error in default day " << endl;
		break;
	}

	if (bMonthChanged == true)
	{
		if ((m_iCheckInMonth + 1) > 12)
		{
			m_iCheckOutMonth = 1;
			m_iCheckOutYear = m_iCheckInYear + 1;
		}
		else
		{
			m_iCheckOutMonth = m_iCheckInMonth + 1;
			m_iCheckOutYear = m_iCheckInYear;
		}
	}
	else
	{
		m_iCheckOutMonth = m_iCheckInMonth;
		m_iCheckOutYear = m_iCheckInYear;
	}
	m_iCheckOutHour = m_iCheckInHour;
	m_iCheckOutMinute = m_iCheckInMinute;
}

void CHotelSearchInterface::Recalc_num_people(void)
{
	 int isize = m_vecNumPeoplePerRoom.size();
	m_iNumberOfPeople = 0;
	for ( int i = 0; i < isize; ++i)
	{
		m_iNumberOfPeople += m_vecNumPeoplePerRoom[i];
	}
}

void CHotelSearchInterface::N_Format(int _iDigit)
{
	if (_iDigit < 10)
	{
		cout << "0" << _iDigit;
	}
	else
	{
		cout << _iDigit;
	}
}

void CHotelSearchInterface::Clear_ResultMap(void)
{
	for (auto pmap : m_mapvecRoomNumbers)
	{
		pmap.second.clear();
		pmap.second.shrink_to_fit();
	}
	m_mapvecRoomNumbers.clear();
}

void CHotelSearchInterface::Clear_ResultVector(void)
{
	m_vecResultHotels.clear();
	m_vecResultHotels.shrink_to_fit();
}

int CHotelSearchInterface::Compare_Dates(int _SrcYear, int _SrcMonth, int _SrcDay, int _DstYear, int _DstMonth, int _DstDay)
{
	// compare year first
	if (_SrcYear > _DstYear)
	{
		return 1;  // src older
	}
	else if (_SrcYear < _DstYear)
	{
		return -1; // src younger
	}
	else if (_SrcYear == _DstYear)
	{
		// then compare month

		if (_SrcMonth > _DstMonth)
		{
			return 1;  // src older
		}
		else if (_SrcMonth < _DstMonth)
		{
			return -1; // src younger
		}
		else if (_SrcMonth == _DstMonth)
		{
			// then day
			if (_SrcDay > _DstDay)
			{
				return 1;  // src older
			}
			else if (_SrcDay < _DstDay)
			{
				return -1; // src younger
			}
			else if (_SrcDay == _DstDay)
			{
				return 0;  // same
			}
		}
	}
	return 0;  // same // can't really reach here
}

CHotel * CHotelSearchInterface::Get_SelectedHotel(void)
{
	if (nullptr != m_pHotelThatIsSelected)
	{
		return m_pHotelThatIsSelected;
	}

	return nullptr;
}

int CHotelSearchInterface::Get_SelectedNumPeople(void)
{
	Recalc_num_people();
	return m_iNumberOfPeople;
}

std::vector<std::string>* CHotelSearchInterface::Get_Cities(void)
{
	return &m_vecCities;
}

bool CHotelSearchInterface::CheckSuggChosen(void)
{
	return m_bCheckIfWeAreUsingSuggested;
}

void CHotelSearchInterface::UseSuggChoice(void)
{
	if (m_pSuggInterface != nullptr)
	{
		m_pHotelThatIsSelected = m_pSuggInterface->Grab_SuggHotel();
	}
	else
	{
		cout << "sugg interface is null" << endl;
		m_pHotelThatIsSelected = nullptr;
	}
}

void CHotelSearchInterface::MoreSearchOptions(void)
{
	// display more search option
	while (true)
	{
		Adv_DisplayCheckMenu();
		if (!Prompt_User(1, 5))
		{
			continue;
		}
		switch (stoi(m_strUserInput))
		{
		case 1: // pet allowed
			if (m_bSearchPetAllowed)
			{
				m_bSearchPetAllowed = false;
				if (m_bSearchPetAllowed == false && m_bSearchSmokeAllowed == false && m_bSearchRatingAllowed == false)
				{
					m_bCheckUseAdvfilters = false;
				}
			}
			else
			{
				m_bSearchPetAllowed = true;
				m_bCheckUseAdvfilters = true;
			}
			break;
		case 2: // smoking allowed
			if (m_bSearchSmokeAllowed)
			{
				m_bSearchSmokeAllowed = false;
				if (m_bSearchPetAllowed == false && m_bSearchSmokeAllowed == false && m_bSearchRatingAllowed == false)
				{
					m_bCheckUseAdvfilters = false;
				}
			}
			else
			{
				m_bSearchSmokeAllowed = true;
				m_bCheckUseAdvfilters = true;
			}
			break;
		case 3: // rating allowed
			if (m_bSearchRatingAllowed)
			{
				m_bSearchRatingAllowed = false;
				if (m_bSearchPetAllowed == false && m_bSearchSmokeAllowed == false && m_bSearchRatingAllowed == false)
				{
					m_bCheckUseAdvfilters = false;
				}
			}
			else
			{
				m_bSearchRatingAllowed = true;
				m_bCheckUseAdvfilters = true;
			}
			break;
		case 4: // change rating setting
			Adv_ChangeRatingSettings();
			break;
		case 5: // go back
			return;
		default:
			cout << "Error" << endl;
			//system("pause");
			break;
		}
	}
}

void CHotelSearchInterface::Adv_DisplayCheckMenu(void)
{
	system("clear");
	cout << "-------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "------                                                       ------" << endl;
	cout << "------           1. ["; if (m_bSearchPetAllowed) { cout << "O"; }
	else { cout << " " ; }
	cout << "] Pet   Allowed                    " << endl;
	cout << "------           2. ["; if (m_bSearchSmokeAllowed) { cout << "O"; }
	else { cout << " " ; }
	cout << "] Smoke Allowed                   " << endl;
	cout << "------           3. ["; if (m_bSearchRatingAllowed) { cout << "O"; }
	else { cout << " "; }
	cout << "] Rating           " << endl;
	cout << "------              Current Rating Minimum: " << m_iCurrMinRating << "   " << endl;
	cout << "------                                                      " << endl;
	cout << "------           4. Change Rating Setting " << endl;
	cout << "------           5 . Go back                               " << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------" << endl << endl;
}

void CHotelSearchInterface::Adv_ChangeRatingSettings(void)
{
	while (true)
	{
		system("clear");
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "------              Current Rating Minimum :" << m_iCurrMinRating << "    " << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------" << endl<< endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "------              Type To Change Current Rating           " << endl;
		cout << "-------------------------------------------------------------------" << endl << endl;

		if (!Prompt_User(0, 5))
		{
			continue;
		}
		m_iCurrMinRating = stoi(m_strUserInput);
		break;
	}
}

bool CHotelSearchInterface::Get_UsedAdvOption(void)
{
	return m_bUsedAdvOption;
}

void CHotelSearchInterface::Set_UsedAdvOption(bool _bOpt)
{
	m_bUsedAdvOption = _bOpt;
}


