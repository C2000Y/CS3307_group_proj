////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  Header file for UserGuest.cpp
////////////////////////////////////////////////////////////////////


#ifndef UserGuest_h__
#define UserGuest_h__

#include "Enums.h"
#include "Headers.h"
#include "UserInterface.h" // haoran
#include "User.h"

class CUserGuest : public CUser
{
public:
	CUserGuest();
	virtual ~CUserGuest();

public:
	int getRoomNumber();

	std::string getRegisteredHotel();
	std::string getParkingSpot();
	std::string getLocation();
	std::string getBookingReference();

	eMEMBERSHIP getMemberRank();

	bool getIsBooked();
	bool getUsingParking();

public:
	void setRoomNumber(int _iRoomNum);

	void setRegisteredHotel(std::string _strRegHotel);
	void setParkingSpot(std::string _strParkSpot);
	void setLocation(std::string _strLocation);
	void setBookingReference(std::string _strReference);

	void setMemberRank(eMEMBERSHIP eRank);

	void setIsBooked(bool _bIsBook);
	void setUsingParking(bool _bUsePark);

public: // haroan
	void input_data(CUserInterface* _pInterface);
	void write_account(CUserInterface* _pInterface);
	void read_account(std::string username);

private:
	eMEMBERSHIP m_eMembership;

	int m_iRoomNumber;

	bool m_bIsBooked;
	bool m_bUsingParking;

	std::string m_stringBookingReference;
	std::string m_strRegisteredHotel;
	std::string m_strParkingSpot;
	std::string m_stringLocation;

};
#endif
