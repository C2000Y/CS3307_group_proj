////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  This is class for UserGuest, a child class of User, and has functions for login check and 
//  making new account
////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "UserGuest.h"

using namespace std;

CUserGuest::CUserGuest()
	: m_eMembership(eMEMBERSHIP::MEMBERSHIP_ERROR)
	, m_iRoomNumber(0)
	, m_bIsBooked(false)
	, m_bUsingParking(false)
	, m_stringBookingReference("")
	, m_strRegisteredHotel("")
	, m_strParkingSpot("")
	, m_stringLocation("")
{
	guest = true;
}

CUserGuest::~CUserGuest()
{
}

int CUserGuest::getRoomNumber()
{
	return m_iRoomNumber;
}

string CUserGuest::getRegisteredHotel()
{
	return m_strRegisteredHotel;
}

string CUserGuest::getParkingSpot()
{
	return m_strParkingSpot;
}

string CUserGuest::getLocation()
{
	return m_stringLocation;
}

string CUserGuest::getBookingReference()
{
	return m_stringBookingReference;
}

eMEMBERSHIP CUserGuest::getMemberRank()
{
	return m_eMembership;
}

bool CUserGuest::getIsBooked()
{
	return m_bIsBooked;
}

bool CUserGuest::getUsingParking()
{
	return m_bUsingParking;
}

void CUserGuest::setRoomNumber(int _iRoomNum)
{
	m_iRoomNumber = _iRoomNum;
}

void CUserGuest::setRegisteredHotel(std::string _strRegHotel)
{
	m_strRegisteredHotel = _strRegHotel;
}

void CUserGuest::setParkingSpot(std::string _strParkSpot)
{
	m_strParkingSpot = _strParkSpot;
}

void CUserGuest::setLocation(std::string _strLocation)
{
	m_stringLocation = _strLocation;
}

void CUserGuest::setBookingReference(std::string _strReference)
{
	m_stringBookingReference = _strReference;
}

void CUserGuest::setMemberRank(eMEMBERSHIP eRank)
{
	m_eMembership = eRank;
}

void CUserGuest::setIsBooked(bool _bIsBook)
{
	m_bIsBooked = _bIsBook;
}

void CUserGuest::setUsingParking(bool _bUsePark)
{
	m_bUsingParking = _bUsePark;
}

void CUserGuest::input_data(CUserInterface* _pInterface)
{
	//As the user is trying to register a new account
	//This allows User to input all inforamation for Guest account
	//CUserInterface a;
	string uid = "";

	//Retry:
	bool bContinue = true;

	cout << "please enter the following details";
	cout << "\nEnter UserID: ";
	cin >> m_tInfo.strUserName;

	//Read the existing UserID data from text file
	//This is to determine if this UserID has already been created 
	ifstream is(CUserInterface::guestsAccountPath);

	bool exists = false;

	while (getline(is, uid, ',') && getline(is, m_tInfo.strPassword, '\n'))
	{
		if (uid == m_tInfo.strUserName)
		{
			cout << "\nUserID Matches with Existing Account!";
			cout << "\nPress any key to back to previous menu.";
			cin.get();
			cin.get();
			exists = true;
			break;
		}
	}
	is.close();

	if (exists)
	{
		_pInterface->Guest();
		return;
	}

	//If the UserID that user input doesn't match with existing account
	//Registration will continue and this will ask user to input more information for the account

	fflush(stdin);
	cout << "\nEnter Name: ";
	cin >> m_tInfo.strName;
	fflush(stdin);
	cout << "\nEnter the age:";
	cin >> m_tInfo.iAge;

	fflush(stdin);
	cout << "\nEnter the address:";
	cin >> m_tInfo.strAddress;
	fflush(stdin);
	cout << "\nEnter the phone number: ";
	cin >> m_tInfo.strPhoneNum;
	fflush(stdin);
	cout << "\nEnter Password For Your Account:";
	cin >> m_tInfo.strPassword;
	fflush(stdin);
	time_t now = time(0);
	string dt = ctime(&now);
	m_tInfo.date = dt;
	cout << "\nDate and Time of Account Creation:" << m_tInfo.date << endl;

	_pInterface->AddGuest(this);
}

void CUserGuest::write_account(CUserInterface* _pInterface)
{
	//After all information is input into system
	//This will store all information into 2 seperate text file
	ofstream MyFile1, MyFile2;
	input_data(_pInterface);

	//info file is for all personal information of the user
	MyFile1.open(CUserInterface::guestsInfoPath, ios::out | ios::app);
	MyFile1 << m_tInfo.strUserName << "," << m_tInfo.strName << "," << m_tInfo.iAge << "," << m_tInfo.strAddress << "," << m_tInfo.strPhoneNum << "," << m_tInfo.date << "\n";
	MyFile1.close();

	//account file is for UserID and password
	MyFile2.open(CUserInterface::guestsAccountPath, ios::out | ios::app);
	MyFile2 << m_tInfo.strUserName << "," << m_tInfo.strPassword << "\n";
	MyFile2.close();
	cout << "\nAccount created successfully!\n";
	cout << "\nPress any key to back to previous menu.";
	cin.get();
	cin.get();
}

void CUserGuest::read_account(string username)
{
	// Read all guests data from a text file
	ifstream is(CUserInterface::guestsInfoPath);

	string line;
	while (getline(is, line))
	{
		istringstream line_stream{ line };
		string curUserName;
		string age;

		// read current user name
		getline(line_stream, curUserName, ',');
		// if the neeeded username found
		if (curUserName == username)
		{
			// read the guest's values split by comma and store
			getline(line_stream, m_tInfo.strName, ',');
			getline(line_stream, age, ',');
			getline(line_stream, m_tInfo.strAddress, ',');
			getline(line_stream, m_tInfo.strPhoneNum, ',');
			getline(line_stream, m_tInfo.date, ',');

			// store username read
			m_tInfo.strUserName = curUserName;
			// convert age to int and store
			m_tInfo.iAge = stoi(age);
		}

	}
}

