//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// definitions of hotel methods
// A lot of data parsing 
// and iterating STL containers
//////////////////////////////////////////////////////////////
#include "HotelManager.h"

#include "Defines.h"

#include "BookingManager.h"
#include "HotelSpecContainer.h"

#include "Hotel.h"
#include "Room.h"

using namespace std;

CHotelManager::CHotelManager(void)
	: m_pBookingManager(NULL)
	, m_iNumHotels(0)
{
}

CHotelManager::~CHotelManager(void)
{
	Save_Manager(); //works.

	Clean_Manager();
}

void CHotelManager::Init_Manager(CBookingManager * _pBookingManager)
{
	m_pBookingManager = _pBookingManager;

	if (Load_Manager()) // load existing data
	{
		//cout << "load successful" << endl;
	}
	else
	{
		//cout << "load unsuccessful" << endl;
		//system("pause");
	}

	// for testing
	//Save_Manager(); //works.



}

bool CHotelManager::Create_Hotel(CUser * _pUser)
{
	return false;
}

bool CHotelManager::Remove_Hotel(std::string _strHotelID)
{
	return false;
}

bool CHotelManager::Modify_Hotel(std::string _strHotelID)
{
	return false;
}

CHotel* CHotelManager::Find_Hotel(std::string _strHotelID)
{
	CHotel* hotel = nullptr;
	int id = 0;

	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_vec = iter_map->second.begin(); iter_vec != iter_map->second.end(); ++iter_vec)
		{
			// your code
			id = (*iter_vec)->Get_HotelRegID();
			std::string str_ID = std::to_string(id);
			if (str_ID == _strHotelID)
			{
				hotel = (*iter_vec);
				return hotel;
			}
		}
	}
	return hotel;
}

void CHotelManager::Partner_CreateHotel(std::string _strLocation, std::string _strHotelName, int _iNumberOfRooms,
	int _iNumSmall, int _iNumMid, int _iNumBig, int _iNumHuge, 
	float _fpriceSmall, float _fpriceMid, float _fpriceBig, float _fpriceHuge,
	int _iHotelID, int _iPartnerID, bool _bPetFri, bool _bSmokeFri)
{
	CHotelSpecContainer* pHotelSpec = new CHotelSpecContainer;
	pHotelSpec->setOwnderID(_iPartnerID);
	pHotelSpec->setHotelReg(_iHotelID);
	pHotelSpec->setLocation(_strLocation);
	pHotelSpec->setHotelName(_strHotelName);
	pHotelSpec->setNumOfRoom(_iNumberOfRooms);
	pHotelSpec->setHotelCode("0");
	
	mt19937 genRand(m_randomDevice());
	uniform_int_distribution<int> randIntValue(0,5);

	pHotelSpec->setRating(randIntValue(genRand));

	CHotel* pHotel = new CHotel(pHotelSpec);

	CRoom* pRoom = nullptr;

	int iRoomNUmber = 1;
	// small
	for (int i = 0; i < _iNumSmall; ++i)
	{
		pRoom = new CRoom;

		//int m_iRoomNumber;
		pRoom->Set_RoomNumber(iRoomNUmber++);
		//int m_iBookingStatus;
		pRoom->Set_BookingStatus(0);
		//int m_iBedNumber;
		pRoom->Set_BedNumber(1);

		pRoom->Set_Occupant("empty");

		//float m_fCost;
		pRoom->Set_Cost(_fpriceSmall);

		//std::string m_strRoomSize;
		pRoom->Set_RoomSize(CRoom::eROOMSIZE::SIZE_SMALL);

		//int m_iCheckInYear;
		pRoom->Set_CheckInYear(2020);
		//int m_iCheckInMonth;
		pRoom->Set_CheckInMonth(1);
		//int m_iCheckInDay;
		pRoom->Set_CheckInDay(2);
		//int m_iCheckInHour;
		pRoom->Set_CheckInHour(3);
		//int m_iCheckInMinute;
		pRoom->Set_CheckInMinute(4);

		//int m_iCheckOutYear;
		pRoom->Set_CheckOutYear(2100);
		//int m_iCheckOutMonth;
		pRoom->Set_CheckOutMonth(1);
		//int m_iCheckOutDay;
		pRoom->Set_CheckOutDay(2);
		//int m_iCheckOutHour;
		pRoom->Set_CheckOutHour(3);
		//int m_iCheckOutMinute;
		pRoom->Set_CheckOutMinute(4);

		// recently added
		//bool m_bPetAllowed;
		pRoom->Set_PetAllowed(_bPetFri);
		//bool m_bSmokeAllowed;
		pRoom->Set_SmokeAllowed(_bSmokeFri);

		pHotel->PushTo_Vector(pRoom);
	}

	// mid
	for (int i = 0; i < _iNumMid; ++i)
	{
		pRoom = new CRoom;

		//int m_iRoomNumber;
		pRoom->Set_RoomNumber(iRoomNUmber++);
		//int m_iBookingStatus;
		pRoom->Set_BookingStatus(0);
		//int m_iBedNumber;
		pRoom->Set_BedNumber(2);

		pRoom->Set_Occupant("empty");

		//float m_fCost;
		pRoom->Set_Cost(_fpriceMid);

		//std::string m_strRoomSize;
		pRoom->Set_RoomSize(CRoom::eROOMSIZE::SIZE_MID);

		//int m_iCheckInYear;
		pRoom->Set_CheckInYear(2020);
		//int m_iCheckInMonth;
		pRoom->Set_CheckInMonth(1);
		//int m_iCheckInDay;
		pRoom->Set_CheckInDay(2);
		//int m_iCheckInHour;
		pRoom->Set_CheckInHour(3);
		//int m_iCheckInMinute;
		pRoom->Set_CheckInMinute(4);

		//int m_iCheckOutYear;
		pRoom->Set_CheckOutYear(2100);
		//int m_iCheckOutMonth;
		pRoom->Set_CheckOutMonth(1);
		//int m_iCheckOutDay;
		pRoom->Set_CheckOutDay(2);
		//int m_iCheckOutHour;
		pRoom->Set_CheckOutHour(3);
		//int m_iCheckOutMinute;
		pRoom->Set_CheckOutMinute(4);

		// recently added
		//bool m_bPetAllowed;
		pRoom->Set_PetAllowed(_bPetFri);
		//bool m_bSmokeAllowed;
		pRoom->Set_SmokeAllowed(_bSmokeFri);

		pHotel->PushTo_Vector(pRoom);
	}

	// big
	for (int i = 0; i < _iNumBig; ++i)
	{
		pRoom = new CRoom;

		//int m_iRoomNumber;
		pRoom->Set_RoomNumber(iRoomNUmber++);
		//int m_iBookingStatus;
		pRoom->Set_BookingStatus(0);
		//int m_iBedNumber;
		pRoom->Set_BedNumber(3);

		pRoom->Set_Occupant("empty");

		//float m_fCost;
		pRoom->Set_Cost(_fpriceBig);

		//std::string m_strRoomSize;
		pRoom->Set_RoomSize(CRoom::eROOMSIZE::SIZE_BIG);

		//int m_iCheckInYear;
		pRoom->Set_CheckInYear(2020);
		//int m_iCheckInMonth;
		pRoom->Set_CheckInMonth(1);
		//int m_iCheckInDay;
		pRoom->Set_CheckInDay(2);
		//int m_iCheckInHour;
		pRoom->Set_CheckInHour(3);
		//int m_iCheckInMinute;
		pRoom->Set_CheckInMinute(4);

		//int m_iCheckOutYear;
		pRoom->Set_CheckOutYear(2100);
		//int m_iCheckOutMonth;
		pRoom->Set_CheckOutMonth(1);
		//int m_iCheckOutDay;
		pRoom->Set_CheckOutDay(2);
		//int m_iCheckOutHour;
		pRoom->Set_CheckOutHour(3);
		//int m_iCheckOutMinute;
		pRoom->Set_CheckOutMinute(4);

		// recently added
		//bool m_bPetAllowed;
		pRoom->Set_PetAllowed(_bPetFri);
		//bool m_bSmokeAllowed;
		pRoom->Set_SmokeAllowed(_bSmokeFri);

		pHotel->PushTo_Vector(pRoom);
	}

	// huge
	for (int i = 0; i < _iNumHuge; ++i)
	{
		pRoom = new CRoom;

		//int m_iRoomNumber;
		pRoom->Set_RoomNumber(iRoomNUmber++);
		//int m_iBookingStatus;
		pRoom->Set_BookingStatus(0);
		//int m_iBedNumber;
		pRoom->Set_BedNumber(4);

		pRoom->Set_Occupant("empty");

		//float m_fCost;
		pRoom->Set_Cost(_fpriceHuge);

		//std::string m_strRoomSize;
		pRoom->Set_RoomSize(CRoom::eROOMSIZE::SIZE_HUGE);

		//int m_iCheckInYear;
		pRoom->Set_CheckInYear(2020);
		//int m_iCheckInMonth;
		pRoom->Set_CheckInMonth(1);
		//int m_iCheckInDay;
		pRoom->Set_CheckInDay(2);
		//int m_iCheckInHour;
		pRoom->Set_CheckInHour(3);
		//int m_iCheckInMinute;
		pRoom->Set_CheckInMinute(4);

		//int m_iCheckOutYear;
		pRoom->Set_CheckOutYear(2100);
		//int m_iCheckOutMonth;
		pRoom->Set_CheckOutMonth(1);
		//int m_iCheckOutDay;
		pRoom->Set_CheckOutDay(2);
		//int m_iCheckOutHour;
		pRoom->Set_CheckOutHour(3);
		//int m_iCheckOutMinute;
		pRoom->Set_CheckOutMinute(4);

		// recently added
		//bool m_bPetAllowed;
		pRoom->Set_PetAllowed(_bPetFri);
		//bool m_bSmokeAllowed;
		pRoom->Set_SmokeAllowed(_bSmokeFri);

		pHotel->PushTo_Vector(pRoom);
	}
	m_mapvecHotels[_strLocation].emplace_back(pHotel);

	++m_iNumHotels;

	Save_Manager(); //save everytime we create it.
}


void CHotelManager::Partner_DeleteHotel(int _iOwnderID, int _iHotelID)
{
	if (m_mapvecHotels.empty())
	{
		cout << "map empty" << endl;
		return;
	}

	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_vec = iter_map->second.begin(); iter_vec != iter_map->second.end(); ++iter_vec)
		{
			if (((*iter_vec)->Get_HotelRegID() == _iHotelID) && ((*iter_vec)->Get_OwnderID() == _iOwnderID))
			{
				// delete it
				iter_map->second.erase(iter_vec);

				--m_iNumHotels;

				Save_Manager(); // save file
				return;
			}
		}
	}
}

void CHotelManager::Partner_ChangeHotelName(int _iOwnderID, int _iHotelID, std::string _strHotelName)
{
	if (m_mapvecHotels.empty())
	{
		cout << "map empty" << endl;
		return;
	}

	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_vec = iter_map->second.begin(); iter_vec != iter_map->second.end(); ++iter_vec)
		{
			if (((*iter_vec)->Get_HotelRegID() == _iHotelID) && ((*iter_vec)->Get_OwnderID() == _iOwnderID))
			{
				(*iter_vec)->Set_HotelName(_strHotelName);

				Save_Manager(); // save file
				return;
			}
		}
	}
}

void CHotelManager::Partner_ChangeLocation(int _iOwnderID, int _iHotelID, std::string _strLocation)
{
	if (m_mapvecHotels.empty())
	{
		cout << "map empty" << endl;
		return;
	}

	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_vec = iter_map->second.begin(); iter_vec != iter_map->second.end(); ++iter_vec)
		{
			if (((*iter_vec)->Get_HotelRegID() == _iHotelID) && ((*iter_vec)->Get_OwnderID() == _iOwnderID))
			{
				(*iter_vec)->Set_Location(_strLocation);

				Save_Manager(); // save file
				return;
			}
		}
	}
}

void CHotelManager::Partner_ChangePet(int _iOwnderID, int _iHotelID, bool _bPetFriendly)
{
	if (m_mapvecHotels.empty())
	{
		cout << "map empty" << endl;
		return;
	}

	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_vec = iter_map->second.begin(); iter_vec != iter_map->second.end(); ++iter_vec)
		{
			if (((*iter_vec)->Get_HotelRegID() == _iHotelID) && ((*iter_vec)->Get_OwnderID() == _iOwnderID))
			{
				// change all pets for all rooms

				auto pVector = (*iter_vec)->Get_RoomVector();

				for (auto pRoom = pVector->begin(); pRoom != pVector->end(); ++pRoom)
				{
					(*pRoom)->Set_PetAllowed(_bPetFriendly);
				}

				Save_Manager(); // save file
				return;
			}
		}
	}
}

void CHotelManager::Partner_ChangeSmoke(int _iOwnderID, int _iHotelID, bool _bSmokeFriendly)
{
	if (m_mapvecHotels.empty())
	{
		cout << "map empty" << endl;
		return;
	}

	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_vec = iter_map->second.begin(); iter_vec != iter_map->second.end(); ++iter_vec)
		{
			if (((*iter_vec)->Get_HotelRegID() == _iHotelID) && ((*iter_vec)->Get_OwnderID() == _iOwnderID))
			{
				// change all pets for all rooms

				auto pVector = (*iter_vec)->Get_RoomVector();

				for (auto pRoom = pVector->begin(); pRoom != pVector->end(); ++pRoom)
				{
					(*pRoom)->Set_SmokeAllowed(_bSmokeFriendly);
				}

				Save_Manager(); // save file
				return;
			}
		}
	}
}

void CHotelManager::Partner_ChangeRooms(int _iOwnderID, int _iHotelID,
	int _iNumSmall, int _iNumMid, int _iNumBig, int _iNumHuge, 
	float _fpriceSmall, float _fpriceMid, float _fpriceBig, float _fpriceHuge,
	bool _bPetFriendly, bool _bSmokeFriendly)
{
	if (m_mapvecHotels.empty())
	{
		cout << "map empty" << endl;
		return;
	}

	CRoom* pRoom = nullptr;

	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_vec = iter_map->second.begin(); iter_vec != iter_map->second.end(); ++iter_vec)
		{
			if (((*iter_vec)->Get_HotelRegID() == _iHotelID) && ((*iter_vec)->Get_OwnderID() == _iOwnderID))
			{
				auto pVector = (*iter_vec)->Get_RoomVector();

				// delete the whole vector
				// and then make new rooms
				for (auto iter = pVector->begin(); iter != pVector->end(); ++iter)
				{
					delete (*iter);
				}
				pVector->clear();
				pVector->shrink_to_fit();


				(*iter_vec)->Set_NumberOfRooms((_iNumSmall + _iNumMid + _iNumBig + _iNumHuge));
					int iRoomNUmber = 1;
				// small
				for (int i = 0; i < _iNumSmall; ++i)
				{
					pRoom = new CRoom;

					//int m_iRoomNumber;
					pRoom->Set_RoomNumber(iRoomNUmber++);
					//int m_iBookingStatus;
					pRoom->Set_BookingStatus(0);
					//int m_iBedNumber;
					pRoom->Set_BedNumber(1);

					pRoom->Set_Occupant("empty");

					//float m_fCost;
					pRoom->Set_Cost(_fpriceSmall);

					//std::string m_strRoomSize;
					pRoom->Set_RoomSize(CRoom::eROOMSIZE::SIZE_SMALL);

					//int m_iCheckInYear;
					pRoom->Set_CheckInYear(2020);
					//int m_iCheckInMonth;
					pRoom->Set_CheckInMonth(1);
					//int m_iCheckInDay;
					pRoom->Set_CheckInDay(2);
					//int m_iCheckInHour;
					pRoom->Set_CheckInHour(3);
					//int m_iCheckInMinute;
					pRoom->Set_CheckInMinute(4);

					//int m_iCheckOutYear;
					pRoom->Set_CheckOutYear(2100);
					//int m_iCheckOutMonth;
					pRoom->Set_CheckOutMonth(1);
					//int m_iCheckOutDay;
					pRoom->Set_CheckOutDay(2);
					//int m_iCheckOutHour;
					pRoom->Set_CheckOutHour(3);
					//int m_iCheckOutMinute;
					pRoom->Set_CheckOutMinute(4);

					// recently added
					//bool m_bPetAllowed;
					pRoom->Set_PetAllowed(_bPetFriendly);
					//bool m_bSmokeAllowed;
					pRoom->Set_SmokeAllowed(_bSmokeFriendly);

					(*iter_vec)->PushTo_Vector(pRoom);
				}

				// mid
				for (int i = 0; i < _iNumMid; ++i)
				{
					pRoom = new CRoom;

					//int m_iRoomNumber;
					pRoom->Set_RoomNumber(iRoomNUmber++);
					//int m_iBookingStatus;
					pRoom->Set_BookingStatus(0);
					//int m_iBedNumber;
					pRoom->Set_BedNumber(2);

					pRoom->Set_Occupant("empty");

					//float m_fCost;
					pRoom->Set_Cost(_fpriceMid);

					//std::string m_strRoomSize;
					pRoom->Set_RoomSize(CRoom::eROOMSIZE::SIZE_MID);

					//int m_iCheckInYear;
					pRoom->Set_CheckInYear(2020);
					//int m_iCheckInMonth;
					pRoom->Set_CheckInMonth(1);
					//int m_iCheckInDay;
					pRoom->Set_CheckInDay(2);
					//int m_iCheckInHour;
					pRoom->Set_CheckInHour(3);
					//int m_iCheckInMinute;
					pRoom->Set_CheckInMinute(4);

					//int m_iCheckOutYear;
					pRoom->Set_CheckOutYear(2100);
					//int m_iCheckOutMonth;
					pRoom->Set_CheckOutMonth(1);
					//int m_iCheckOutDay;
					pRoom->Set_CheckOutDay(2);
					//int m_iCheckOutHour;
					pRoom->Set_CheckOutHour(3);
					//int m_iCheckOutMinute;
					pRoom->Set_CheckOutMinute(4);

					// recently added
					//bool m_bPetAllowed;
					pRoom->Set_PetAllowed(_bPetFriendly);
					//bool m_bSmokeAllowed;
					pRoom->Set_SmokeAllowed(_bSmokeFriendly);

					(*iter_vec)->PushTo_Vector(pRoom);
				}

				// big
				for (int i = 0; i < _iNumBig; ++i)
				{
					pRoom = new CRoom;

					//int m_iRoomNumber;
					pRoom->Set_RoomNumber(iRoomNUmber++);
					//int m_iBookingStatus;
					pRoom->Set_BookingStatus(0);
					//int m_iBedNumber;
					pRoom->Set_BedNumber(3);

					pRoom->Set_Occupant("empty");

					//float m_fCost;
					pRoom->Set_Cost(_fpriceBig);

					//std::string m_strRoomSize;
					pRoom->Set_RoomSize(CRoom::eROOMSIZE::SIZE_BIG);

					//int m_iCheckInYear;
					pRoom->Set_CheckInYear(2020);
					//int m_iCheckInMonth;
					pRoom->Set_CheckInMonth(1);
					//int m_iCheckInDay;
					pRoom->Set_CheckInDay(2);
					//int m_iCheckInHour;
					pRoom->Set_CheckInHour(3);
					//int m_iCheckInMinute;
					pRoom->Set_CheckInMinute(4);

					//int m_iCheckOutYear;
					pRoom->Set_CheckOutYear(2100);
					//int m_iCheckOutMonth;
					pRoom->Set_CheckOutMonth(1);
					//int m_iCheckOutDay;
					pRoom->Set_CheckOutDay(2);
					//int m_iCheckOutHour;
					pRoom->Set_CheckOutHour(3);
					//int m_iCheckOutMinute;
					pRoom->Set_CheckOutMinute(4);

					// recently added
					//bool m_bPetAllowed;
					pRoom->Set_PetAllowed(_bPetFriendly);
					//bool m_bSmokeAllowed;
					pRoom->Set_SmokeAllowed(_bSmokeFriendly);

					(*iter_vec)->PushTo_Vector(pRoom);
				}

				// huge
				for (int i = 0; i < _iNumHuge; ++i)
				{
					pRoom = new CRoom;

					//int m_iRoomNumber;
					pRoom->Set_RoomNumber(iRoomNUmber++);
					//int m_iBookingStatus;
					pRoom->Set_BookingStatus(0);
					//int m_iBedNumber;
					pRoom->Set_BedNumber(4);

					pRoom->Set_Occupant("empty");

					//float m_fCost;
					pRoom->Set_Cost(_fpriceHuge);

					//std::string m_strRoomSize;
					pRoom->Set_RoomSize(CRoom::eROOMSIZE::SIZE_HUGE);

					//int m_iCheckInYear;
					pRoom->Set_CheckInYear(2020);
					//int m_iCheckInMonth;
					pRoom->Set_CheckInMonth(1);
					//int m_iCheckInDay;
					pRoom->Set_CheckInDay(2);
					//int m_iCheckInHour;
					pRoom->Set_CheckInHour(3);
					//int m_iCheckInMinute;
					pRoom->Set_CheckInMinute(4);

					//int m_iCheckOutYear;
					pRoom->Set_CheckOutYear(2100);
					//int m_iCheckOutMonth;
					pRoom->Set_CheckOutMonth(1);
					//int m_iCheckOutDay;
					pRoom->Set_CheckOutDay(2);
					//int m_iCheckOutHour;
					pRoom->Set_CheckOutHour(3);
					//int m_iCheckOutMinute;
					pRoom->Set_CheckOutMinute(4);

					// recently added
					//bool m_bPetAllowed;
					pRoom->Set_PetAllowed(_bPetFriendly);
					//bool m_bSmokeAllowed;
					pRoom->Set_SmokeAllowed(_bSmokeFriendly);

					(*iter_vec)->PushTo_Vector(pRoom);
				}

				Save_Manager(); // save file
				return;
			}
		}
	}
}

void CHotelManager::Partner_ChangePrice(int _iOwnderID, int _iHotelID, float _fpriceSmall, float _fpriceMid, float _fpriceBig, float _fpriceHuge)
{
	if (m_mapvecHotels.empty())
	{
		cout << "map empty" << endl;
		return;
	}

	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_vec = iter_map->second.begin(); iter_vec != iter_map->second.end(); ++iter_vec)
		{
			if (((*iter_vec)->Get_HotelRegID() == _iHotelID) && ((*iter_vec)->Get_OwnderID() == _iOwnderID))
			{
				auto pVector = (*iter_vec)->Get_RoomVector();

				for (auto pRoom = pVector->begin(); pRoom != pVector->end(); ++pRoom)
				{
					if ((*pRoom)->Get_RoomSize() == CRoom::eROOMSIZE::SIZE_SMALL)
					{
						(*pRoom)->Set_Cost(_fpriceSmall);
					}
					else if ((*pRoom)->Get_RoomSize() == CRoom::eROOMSIZE::SIZE_MID)
					{
						(*pRoom)->Set_Cost(_fpriceMid);
					}
					else if ((*pRoom)->Get_RoomSize() == CRoom::eROOMSIZE::SIZE_BIG)
					{
						(*pRoom)->Set_Cost(_fpriceBig);
					}
					else if ((*pRoom)->Get_RoomSize() == CRoom::eROOMSIZE::SIZE_HUGE)
					{
						(*pRoom)->Set_Cost(_fpriceHuge);
					}
				}

				Save_Manager(); // save file
				return;
			}
		}
	}
}

bool CHotelManager::Load_Manager(void)
{
	// lets implement this first so we can have data to get started upon

	// format i should save information upon.
	// lets try saving in non binary mode first
	// and then save in binary for security.

	// saving with , between each

	string strFileName = "";
	strFileName = "SaveFileHotel.txt";

	ifstream* fp = new ifstream;
	fp->open(strFileName.c_str());

	char szToken[STRSIZE] = "";

	// check if the file is opend correctly.
	if (!fp->is_open() || fp->fail())
	{
		// failed to open
		cout << "File" << strFileName << "failed to open while load" << endl;
		return false;
	}

	// then each hotel inside map container 
	CHotel* pHotelShell = nullptr;
	// we declare it ouside so we can use it's imformation to emplace
	CHotelSpecContainer* pHotelSpec = nullptr; 
	CRoom* pRoomShell = nullptr;

	char chNewLine = '\0';

	string strNumHotel = "";
	// for the number of Hotels
	Tokenize_Comma(fp, &strNumHotel);
	m_iNumHotels = stoi(strNumHotel);
	
	if ( 0 == m_iNumHotels)// if 0 hotels are in the app
	{
		// dont load
		return true;
	}

	fp->get(chNewLine); // to negate newline

	for (int i = 0; i < m_iNumHotels; ++i)
	{
		Load_Hotel(fp, &pHotelShell, &pHotelSpec);
		fp->get(chNewLine); // to negate newline

		// each rooms per hotel
		//std::vector<CRoom*> m_vecRooms;
		for (int i = 0; i < pHotelSpec->getNumOfRoom(); ++i)
		{
			Load_Room(fp, &pRoomShell);
			pHotelShell->PushTo_Vector(pRoomShell);
			fp->get(chNewLine); // to negate newline
		}

		// then push into map
		//std::map<std::string, std::vector<CHotel*>> m_mapvecHotels;
		m_mapvecHotels[pHotelSpec->getLocation()].emplace_back(pHotelShell);// all the hotels in that location are pushed into the vector for that location
	}

	if (m_mapvecHotels.empty())
	{
		cout << " m_mapHotels map is empty" << endl;
		return false; // if failed to load any.
	}

	fp->close(); // when done close fp
	fp->clear();

	delete fp;

	return true; // if load is successful.
}

bool CHotelManager::Save_Manager(void)
{
	string strFileName = "";
	strFileName = "SaveFileHotel.txt";

	string strIndent = ",";
	char chNewline = '\n';

	ofstream* fp = new ofstream;
	fp->open(strFileName.c_str());

	// check if the file is opend correctly.
	if (!fp->is_open() || fp->fail())
	{
		// failed to open
		cout << "File" << strFileName << "failed to open while save" << endl;
		return false;
	}

	// i guess you dont have to put it into string before saving it on text
	//*fp << to_string(m_iNumHotels) << strIndent;
	*fp << m_iNumHotels << strIndent << chNewline;

	CHotelSpecContainer* pHotelSpec = nullptr;
	vector<CRoom*>* m_pvecRooms = nullptr;
	// std::map<int, CHotel*> m_mapHotels;
	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_map_vec = iter_map->second.begin(); iter_map_vec != iter_map->second.end(); ++iter_map_vec)
		{
			///---------------------- hotelspec
			pHotelSpec = (*iter_map_vec)->Get_HotelSpec();
			Save_Hotel(fp, pHotelSpec);

			*fp << chNewline;// new line per spec
							 //std::vector<CRoom*> m_vecRooms;
							 ///----------------------- room
			m_pvecRooms = (*iter_map_vec)->Get_RoomVector();
			Save_Room(fp, m_pvecRooms);
		}

	}

	fp->close();
	fp->clear();

	delete fp;

	return true;
}

std::vector<CHotel*>* CHotelManager::Get_HotelsBasedOnLocation(std::string _strLocation)
{
	if (m_mapvecHotels[_strLocation].empty())
	{
		// this means that location doesn't exist
		m_mapvecHotels.erase(_strLocation);
		return nullptr; 
	}
	// if it exists then return real vector
	return &(m_mapvecHotels[_strLocation]);
}

bool CHotelManager::Delete_Hotel(std::string _strHotelID)
{
	return false;
}

void CHotelManager::Tokenize_Comma(ifstream* _fp, std::string* _strToken)
{
	char chGet = '\0';
	*_strToken = ""; // reset per new 
	while (true)
	{
		_fp->get(chGet);
		if (EOF == chGet || '\n' == chGet) // if commna got end 
		{
			cout << "ERROR while tokenizing... file is has reached end of file or has met newline" << endl;
			//system("pause");
		}
		if (',' == chGet) // if commna got end 
		{
			break;
		}
		// if not a comman then continue concatinating
		*_strToken += chGet;
	}
}

void CHotelManager::Load_Hotel(ifstream* _fp, CHotel** _pHotel, CHotelSpecContainer** _pHotelSpec)
{
	string strToken = "";
	(*_pHotelSpec) = new CHotelSpecContainer;

	// m_iOwnerID;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setOwnderID(stoi(strToken));
	// m_iHotelReg;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setHotelReg(stoi(strToken));
	// m_iRating;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setRating(stoi(strToken));
	// m_iContractYear;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setContractYear(stoi(strToken));
	// m_iContractRemain;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setContractRemain(stoi(strToken));
	// m_iNumEmployee;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setNumEmployee(stoi(strToken));
	//m_iNumOfRooms;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setNumOfRoom(stoi(strToken));

	// m_fMantainCost;	Tokenize_Comma(fp, strToken);
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setMantainCost(stof(strToken));
	// m_fEarning;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setEarning(stof(strToken));

	// m_strHotelName;Tokenize_Comma(fp, strToken);
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setHotelName(strToken);
	// m_strHotelCode;Tokenize_Comma(fp, strToken);
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setHotelCode(strToken);
	// m_strLocation;
	Tokenize_Comma(_fp, &strToken);
	(*_pHotelSpec)->setLocation(strToken);

	(*_pHotel) = new CHotel((*_pHotelSpec));
}

void CHotelManager::Load_Room(ifstream* _fp, CRoom** _pRoom)
{
	string strToken = "";
	(*_pRoom) = new CRoom;

	//int m_iRoomNumber;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_RoomNumber(stoi(strToken));
	//int m_iBookingStatus;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_BookingStatus(stoi(strToken));
	//int m_iBedNumber;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_BedNumber(stoi(strToken));

	//float m_fCost;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_Cost(stof(strToken));

	//std::string m_strOccupant;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_Occupant(strToken);

	//std::string m_strRoomSize;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_RoomSize(stoi(strToken));

	//int m_iCheckInYear;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckInYear(stoi(strToken));
	//int m_iCheckInMonth;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckInMonth(stoi(strToken));
	//int m_iCheckInDay;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckInDay(stoi(strToken));
	//int m_iCheckInHour;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckInHour(stoi(strToken));
	//int m_iCheckInMinute;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckInMinute(stoi(strToken));
	
	//int m_iCheckOutYear;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckOutYear(stoi(strToken));
	//int m_iCheckOutMonth;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckOutMonth(stoi(strToken));
	//int m_iCheckOutDay;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckOutDay(stoi(strToken));
	//int m_iCheckOutHour;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckOutHour(stoi(strToken));
	//int m_iCheckOutMinute;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_CheckOutMinute(stoi(strToken));

	// recently added
	//bool m_bPetAllowed;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_Save_PetAllowed(stoi(strToken));
	//bool m_bSmokeAllowed;
	Tokenize_Comma(_fp, &strToken);
	(*_pRoom)->Set_Save_SmokeAllowed(stoi(strToken));
}

void CHotelManager::Save_Hotel(ofstream * _fp, CHotelSpecContainer * _pHotelSpec)
{
	string strIndent = ",";
	*_fp << _pHotelSpec->getOwnderID() << strIndent;
	//int m_iHotelReg;
	*_fp << _pHotelSpec->getHotelReg() << strIndent;
	//int m_iRating;
	*_fp << _pHotelSpec->getRating() << strIndent;
	//int m_iContractYear;
	*_fp << _pHotelSpec->getContractYear() << strIndent;
	//int m_iContractRemain;
	*_fp << _pHotelSpec->getContractRemain() << strIndent;
	//int m_iNumEmployee;
	*_fp << _pHotelSpec->getNumEmployee() << strIndent;
	//int m_iNumOfRooms;
	*_fp << _pHotelSpec->getNumOfRoom() << strIndent;
	//float m_fMantainCost;
	*_fp << _pHotelSpec->getMantainCost() << strIndent;
	//float m_fEarning;
	*_fp << _pHotelSpec->getEarning() << strIndent;
	//std::string m_strHotelName;
	*_fp << _pHotelSpec->getHotelName() << strIndent;
	//std::string m_strHotelCode;
	*_fp << _pHotelSpec->getHotelCode() << strIndent;
	//std::string m_strLocation;
	*_fp << _pHotelSpec->getLocation() << strIndent;
}

void CHotelManager::Save_Room(ofstream * _fp, vector<CRoom*>* _pvecRooms)
{
	string strIndent = ",";
	char chNewline = '\n';
	for (auto iter_vec = _pvecRooms->begin(); iter_vec != _pvecRooms->end(); ++iter_vec)
	{
		//int m_iRoomNumber;
		*_fp << (*iter_vec)->Get_RoomNumber() << strIndent;
		//int m_iBookingStatus;
		*_fp << (*iter_vec)->Get_BookingStatus() << strIndent;
		//int m_iBedNumber;
		*_fp << (*iter_vec)->Get_BedNumber() << strIndent;
		//float m_fCost;
		*_fp << (*iter_vec)->Get_Cost() << strIndent;
		//std::string m_strOccupant;
		*_fp << (*iter_vec)->Get_Occupant() << strIndent;
		//eROOMSIZE m_eRoomSize;
		*_fp << (*iter_vec)->Get_RoomSize() << strIndent;
		//int m_iCheckInYear;
		*_fp << (*iter_vec)->Get_CheckInYear() << strIndent;
		//int m_iCheckInMonth;
		*_fp << (*iter_vec)->Get_CheckInMonth() << strIndent;
		//int m_iCheckInDay;
		*_fp << (*iter_vec)->Get_CheckInDay() << strIndent;
		//int m_iCheckInHour;
		*_fp << (*iter_vec)->Get_CheckInHour() << strIndent;
		//int m_iCheckInMinute;
		*_fp << (*iter_vec)->Get_CheckInMinute() << strIndent;
		//int m_iCheckOutYear;
		*_fp << (*iter_vec)->Get_CheckOutYear() << strIndent;
		//int m_iCheckOutMonth;
		*_fp << (*iter_vec)->Get_CheckOutMonth() << strIndent;
		//int m_iCheckOutDay;
		*_fp << (*iter_vec)->Get_CheckOutDay() << strIndent;
		//int m_iCheckOutHour;
		*_fp << (*iter_vec)->Get_CheckOutHour() << strIndent;
		//int m_iCheckOutMinute;
		*_fp << (*iter_vec)->Get_CheckOutMinute() << strIndent;

		// recently added
		//bool m_bPetAllowed;
		*_fp << (*iter_vec)->Get_PetAllowed() << strIndent;
		//bool m_bSmokeAllowed;
		*_fp << (*iter_vec)->Get_SmokeAllowed() << strIndent;

		*_fp << chNewline;// new line per room since notepad limit is only 1024 characters.
	}
}

void CHotelManager::Clean_Manager(void)
{
	//	std::map<std::string, std::vector<CHotel*>> m_mapvecHotels;
	//CBookingManager* m_pBookingManager;
	for (auto iter_map = m_mapvecHotels.begin(); iter_map != m_mapvecHotels.end(); ++iter_map)
	{
		for (auto iter_map_vec = iter_map->second.begin(); iter_map_vec != iter_map->second.end(); ++iter_map_vec)
		{
			delete *iter_map_vec;
		}
		iter_map->second.clear();
		iter_map->second.shrink_to_fit();
	}

	m_mapvecHotels.clear();

	m_pBookingManager = nullptr;
}

std::map<std::string, std::vector<CHotel*>>* CHotelManager::Get_HotelContainer(void)
{
	return &m_mapvecHotels;
}

