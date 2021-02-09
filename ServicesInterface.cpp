////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  services Interface to manage all the interfaces related to services
////////////////////////////////////////////////////////////////////
#include "ServicesInterface.h"
using namespace std;
bool CServicesInterface::integerCheck(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}

/**
* service interface for customer and partner
*/
bool CServicesInterface::services_display()
{
	cout << "Are you a customer or a partner" << endl;
	while (true)
	{
		cout << "Enter 1 for partner" << endl;
		cout << "Enter 2 for customer" << endl;
		cout << "Enter 3 to quit" << endl;
		cin >> sUserIdentity;
		if (integerCheck(sUserIdentity) && stoi(sUserIdentity) == 1)
		{
			cout << "What Services do you want to access, Room Services or Extra Services?" << endl;
			while (true)
			{
				cout << "Enter 1 for Room Services" << endl;
				cout << "Enter 2 for Extra Services" << endl;
				cout << "Enter 3 to quit" << endl;
				cin >> sUserInput;
				if (integerCheck(sUserInput) && sUserInput.length() < 10 && stoi(sUserInput) == 1)
				{
					CRoomServicesInterfaceP *rSIP = new CRoomServicesInterfaceP();
					rSIP->partner_display();
					break;
				}
				else if (integerCheck(sUserInput) && sUserInput.length() < 10 && stoi(sUserInput) == 2)
				{
					CExtraServicesInterfaceP *eSIP = new CExtraServicesInterfaceP();
					eSIP->partnerDisplay();
					break;
				}
				else if (integerCheck(sUserInput) && sUserInput.length() < 10 && stoi(sUserInput) == 3)
				{
					return true;
				}
				else
				{
					continue;
				}
			}
		}
		//if customer
		else if (integerCheck(sUserIdentity) && sUserIdentity.length() < 10 && stoi(sUserIdentity) == 2)
		{
			cout << "What Services do you want to access, Room Services or Extra Services?" << endl;
			while (true)
			{

				cout << "Enter 1 for Room Services" << endl;
				cout << "Enter 2 for Extra Services" << endl;
				cout << "Enter 3 to quit" << endl;
				cin >> sUserInput;
				if (integerCheck(sUserInput) && sUserInput.length() < 10 && stoi(sUserInput) == 1)
				{

					CRoomServicesInterfaceC *rSIC = new CRoomServicesInterfaceC();
					rSIC->servicesChoose();
					break;

					//the user booked multiple rooms
				}
				else if (integerCheck(sUserInput) && sUserInput.length() < 10 && stoi(sUserInput) == 2)
				{
					CExtraServicesInterfaceC *eSIC = new CExtraServicesInterfaceC();
					eSIC->customerDisplay();
					break;
				}
				else if (integerCheck(sUserInput) && sUserInput.length() < 10 && stoi(sUserInput) == 3)
				{
					return true;
				}
				else
				{
					continue;
				}
			}
		}
		else if (integerCheck(sUserIdentity) && sUserIdentity.length() < 10 && stoi(sUserIdentity) == 3)
		{
			return true;
		}
		else
		{
			continue;
		}
	}
	return false;
}

CServicesInterface::CServicesInterface()
{

}

CServicesInterface::~CServicesInterface()
{
	vecMultipleRooms.clear();
}