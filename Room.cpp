//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// initializations, setters and getters.
//////////////////////////////////////////////////////////////
#include "Room.h"
#include "Headers.h"
using namespace std;

CRoom::CRoom(int _iRoomNum)
	: m_iRoomNumber(_iRoomNum)
	, m_iBookingStatus(STATUS_USE_NOT)
	, m_iBedNumber(BEDNUM_SMALL)
	, m_fCost(COST_SMALL)
	, m_eRoomSize(eROOMSIZE::SIZE_END)
	, m_strOccupant("")
	, m_iCheckInYear(0)
	, m_iCheckInMonth(0)
	, m_iCheckInDay(0)
	, m_iCheckInHour(0)
	, m_iCheckInMinute(0)
	, m_iCheckOutYear(0)
	, m_iCheckOutMonth(0)
	, m_iCheckOutDay(0)
	, m_iCheckOutHour(0)
	, m_iCheckOutMinute(0)
	, m_bPetAllowed(false)
	, m_bSmokeAllowed(false)
{
}

CRoom::CRoom(void)
	: m_iRoomNumber(0)
	, m_iBookingStatus(0)
	, m_iBedNumber(0)
	, m_fCost(0.f)
	, m_eRoomSize(eROOMSIZE::SIZE_END)
	, m_strOccupant("")
	, m_iCheckInMonth(0)
	, m_iCheckInDay(0)
	, m_iCheckInHour(0)
	, m_iCheckInMinute(0)
	, m_iCheckOutYear(0)
	, m_iCheckOutMonth(0)
	, m_iCheckOutDay(0)
	, m_iCheckOutHour(0)
	, m_iCheckOutMinute(0)
	, m_bPetAllowed(false)
	, m_bSmokeAllowed(false)
{
}

CRoom::~CRoom(void)
{
}

void CRoom::Gen_Default_RoomSize(int _eRoomSize)
{
	switch (_eRoomSize)
	{
	case eROOMSIZE::SIZE_SMALL:
		m_iBedNumber = BEDNUM_SMALL;
		m_fCost = COST_SMALL;
		m_eRoomSize = eROOMSIZE::SIZE_SMALL;
		break;
	case eROOMSIZE::SIZE_MID:
		m_iBedNumber = BEDNUM_MID;
		m_fCost = COST_MID;
		m_eRoomSize = eROOMSIZE::SIZE_MID;
		break;
	case eROOMSIZE::SIZE_BIG:
		m_iBedNumber = BEDNUM_BIG;
		m_fCost = COST_BIG;
		m_eRoomSize = eROOMSIZE::SIZE_BIG;
		break;
	case eROOMSIZE::SIZE_HUGE:
		m_iBedNumber = BEDNUM_HUGE;
		m_fCost = COST_HUGE;
		m_eRoomSize = eROOMSIZE::SIZE_HUGE;
		break;
	default:
		cout << "Error in default size" << endl;
		//system("pause");
		break;
	}
}

int CRoom::Get_RoomNumber(void)
{
	return m_iRoomNumber;
}

int CRoom::Get_BookingStatus(void)
{
	return m_iBookingStatus;
}

int CRoom::Get_BedNumber(void)
{
	return m_iBedNumber;
}

float CRoom::Get_Cost(void)
{
	return m_fCost;
}

CRoom::eROOMSIZE CRoom::Get_RoomSize(void)
{
	return m_eRoomSize;
}

int CRoom::Get_CheckInYear(void)
{
	return m_iCheckInYear;
}

int CRoom::Get_CheckInMonth(void)
{
	return m_iCheckInMonth;
}

int CRoom::Get_CheckInDay(void)
{
	return m_iCheckInDay;
}

int CRoom::Get_CheckInHour(void)
{
	return m_iCheckInHour;
}

int CRoom::Get_CheckInMinute(void)
{
	return m_iCheckInMinute;
}

int CRoom::Get_CheckOutYear(void)
{
	return m_iCheckOutYear;
}

int CRoom::Get_CheckOutMonth(void)
{
	return m_iCheckOutMonth;
}

int CRoom::Get_CheckOutDay(void)
{
	return m_iCheckOutDay;
}

int CRoom::Get_CheckOutHour(void)
{
	return m_iCheckOutHour;
}

int CRoom::Get_CheckOutMinute(void)
{
	return m_iCheckOutMinute;
}

bool CRoom::Get_PetAllowed(void)
{
	return m_bPetAllowed;
}

bool CRoom::Get_SmokeAllowed(void)
{
	return m_bSmokeAllowed;
}

std::string CRoom::Get_Occupant(void)
{
	return m_strOccupant;
}

void CRoom::Set_RoomNumber(int _iRoomNumber)
{
	m_iRoomNumber = _iRoomNumber;
}

void CRoom::Set_BookingStatus(int _iBookingStatus)
{
	m_iBookingStatus = _iBookingStatus;
}

void CRoom::Set_BedNumber(int _iBedNumber)
{
	m_iBedNumber = _iBedNumber;
}

void CRoom::Set_Cost(float _fCost)
{
	m_fCost = _fCost;
}

void CRoom::Set_RoomSize(int _eRoomSize)
{
	m_eRoomSize = CRoom::eROOMSIZE(_eRoomSize);
}

void CRoom::Set_CheckInYear(int _iCheckInYear)
{
	m_iCheckInYear = _iCheckInYear;
}

void CRoom::Set_CheckInMonth(int _iCheckInMonth)
{
	m_iCheckInMonth = _iCheckInMonth;
}

void CRoom::Set_CheckInDay(int _iCheckInDay)
{
	m_iCheckInDay = _iCheckInDay;
}

void CRoom::Set_CheckInHour(int _iCheckInHour)
{
	m_iCheckInHour = _iCheckInHour;
}

void CRoom::Set_CheckInMinute(int _iCheckInMinute)
{
	m_iCheckInMinute = _iCheckInMinute;
}

void CRoom::Set_CheckOutYear(int _iCheckOutYear)
{
	m_iCheckOutYear = _iCheckOutYear;
}

void CRoom::Set_CheckOutMonth(int _iCheckOutMonth)
{
	m_iCheckOutMonth = _iCheckOutMonth;
}

void CRoom::Set_CheckOutDay(int _iCheckOutDay)
{
	m_iCheckOutDay = _iCheckOutDay;
}

void CRoom::Set_CheckOutHour(int _iCheckOutHour)
{
	m_iCheckOutHour = _iCheckOutHour;
}

void CRoom::Set_CheckOutMinute(int _iCheckOutMinute)
{
	m_iCheckOutMinute = _iCheckOutMinute;
}

void CRoom::Set_PetAllowed(bool _bPet)
{
	m_bPetAllowed = _bPet;
}

void CRoom::Set_SmokeAllowed(bool _bSmoke)
{
	m_bSmokeAllowed = _bSmoke;
}

void CRoom::Set_Save_PetAllowed(int _bPet)
{
	if (_bPet == 1)
	{
		m_bPetAllowed = true;
	}
	else if (_bPet == 0)
	{
		m_bPetAllowed = false;
	}
}

void CRoom::Set_Save_SmokeAllowed(int _bSmoke)
{
	if (_bSmoke == 1)
	{
		m_bSmokeAllowed = true;
	}
	else if (_bSmoke == 0)
	{
		m_bSmokeAllowed = false;
	}
}

void CRoom::Set_Occupant(std::string _strOccupant)
{
	m_strOccupant = _strOccupant;
}
