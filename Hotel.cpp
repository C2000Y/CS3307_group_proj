//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// Hotel method definitions
//////////////////////////////////////////////////////////////
#include "Hotel.h"

#include "Headers.h"
#include "Room.h"
#include "HotelSpecContainer.h"

using namespace std;

CHotel::CHotel(CHotelSpecContainer * _pHotelSpec)
	: m_pRoomShell(NULL)
{
	m_pHotelSpec = _pHotelSpec;

	for (int i = 0; i < ROOMSIZETYPES; ++i)
	{
		m_iNumRoomSize[i] = 0;
	}
}

CHotel::CHotel(void)
	: m_pRoomShell(NULL)
	, m_pHotelSpec(NULL)
{
	for (int i = 0; i < ROOMSIZETYPES; ++i)
	{
		m_iNumRoomSize[i] = 0;
	}
}

CHotel::~CHotel(void)
{
	Clean_Storage();
}

void CHotel::Create_Room_WithSize(int eSize)
{
	m_pRoomShell = new CRoom(m_pHotelSpec->getNumOfRoom() + 1); // room# shouldn't be 0
	m_pRoomShell->Gen_Default_RoomSize(eSize);

	m_vecRooms.emplace_back(m_pRoomShell);
}

void CHotel::PushTo_Vector(CRoom * _pRoom)
{
	m_vecRooms.emplace_back(_pRoom);
}

std::vector<CRoom*>* CHotel::Get_RoomVector(void)
{
	return &m_vecRooms;
}

CHotelSpecContainer * CHotel::Get_HotelSpec(void)
{
	return m_pHotelSpec;
}

void CHotel::Set_HotelName(std::string _strHotelName)
{
	m_pHotelSpec->setHotelName(_strHotelName);
}

void CHotel::Set_Location(std::string _strLocation)
{
	m_pHotelSpec->setLocation(_strLocation);
}

void CHotel::Set_NumberOfRooms(int _iNumRoom)
{
	m_pHotelSpec->setNumOfRoom(_iNumRoom);
}

int CHotel::Get_NumberofRooms(void)
{
	// again have to do this when we pushing to vector but for proto 


	//m_pHotelSpec->setNumOfRoom()

	//m_iNumOfRooms

	return m_pHotelSpec->getNumOfRoom();
}

int CHotel::Get_NumberofSizedRooms(int _iRoomSize)
{
	// go through the rooms and check their sizes

	// need to resett everytime
	for (int i = 0; i < ROOMSIZETYPES; ++i)
	{
		m_iNumRoomSize[i] = 0;
	}

	for (auto iter_vec : m_vecRooms)
	{
		++m_iNumRoomSize[iter_vec->Get_RoomSize()];
	}

	return m_iNumRoomSize[_iRoomSize];
}

int CHotel::Get_HotelRating(void)
{
	return m_pHotelSpec->getRating();
}

float CHotel::Get_RoomCost(int _iRoomSize)
{
	switch (_iRoomSize)
	{
	case CRoom::eROOMSIZE::SIZE_SMALL:
	{
		for (auto piter_vec = m_vecRooms.begin(); piter_vec != m_vecRooms.end(); ++piter_vec)
		{
			if ((*piter_vec)->Get_RoomSize() == CRoom::eROOMSIZE::SIZE_SMALL)
			{
				return (*piter_vec)->Get_Cost();
			}
		}
		// if size doesnt exist return 0
		return 0.f;
	}
	case CRoom::eROOMSIZE::SIZE_MID:
	{
		for (auto piter_vec = m_vecRooms.begin(); piter_vec != m_vecRooms.end(); ++piter_vec)
		{
			if ((*piter_vec)->Get_RoomSize() == CRoom::eROOMSIZE::SIZE_MID)
			{
				return (*piter_vec)->Get_Cost();
			}
		}
		// if size doesnt exist return 0
		return 0.f;
	}
	case CRoom::eROOMSIZE::SIZE_BIG:
	{
		for (auto piter_vec = m_vecRooms.begin(); piter_vec != m_vecRooms.end(); ++piter_vec)
		{
			if ((*piter_vec)->Get_RoomSize() == CRoom::eROOMSIZE::SIZE_BIG)
			{
				return (*piter_vec)->Get_Cost();
			}
		}
		// if size doesnt exist return 0
		return 0.f;
	}
	case CRoom::eROOMSIZE::SIZE_HUGE:
	{
		for (auto piter_vec = m_vecRooms.begin(); piter_vec != m_vecRooms.end(); ++piter_vec)
		{
			if ((*piter_vec)->Get_RoomSize() == CRoom::eROOMSIZE::SIZE_HUGE)
			{
				return (*piter_vec)->Get_Cost();
			}
		}
		// if size doesnt exist return 0
		return 0.f;
	}
	default:
		break;
	}
	return 0.0f;
}

std::string CHotel::Get_HotelName(void)
{
	return m_pHotelSpec->getHotelName();
}

int CHotel::Get_HotelRegID(void)
{
	return  m_pHotelSpec->getHotelReg();
}

int CHotel::Get_OwnderID(void)
{
	return  m_pHotelSpec->getOwnderID();
}

void CHotel::Clean_Storage(void)
{
	//	std::vector<CRoom*> m_vecRooms;
	vector<CRoom*>::iterator iter;

	for (iter = m_vecRooms.begin(); iter != m_vecRooms.end(); ++iter)
	{
		delete (*iter);
	}
	m_vecRooms.clear();
	m_vecRooms.shrink_to_fit();

	//CHotelSpecContainer* m_pHotelSpec;
	delete m_pHotelSpec;
	m_pHotelSpec = nullptr;
	m_pRoomShell = nullptr;
}
