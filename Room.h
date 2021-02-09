//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// Contains all the information regarding a hotel room
// Mostly has setters and getters that are used by other classes such as CHotel
//////////////////////////////////////////////////////////////
#ifndef Room_h__
#define Room_h__

#include "Headers.h"

#define COST_SMALL	111.f
#define COST_MID	222.f
#define COST_BIG	333.f
#define COST_HUGE	444.f

class CRoom
{
public:
	CRoom(int _iRoomNum);
public:
	CRoom(void);
	~CRoom(void);
public:
	enum eROOMSIZE { SIZE_SMALL, SIZE_MID, SIZE_BIG, SIZE_HUGE, SIZE_END};
public:
	enum eROOMBEDNUM
	{
		BEDNUM_SMALL = 1,
		BEDNUM_MID = 2,
		BEDNUM_BIG = 3,
		BEDNUM_HUGE = 4
	};
public:
	enum eROOMINUSE
	{
		STATUS_USE_NOT = 0,
		STATUS_USE_YES = 1
	};

public:
	void  Gen_Default_RoomSize(int _eRoomSize);

public:
	int Get_RoomNumber(void);
	int Get_BookingStatus(void);
	int Get_BedNumber(void);

	float Get_Cost(void);

	std::string Get_Occupant(void);

	eROOMSIZE Get_RoomSize(void);

	int Get_CheckInYear(void);
	int Get_CheckInMonth(void);
	int Get_CheckInDay(void);
	int Get_CheckInHour(void);
	int Get_CheckInMinute(void);

	int Get_CheckOutYear(void);
	int Get_CheckOutMonth(void);
	int Get_CheckOutDay(void);
	int Get_CheckOutHour(void);
	int Get_CheckOutMinute(void);


	// recently added
	bool Get_PetAllowed(void);
	bool Get_SmokeAllowed(void);


public:
	void Set_RoomNumber(int _iRoomNumber);
	void Set_BookingStatus(int _iBookingStatus);
	void Set_BedNumber(int _iBedNumber);

	void Set_Cost(float _fCost);
	
	void Set_Occupant(std::string _strOccupant);

	void Set_RoomSize(int m_eRoomSize);

	void Set_CheckInYear(int _iCheckInYear);
	void Set_CheckInMonth(int _iCheckInMonth);
	void Set_CheckInDay(int _iCheckInDay);
	void Set_CheckInHour(int _iCheckInHour);
	void Set_CheckInMinute(int _iCheckInMinute);

	void Set_CheckOutYear(int _iCheckOutYear);
	void Set_CheckOutMonth(int _iCheckOutMonth);
	void Set_CheckOutDay(int _iCheckOutDay);
	void Set_CheckOutHour(int _iCheckOutHour);
	void Set_CheckOutMinute(int _iCheckOutMinute);

	// recently added

	void Set_PetAllowed(bool _bPet);
	void Set_SmokeAllowed(bool _bSmoke);

	// for save

	void Set_Save_PetAllowed(int _bPet);
	void Set_Save_SmokeAllowed(int _bSmoke);


private:
	int m_iRoomNumber;
	int m_iBookingStatus;
	int m_iBedNumber;

	float m_fCost;

	std::string m_strOccupant;

	eROOMSIZE m_eRoomSize;

	int m_iCheckInYear;
	int m_iCheckInMonth;
	int m_iCheckInDay;
	int m_iCheckInHour;
	int m_iCheckInMinute;

	int m_iCheckOutYear;
	int m_iCheckOutMonth;
	int m_iCheckOutDay;
	int m_iCheckOutHour;
	int m_iCheckOutMinute;

	// recently added

	bool m_bPetAllowed;
	bool m_bSmokeAllowed;
};

#endif

