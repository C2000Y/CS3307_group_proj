////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  P's extra services interface
////////////////////////////////////////////////////////////////////
#include "ExtraServicesInterfaceP.h"
using namespace std;
// check wether the every char  in string is a digit
bool CExtraServicesInterfaceP::integerCheck(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}
void CExtraServicesInterfaceP::partnerDisplay()
{
	//set a default value for right now
	//link to acount info in stage 4

	CExtraServicesManager *ESManagerP = new (CExtraServicesManager);
	while (true)
	{
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "---------------                                             ---------------" << endl;
		cout << "----------     Enter 1 to modify extra services availability     ----------" << endl;
		cout << "----------     Enter 2 to quit                                   ----------" << endl;
		cout << "---------------                                             ---------------" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cin >> sUserinput;
		if (integerCheck(sUserinput) && sUserinput.length() < 10 && stoi(sUserinput) == 1)
		{
			while (true)
			{
				cout << "--------------------------------------------------------------------" << endl;
				cout << "--------------------------------------------------------------------" << endl;
				cout << "-------------                                          -------------" << endl;
				cout << "----------       What Services do you want to change      ----------" << endl;
				cout << "----------       Enter 1 for Gym                          ----------" << endl;
				cout << "----------       Enter 2 for Dining                       ----------" << endl;
				cout << "----------       Enter 3 for Shopping Arcade              ----------" << endl;
				cout << "----------       Enter 4 to quit                          ----------" << endl;
				cout << "-------------                                          -------------" << endl;
				cout << "--------------------------------------------------------------------" << endl;
				cout << "--------------------------------------------------------------------" << endl;
				cin >> sServiceInput;

				if (integerCheck(sServiceInput) && sServiceInput.length() < 10 && (stoi(sServiceInput) == 1 || stoi(sServiceInput) == 2 || stoi(sServiceInput) == 3))
				{
					cout << stoi(sServiceInput) << endl; //test
					ESManagerP->modifyExtraServicesAv(iHotelID, stoi(sServiceInput));
					cout << "Availability Updated" << endl;
					ESManagerP->displayExtraServicesAv(iHotelID);
					break;
				}
				else if (integerCheck(sServiceInput) && sServiceInput.length() < 10 && stoi(sServiceInput) == 4)
				{

					return;
				}
				else
				{
					continue;
				}
			}
		}
		else if (integerCheck(sUserinput) && sUserinput.length() < 10 && stoi(sUserinput) == 2)
		{
			break;
		}
		else
		{
			continue;
		}
	}
}

CExtraServicesInterfaceP::CExtraServicesInterfaceP()
{

}

CExtraServicesInterfaceP::~CExtraServicesInterfaceP()
{
}