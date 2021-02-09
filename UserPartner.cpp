////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  This is class for UserPartner, a child class of User, and has functions for login check and 
//  making new account
////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "UserPartner.h"
using namespace std;
CUserPartner::CUserPartner()
	: CUser()
{
	guest = false;
}



void CUserPartner::input_data(CUserInterface* _pInterface)
{
	//As the user trying to register a new account
	//This allows User to input all inforamation for Guest account
	//CUserInterface a;
	string uid = "";
	bool bInputTrue = true;
	cout << "please enter the following details";
	cout << "\nEnter UserID: ";
	cin >> m_tInfo.strUserName;

	//Read the existing Username data from text file
	//This is to determine if this Username has already been created 
	ifstream is(CUserInterface::partnersAccountPath);

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
		_pInterface->Partner();
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

	_pInterface->AddPartner(this);
}
void CUserPartner::write_account(CUserInterface* _pInterface)
{
	ofstream MyFile1, MyFile2;
	input_data(_pInterface);

	//After all information are input into system
	//This will store all information into 2 seperate text file  

	//info file is for all personal information of the user
	MyFile1.open(CUserInterface::partnersInfoPath, ios::out | ios::app);
	MyFile1 << m_tInfo.strUserName << "," << m_tInfo.strName << "," << m_tInfo.iAge << "," << m_tInfo.strAddress << "," << m_tInfo.strPhoneNum << "," << m_tInfo.date << "\n";
	MyFile1.close();

	//account file is for UserID and password
	MyFile2.open(CUserInterface::partnersAccountPath, ios::out | ios::app);
	MyFile2 << m_tInfo.strUserName << "," << m_tInfo.strPassword << "\n";
	MyFile2.close();
	cout << "\nAccount created successfully!\n";
	cout << "\nPress any key to back to previous menu.";
	cin.get();
	cin.get();
}

void CUserPartner::read_account(string username)
{
	// Read all guests data from a text file
	ifstream is(CUserInterface::partnersInfoPath);

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