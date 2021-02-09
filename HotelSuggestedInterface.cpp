#include "HotelSuggestedInterface.h"

#include "HotelManager.h"
#include "Hotel.h"
#include "Room.h"

#include "HotelSearchInterface.h"

using namespace std;

CHotelSuggInterface::CHotelSuggInterface(CHotelManager * _pHotelManager, CHotelSearchInterface * _pSearchInterface)
	: m_pHotelManager(nullptr)
	, m_pSearchInterface(nullptr)
	, m_pMapVecHotelRooms(nullptr)
	, m_pCities(nullptr)
	, m_iSelValueLocations(0)
	, m_iSelValueHotels(0)
	, m_iSelValueRooms(0)
{
	if (nullptr != _pHotelManager)
	{
		m_pHotelManager = _pHotelManager;
	}

	if (nullptr != m_pSearchInterface)
	{
		m_pSearchInterface = _pSearchInterface;
	}

	Ready_Sugg();
}

CHotelSuggInterface::~CHotelSuggInterface(void)
{
	Clean_Sugg();
}

void CHotelSuggInterface::Ready_Sugg(void)
{
	if (nullptr != m_pHotelManager)
	{
		m_pMapVecHotelRooms = m_pHotelManager->Get_HotelContainer();
	}

	if (nullptr != m_pSearchInterface)
	{
		m_pCities = m_pSearchInterface->Get_Cities();
	}
}

void CHotelSuggInterface::Display_Sugg(void)
{
	Select_Random_HotelRooms();

	cout << "==================================================" << endl;
	cout << "============== SUGGESTED ROOMS ===================" << endl;
	//cout << "Sugg Loc: " << m_iSelValueLocations << endl;
	//cout << "Sugg Hot: " << m_iSelValueHotels << endl;
	//cout << "Sugg Roo: " << m_iSelValueRooms << endl;

	string strHotelName = "";

	auto iter_mapvecLocation = m_pMapVecHotelRooms->begin();

	for (int i = 0; i < m_iSelValueLocations; ++i)
	{
		++iter_mapvecLocation;
	}

	//(*((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels]->Get_RoomVector()))[m_iSelValueRooms]->

	cout << "        " << "Hotel    : " << ((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels])->Get_HotelName() << endl;
	cout << "        " << "Location : " << iter_mapvecLocation->first << endl;
	cout << "        " << "Rating   : " << ((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels])->Get_HotelRating() << endl;
	// display hotel services later when combined with others

	// and room numbers
	cout << "---- Room ["; m_pSearchInterface->N_Format(m_iSelValueRooms + 1); cout << "] : Size ";
	switch ((*((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels]->Get_RoomVector()))[m_iSelValueRooms]->Get_RoomSize())
	{
	case CRoom::eROOMSIZE::SIZE_SMALL:
		cout << "SMALL      Cost : $" << (*((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels]->Get_RoomVector()))[m_iSelValueRooms]->Get_Cost() << endl;
		break;
	case CRoom::eROOMSIZE::SIZE_MID:
		cout << "MIDDLE     Cost : $" << (*((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels]->Get_RoomVector()))[m_iSelValueRooms]->Get_Cost() << endl;
		break;
	case CRoom::eROOMSIZE::SIZE_BIG:
		cout << "BIG        Cost : $" << (*((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels]->Get_RoomVector()))[m_iSelValueRooms]->Get_Cost() << endl;
		break;
	case CRoom::eROOMSIZE::SIZE_HUGE:
		cout << "HUGE       Cost : $" << (*((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels]->Get_RoomVector()))[m_iSelValueRooms]->Get_Cost() << endl;
		break;
	default:
		cout << "error sugg switch" << endl;
		break;
	}

	cout << "==================================================" << endl << endl;
}

CHotel * CHotelSuggInterface::Grab_SuggHotel(void)
{
	auto iter_mapvecLocation = m_pMapVecHotelRooms->begin();

	for (int i = 0; i < m_iSelValueLocations; ++i)
	{
		++iter_mapvecLocation;
	}

	return ((*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels]);
}

void CHotelSuggInterface::Clean_Sugg(void)
{
	m_pHotelManager = nullptr;
	m_pMapVecHotelRooms = nullptr;
	m_pSearchInterface = nullptr;
	m_pCities = nullptr;
}

void CHotelSuggInterface::Select_Random_HotelRooms(void)
{
	// random
	mt19937 genRand(m_randomDevice());

	int iMaxRanValueLocations = 0;
	int iMaxRanValueHotels = 0;
	int iMaxRanValueRooms = 0;

	// regardless of location
	// look in the vector 

	// location
	iMaxRanValueLocations = m_pMapVecHotelRooms->size() - 1;

	auto iter_mapvecLocation = m_pMapVecHotelRooms->begin();

	if (iMaxRanValueLocations > -1)
	{
		// random values from 0 ~ n  // in this case should be num of location
		uniform_int_distribution<int> randIntValue(0, iMaxRanValueLocations);
		m_iSelValueLocations = randIntValue(genRand);

		for (int i = 0; i < m_iSelValueLocations; ++i)
		{
			++iter_mapvecLocation;
		}
	}
	else // if non then error
	{
		cout << "error at randLoc" << endl;
		return;
	}

	// Hotel
	//iMaxRanValueHotels = (*m_pMapVecHotelRooms)[(*m_pCities)[m_iSelValueLocations]].size() - 1;
	iMaxRanValueHotels = (*m_pMapVecHotelRooms)[iter_mapvecLocation->first].size() - 1;

	if (iMaxRanValueHotels > -1)
	{
		// random values from 0 ~ n
		uniform_int_distribution<int> randIntValue(0, iMaxRanValueHotels);
		m_iSelValueHotels = randIntValue(genRand);
	}
	else // if non then error
	{
		cout << "error at randHotel" << endl;
		return;
	}

	// Room
	iMaxRanValueRooms = (*m_pMapVecHotelRooms)[iter_mapvecLocation->first][m_iSelValueHotels]->Get_RoomVector()->size() - 1;

	if (iMaxRanValueRooms > -1)
	{
		// random values from 0 ~ n  
		uniform_int_distribution<int> randIntValue(0, iMaxRanValueRooms);
		m_iSelValueRooms = randIntValue(genRand);
	}
	else // if non then error
	{
		cout << "error at randroom" << endl;
		return;
	}

	// since at this point we've selected random room
	// on the basis that they exist
	// we now have to use that data to show 
}
