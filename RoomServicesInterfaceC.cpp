////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  customer's room services Interface
////////////////////////////////////////////////////////////////////
#include "RoomServicesInterfaceC.h"
using namespace std;
bool CRoomServicesInterfaceC::integerCheck(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}

CRoomServicesInterfaceC::CRoomServicesInterfaceC()
{

}

CRoomServicesInterfaceC::~CRoomServicesInterfaceC()
{
	vecMultipleRooms.clear();
	vSelectedServices.clear();
	vAvServicesList.clear();
	vHotelServices.clear();
	vHotelServicesPrices.clear();
	vAvServices.clear();
	vAvServicesPrices.clear();
	vServicesList.clear();
}
/**
* roomservice interface designed for customer
*/
void CRoomServicesInterfaceC::servicesChoose()
{

	//get from account info
	//set a default value for testing right now, will get from the account in stage 4
	while (true)
	{
		//get the info from  rSAv file and change to a string
		string line;
		ifstream file;
		file.open("RoomServicesAv.csv");
		vector<string> result;

		while (getline(file, line))
		{
			stringstream s_stream(line);
			while (s_stream.good())
			{
				string substr;
				getline(s_stream, substr, ',');

				result.push_back(substr);
			}

			if (result[0] == to_string(iHotelID))
			{
				for (int i = 1; i < result.size(); i = i + 2)
				{
					vHotelServices.push_back(result[i]);

					vHotelServicesPrices.push_back(result[i + 1]);
				}
				break;
			}
			else
			{
				result.clear();
			}
		}

		for (int i = 0; i < vHotelServices.size(); i++)

		{
			if (stoi(vHotelServices[i]) == 1)
			{
				vAvServices.push_back(vServicesList[i]);
				vAvServicesPrices.push_back(vHotelServicesPrices[i]);
			}
		}

		CRoomServicesManager *newRSM = new CRoomServicesManager();

		CRoomServicesManager *notification = new CRoomServicesManager();

		while (true)
		{
			cout << "--------------------------------------------------------------------" << endl;
			cout << "--------------------------------------------------------------------" << endl;
			cout << "--------------------                            --------------------" << endl;
			cout << "---------------                                      ---------------" << endl;
			cout << "--------    Please select or modify the service you want    --------" << endl;
			for (int i = 0; i < vAvServices.size(); i++)
			{
				cout << "--------    Enter " << i + 1 << " for " << vAvServices[i] << " Services" << endl;
			}
			cout << "--------                                                    --------" << endl;
			cout << "--------            Enter 9 if ready to check out           --------" << endl;
			cout << "--------            Enter 10 to exit                        --------" << endl;
			cout << "---------------                                      ---------------" << endl;
			cout << "--------------------------------------------------------------------" << endl;
			cout << "--------------------------------------------------------------------" << endl;
			cin >> sUserInput;
			if (integerCheck(sUserInput) && sUserInput.length() < int(10) && stoi(sUserInput) != 9 && stoi(sUserInput) != 10 && int(stoi(sUserInput)) <= vAvServices.size())
			{

				int iUserInput = stoi(sUserInput);
				cout << endl;
				if (vAvServices[iUserInput - 1] == "Laundry" || vAvServices[iUserInput - 1] == "Dry Clean" || vAvServices[iUserInput - 1] == "Tea" || vAvServices[iUserInput - 1] == "Coffee" || vAvServices[iUserInput - 1] == "Bed Sheets")
				{
					while (true)
					{
						cout << "---Enter the amount you want" << endl;
						if (vAvServices[iUserInput - 1] == "Laundry")
						{
							cout << "--- Laundry Price: " << vAvServicesPrices[iUserInput - 1] << " per bucket" << endl;
						}
						else if (vAvServices[iUserInput - 1] == "Dry Clean")
						{
							cout << "--- Dry Clean Price: " << vAvServicesPrices[iUserInput - 1] << " per clothes" << endl;
						}
						else if (vAvServices[iUserInput - 1] == "Tea")
						{
							cout << "--- Tea Price: " << vAvServicesPrices[iUserInput - 1] << " per cup" << endl;
						}
						else if (vAvServices[iUserInput - 1] == "Coffee")
						{
							cout << "--- Coffee Price: " << vAvServicesPrices[iUserInput - 1] << " per cup" << endl;
						}
						else if (vAvServices[iUserInput - 1] == "Bed Sheets")
						{
							cout << "--- Bed Sheets Price: " << vAvServicesPrices[iUserInput - 1] << " per bed sheet" << endl;
						}

						string sAmount;
						cin >> sAmount;
						if (integerCheck(sAmount) && sAmount.length() < 10)
						{

							int amount = stoi(sAmount);
							if (vAvServices[iUserInput - 1] == "Laundry")
							{
								newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 1, amount, "None");
								notification->addRoomServicesC(iHotelID, iRoomNum, 1, amount, "None");
								notification->updateNotificationFile(iHotelID, iRoomNum);
							}
							else if (vAvServices[iUserInput - 1] == "Dry Clean")
							{
								newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 2, amount, "None");
								notification->addRoomServicesC(iHotelID, iRoomNum, 2, amount, "None");
								notification->updateNotificationFile(iHotelID, iRoomNum);
							}
							else if (vAvServices[iUserInput - 1] == "Tea")
							{
								newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 3, amount, "None");
								notification->addRoomServicesC(iHotelID, iRoomNum, 3, amount, "None");
								notification->updateNotificationFile(iHotelID, iRoomNum);
							}
							else if (vAvServices[iUserInput - 1] == "Coffee")
							{
								newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 4, amount, "None");
								notification->addRoomServicesC(iHotelID, iRoomNum, 4, amount, "None");
								notification->updateNotificationFile(iHotelID, iRoomNum);
							}
							else if (vAvServices[iUserInput - 1] == "Bed Sheets")
							{
								newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 5, amount, "None");
								notification->addRoomServicesC(iHotelID, iRoomNum, 5, amount, "None");
								notification->updateNotificationFile(iHotelID, iRoomNum);
							}
							break;
						}
						else
						{
							continue;
						}
					}
				}
				//wake up
				else if (vAvServices[iUserInput - 1] == "Wake Up")
				{
					while (true)
					{
						string sWakeUpinput;
						cout << "---Enter the time you wake up: " << endl;
						cout << "---Enter 6 for 6 a.m., 21 for 9 p.m. etc." << endl;
						cin >> sWakeUpinput;
						if (integerCheck(sWakeUpinput) && stoi(sWakeUpinput) < 24 && stoi(sWakeUpinput) > 0)
						{
							int iWakeUpInput = stoi(sWakeUpinput);
							newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 6, iWakeUpInput, "None");
							notification->addRoomServicesC(iHotelID, iRoomNum, 6, iWakeUpInput, "None");
							notification->updateNotificationFile(iHotelID, iRoomNum);
							break;
						}
						else
						{
							continue;
						}
					}
				}
				else if (vAvServices[iUserInput - 1] == "Room Clean")
				{
					newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 7, 0, "None");
					notification->addRoomServicesC(iHotelID, iRoomNum, 7, 0, "None");
					notification->updateNotificationFile(iHotelID, iRoomNum);
				}
				else if (vAvServices[iUserInput - 1] == "Do Not Disturb")
				{
					newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 8, 0, "None");
					notification->addRoomServicesC(iHotelID, iRoomNum, 8, 0, "None");
					notification->updateNotificationFile(iHotelID, iRoomNum);
				}
				//text msg
				else if (vAvServices[iUserInput - 1] == "Text Msg")
				{
					sMsg;
					cout << "---Please leave the message below: (<500 characters)" << endl;
					cin >> sMsg;

					while (sMsg.length() > 500)
					{
						cout << "---!!!Too many words!!!" << endl;
						cout << "---Please leave the message again: " << endl;
						cin >> sMsg;
					}
					newRSM->modifyRoomServicesC(iHotelID, iRoomNum, 9, 0, sMsg);
					notification->addRoomServicesC(iHotelID, iRoomNum, 9, 0, sMsg);
					notification->updateNotificationFile(iHotelID, iRoomNum);
				}
			}
			else if (integerCheck(sUserInput) && sUserInput.length() < 10 && stoi(sUserInput) == 9)
			{
				while (true)
				{
					cout << "-----------------------------------------------------------------------" << endl;
					cout << "-----------------------------------------------------------------------" << endl;
					cout << "----------     How would you like to pay?                    ----------" << endl;
					cout << "----------     Enter 1 if you want to pay when check out.    ----------" << endl;
					cout << "----------     Enter 2 if you want to pay right now.         ----------" << endl;
					cout << "----------     Enter 3 to exit payment.                      ----------" << endl;
					cout << "-----------------------------------------------------------------------" << endl;
					cout << "-----------------------------------------------------------------------" << endl;
					//prompt the payment
					CPaymentInterfaceC *payC = new CPaymentInterfaceC();
					CPaymentManager *payMgr = new CPaymentManager(iHotelID);
					iCurrentPrice = newRSM->getCurrentPrice(iHotelID, iRoomNum);
					iNewPrice = newRSM->getNewAddedPrice(iHotelID, iRoomNum);
					iTotalPrice = iNewPrice + iCurrentPrice;

					cin >> sPaymentChoice;

					if (integerCheck(sPaymentChoice) && (stoi(sPaymentChoice) == 1 || stoi(sPaymentChoice) == 2 || stoi(sPaymentChoice) == 3))
					{
						int iPaymentChoice = stoi(sPaymentChoice);
						//unpdate paymentInfo file
						payMgr->updateRoomServicePrice(iRoomNum, iTotalPrice);
						payMgr->updatePaymentInfoFile(iHotelID, iRoomNum);
						//update CustomerServicesInfo.csv & notification list
						newRSM->updateCSIFile(iHotelID, iRoomNum, sMsg);
						//change the new required servives file
						notification->addToNotificationFile();
						if (iPaymentChoice == 1)
						{
							cout << "Updated." << endl;
							break;
						}
						else if (iPaymentChoice == 2)
						{
							payC->paymentDisplay();
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						cout << "------ !!!Invalid Input!!! ------" << endl;
						continue;
					}
				}
			}
			else if (integerCheck(sUserInput) && sUserInput.length() < 10 && stoi(sUserInput) == 10)
			{
				notification->deleteIfNoServicesAdded(iHotelID, iRoomNum);
				return;
			}
			else
			{
				cout << "------ !!!Invalid Input!!! ------" << endl;
				continue;
			}
		}
		//LTDCB
	}
}
