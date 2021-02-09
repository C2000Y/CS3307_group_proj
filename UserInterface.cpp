////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  User's Login Interface, system will determine the identity of user and login their account
////////////////////////////////////////////////////////////////////

#include "UserInterface.h"
#include "UserGuest.h"
#include "UserPartner.h"

using namespace std;

// This is for closing
void CUserInterface::Close()
{
	cout << "\n\n\n\nThis Program is Closed... Thank You\n";
	cin.get();
}

void CUserInterface::Delay(int j)
{
	for (int i = 0; i < j; i++);
}

void CUserInterface::AddGuest(CUserGuest* guest)
{
	if (guest)
		guests.push_back(guest);
}

void CUserInterface::AddPartner(CUserPartner* partner)
{
	if (partner)
		partners.push_back(partner);
}

// This function greets the user at the first menu stage and gets its choice
void CUserInterface::FirstMenuScreen()
{
	system("clear");
	cout << "***********************************************************************\n\n";
	cout << "                     Welcome to Hotel Management  System               \n\n";
	cout << "                       Are you a guest or a partner?                 \n\n";
	cout << "****************************   MENU  ********************************\n\n";
	cout << "1.I'm a guest\n";
	cout << "2.I'm a partner\n";
	cout << "3.Exit\n";
	cout << "\nEnter your choice : ";
	cin >> strchoice;
}

void CUserInterface::PartnerScreen()
{
	system("clear");
	cout << "***********************************************************************\n\n";
	cout << "                     Welcome to Partner Page                 \n\n";
	cout << "****************************   MENU  ********************************\n\n";
	cout << "1.New Partner\n";
	cout << "2.Existing Partner\n";
	cout << "3.Main Menu\n";
	cout << "\nEnter your choice : ";
	cin >> strchoice;
}

void  CUserInterface::GuestScreen()
{
	system("clear");
	cout << "***********************************************************************\n\n";
	cout << "                     Welcome to Guest Page                 \n\n";
	cout << "****************************   MENU  ********************************\n\n";
	cout << "1.New Guest\n";
	cout << "2.Existing Guest\n";
	cout << "\nEnter your choice : ";
	cin >> strchoice;
}

CUserInterface::~CUserInterface()
{
	// delete all created guests and partners pointers, so there is no memory leak
	for (auto it = guests.begin(); it != guests.end(); ++it)
		delete *it;

	for (auto it = partners.begin(); it != partners.end(); ++it)
		delete *it;
}

// When User chooses to use this program as guest
// This menu is for him to choose if he is login with a existing account or to register a new one
bool CUserInterface::Guest()
{
	while (true)
	{
		GuestScreen();

		//String should be one-length digit
		if (strchoice.length() != 1)
		{
			continue;
		}

		//If the user answers he is a new guest, he will start the registration
		if (stoi(strchoice) == 1)
		{
			CUser* pGuest = guestCreator.FactoryMethod();
			pGuest->write_account(this);
		}

		//If the user answers he has a guest account, the system will ask him to input his UserID and password
		else if (stoi(strchoice) == 2)
		{
			string pass, name, Username, Password;
			int i = 0;

			cout << "Enter the Login Customer Id:\n";
			cin >> name;
			bool b_bpass = false;

			cout << "Enter the password to login:\n";
			cin >> pass;
			cout << endl;

			//After the User input his userID and password
			//This will read data from account txt file to match the account data

			ifstream is(guestsAccountPath);
			while (getline(is, Username, ',') && getline(is, Password, '\n'))
			{
				if (Username == name)
				{
					if (Password == pass)
					{
						for (int i = 0; i <= 6; i++)
						{
							Delay(100000000);
							printf(".");
						}
						system("clear");
						cout << "\n\nAccess Granted!\nLOADING";
						b_bpass = true;
						is.close();
						Delay(500000000);
						break;
					}
				}
			}

			if (!b_bpass)
			{
				cout << "\n\nWrong password or Customer Id!!\n";
				cin.get();
				cin.get();
			}
			else
			{
				// read data about the logged in user from a file and store it in a variable
				loggedInUser = guestCreator.FactoryMethod();
				loggedInUser->read_account(Username);
				return false;
			}
		}
	}

	return false;
}

//When User chooses to use this program as partner
//This menu is for him to choose if he is login with a existing account or to register a new one
bool CUserInterface::Partner()
{
	while (true)
	{
		PartnerScreen();

		//String should be one-length digit
		if (strchoice.length() != 1)
		{
			continue;
		}

		//If the user answers he is a new partner, he will start the registration
		else if (stoi(strchoice) == 1)
		{
			CUser* pPartner = partnerCreator.FactoryMethod();
			pPartner->write_account(this);
		}

		else if (stoi(strchoice) == 3)
		{
			return true;
		}

		//If the user answers he has a guest account, the system will ask him to input his UserID and password
		else if (stoi(strchoice) == 2)
		{
			string pass = "";
			string name = "";
			string Username = "";
			string Password = "";

			cout << "For Security Purpose:\n";

			bool b_bpass = false;

			cout << "Enter the Login Customer Id:\n";
			cin >> name;

			cout << "Enter the password to login:\n";
			cin >> pass;

			//After the User input his userID and password
			//This will read data from account txt file to match the account data

			ifstream is(partnersAccountPath);
			while (getline(is, Username, ',') && getline(is, Password, '\n'))
			{
				if (Username == name)
				{
					if (Password == pass)
					{
						for (int i = 0; i <= 6; i++)
						{
							Delay(100000000);
							printf(".");
						}

						system("clear");
						b_bpass = true;
						printf("\n\nAccess Granted!\nLOADING");
						is.close();
						Delay(500000000);
						break;
					}
				}
			}

			if (!b_bpass)
			{
				cout << "\n\nWrong password for Customer Id!!\n";
				cin.get();
				cin.get();
			}
			else
			{
				// read data about the logged in user from a file and store it in a variable
				loggedInUser = partnerCreator.FactoryMethod();
				loggedInUser->read_account(Username);
				return false;


			}
		}
	}

	return false;
}

// This is the first menu that User will see
// This menu asks the identity of the user, if he is a guest or a partner
int CUserInterface::FirstMenu()
{
	bool canContinue = true;
	bool isValid = false;
	while (canContinue || !isValid)
	{
		canContinue = false;

		FirstMenuScreen();

		// right choice should be digit from 1 to 3
		if (strchoice.length() == 1 && isdigit(strchoice.front()))
		{
			isValid = true;
		}

		if (isValid)
		{
			switch (stoi(strchoice))
			{
			case 0:
				canContinue = DisplayUser();
				break;
			case 1:
				canContinue = Guest();
				if (canContinue == false)
				{
					// over here to tell if its guest
					return 0; // guest
				}
				break;
			case 2:
				canContinue = Partner();
				if (canContinue == false)
				{
					// over here to tell if partner
					return 1; // partner
				}
				break;
			case 3:
				system("clear");
				Close();
				return -1;
			default:
				isValid = false;
				break;
			}
		}
		if (!isValid)
		{
			system("clear");
			cout << "\nWrong Choice Intered\n";
			cout << "\nPress any key to back to previous menu.\n";
			cin.get();
			cin.get();
		}
	}
}

// display current logged in user info
bool CUserInterface::DisplayUser()
{
	// if user is logged in
	if (loggedInUser)
	{
		system("clear");

		// determine if it is a guest or a partner
		if (loggedInUser->isGuest())
		{
			cout << "Logged in as a Guest" << endl;
		}
		else
		{
			cout << "Logged in as a Partner" << endl;
		}

		// display user data
		cout << "Username: " << loggedInUser->get_UserName() << endl;
		cout << "Name: " << loggedInUser->get_Name() << endl;
		cout << "Age: " << loggedInUser->get_Age() << endl;
		cout << "Address: " << loggedInUser->get_Address() << endl;
		cout << "Phone number: " << loggedInUser->get_PhoneNum() << endl;
		cout << "Date: " << loggedInUser->get_Date() << endl;

		while (true)
		{
			// Transfer to next interface



		}
	}

	return true;
}


