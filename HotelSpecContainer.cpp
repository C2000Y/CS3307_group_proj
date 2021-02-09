//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// setters and getter
//////////////////////////////////////////////////////////////
#include "HotelSpecContainer.h"

CHotelSpecContainer::CHotelSpecContainer(void)
	: m_iOwnerID(0)
	, m_iHotelReg(0)
	, m_iRating(0)
	, m_iContractYear(0)
	, m_iContractRemain(0)
	, m_iNumEmployee(0)
	, m_iNumOfRooms(0)
	, m_fMantainCost(0.f)
	, m_fEarning(0.f)
	, m_strHotelName("")
	, m_strHotelCode("")
	, m_strLocation("")
{
}

CHotelSpecContainer::~CHotelSpecContainer(void)
{
}

int CHotelSpecContainer::getOwnderID(void)
{
	return m_iOwnerID;
}

int CHotelSpecContainer::getHotelReg(void)
{
	return m_iHotelReg;
}

int CHotelSpecContainer::getRating(void)
{
	return m_iRating;
}

int CHotelSpecContainer::getContractYear(void)
{
	return m_iContractYear;
}

int CHotelSpecContainer::getContractRemain(void)
{
	return m_iContractRemain;
}

int CHotelSpecContainer::getNumEmployee(void)
{
	return m_iNumEmployee;
}

int CHotelSpecContainer::getNumOfRoom(void)
{
	return m_iNumOfRooms;
}

float CHotelSpecContainer::getMantainCost(void)
{
	return m_fMantainCost;
}

float CHotelSpecContainer::getEarning(void)
{
	return m_fEarning;
}

std::string CHotelSpecContainer::getHotelName(void)
{
	return m_strHotelName;
}

std::string CHotelSpecContainer::getHotelCode(void)
{
	return m_strHotelCode;
}

std::string CHotelSpecContainer::getLocation(void)
{
	return m_strLocation;
}

void CHotelSpecContainer::setOwnderID(int _iOwnerID)
{
	m_iOwnerID = _iOwnerID;
}

void CHotelSpecContainer::setHotelReg(int _iHotelReg)
{
	m_iHotelReg = _iHotelReg;
}

void CHotelSpecContainer::setRating(int _iRating)
{
	m_iRating = _iRating;
}

void CHotelSpecContainer::setContractYear(int _iContractYear)
{
	m_iContractYear = _iContractYear;
}

void CHotelSpecContainer::setContractRemain(int _iContractRemain)
{
	m_iContractRemain = _iContractRemain;
}

void CHotelSpecContainer::setNumEmployee(int _iNumEmployee)
{
	m_iNumEmployee = _iNumEmployee;
}

void CHotelSpecContainer::setNumOfRoom(int _iNumOfRoom)
{
	m_iNumOfRooms = _iNumOfRoom;
}

void CHotelSpecContainer::setMantainCost(float _fMantainCost)
{
	m_fMantainCost = _fMantainCost;
}

void CHotelSpecContainer::setEarning(float _fEarning)
{
	m_fEarning = _fEarning;
}

void CHotelSpecContainer::setHotelName(std::string _strHotelName)
{
	m_strHotelName = _strHotelName;
}

void CHotelSpecContainer::setHotelCode(std::string _strHotelCode)
{
	m_strHotelCode = _strHotelCode;
}

void CHotelSpecContainer::setLocation(std::string _strLocation)
{
	m_strLocation = _strLocation;
}

