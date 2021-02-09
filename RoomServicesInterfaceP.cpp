////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  partner's room services interface
////////////////////////////////////////////////////////////////////
#include "RoomServicesInterfaceP.h"
#include "RoomServices.h"
#include "RoomServicesManager.h"
#include <sstream>
using namespace std;
bool CRoomServicesInterfaceP::integerCheck(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}
/**
* display the room services for the partner
*/
void CRoomServicesInterfaceP::partner_display()

{

	CRoomServicesManager *newRSMg = new CRoomServicesManager();
	cout << "--- New Services Added:" << endl;
	newRSMg->displayNotification(iHotelID);
	newRSMg->removeNotification();
	while (true)
	{
		cout << "--------------------------------------------------------------------" << endl;
		cout << "--------------------------------------------------------------------" << endl;
		cout << "-------------                                          -------------" << endl;
		cout << "----------       Enter 1 to modify available Services     ----------" << endl;
		cout << "----------       Enter 2 to check all the Services        ----------" << endl;
		cout << "----------       Enter 3 to update Services               ----------" << endl;
		cout << "----------       Enter 4 to quit                          ----------" << endl;
		cout << "-------------                                          -------------" << endl;
		cout << "--------------------------------------------------------------------" << endl;
		cout << "--------------------------------------------------------------------" << endl;

		cin >> sUserInput;

		if (integerCheck(sUserInput) && sUserInput.length() < 10)
		{
			int iUserInput = stoi(sUserInput);
			if (iUserInput == 1)
			{
				while (true)
				{
					cout << "--------------------------------------------------------------------" << endl;
					cout << "--------------------------------------------------------------------" << endl;
					cout << "------  Which service availability do you want to change?" << endl;
					cout << "------  Enter 1 for laundry" << endl;
					cout << "------  Enter 2 for dry clean" << endl;
					cout << "------  Enter 3 for tea" << endl;
					cout << "------  Enter 4 for coffee" << endl;
					cout << "------  Enter 5 for bedsheets change" << endl;
					cout << "------  Enter 6 for wake up service" << endl;
					cout << "------  Enter 7 for Do Not Disturb" << endl;
					cout << "------  Enter 8 to quit" << endl;
					cout << "------  Enter 9 to next" << endl;
					cout << "--------------------------------------------------------------------" << endl;
					cout << "--------------------------------------------------------------------" << endl;
					cin >> sServiceInput;

					if (integerCheck(sServiceInput) && sServiceInput.length() < 10)
					{
						int iServiceInput = stoi(sServiceInput);
						if (iServiceInput == 1 || iServiceInput == 2 || iServiceInput == 3 || iServiceInput == 4 || iServiceInput == 5 || iServiceInput == 6 || iServiceInput == 7 || iServiceInput == 9)
						{
							newRSMg->modifyRoomServicesAv(iHotelID, iServiceInput);

							cout << "Room services avaiability updated." << endl;
							while (true)
							{
								cout << "--------------------------------------------------------------------" << endl;
								cout << "--------------------------------------------------------------------" << endl;
								cout << "------  Which service price do you want to change?" << endl;
								cout << "------  Enter 1 for laundry" << endl;
								cout << "------  Enter 2 for dry clean" << endl;
								cout << "------  Enter 3 for tea" << endl;
								cout << "------  Enter 4 for coffee" << endl;
								cout << "------  Enter 5 for bedsheets change" << endl;
								cout << "------  Enter 6 to quit" << endl;
								cout << "--------------------------------------------------------------------" << endl;
								cout << "--------------------------------------------------------------------" << endl;
								cin >> sPriceSelect;
								if (integerCheck(sPriceSelect))
								{
									int iPriceSelect = stoi(sPriceSelect);
									if (iPriceSelect == 1 || iPriceSelect == 2 || iPriceSelect == 3 || iPriceSelect == 4 || iPriceSelect == 5)
									{
										while (true)
										{
											cout << "----  Enter the new Price:" << endl;
											cin >> sPriceInput;
											if (integerCheck(sPriceInput))
											{
												int iPriceInput = stoi(sPriceInput);
												if (iPriceInput > 0)
												{
													newRSMg->modifyRoomServicesPrice(iHotelID, iPriceSelect, iPriceInput);
													cout << "Price updated." << endl;
													break;
												}
											}
											else
											{
												continue;
											}
										}
									}

									else if (iPriceSelect == 6)
									{
										break;
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
							//update room services availability file
							//newRSMg->updateRSAvFile(iHotelID);
						}
						else if (iServiceInput == 8)
						{
							break;
						}
					}
					else
					{
						continue;
					}
				}
			}
			else if (iUserInput == 2)
			{
				while (true)
				{
					cout << "---- Please enter the room number:" << endl;
					cin >> sRoomInput;
					if (integerCheck(sRoomInput) && sRoomInput.length() < int(10))
					{
						if (newRSMg->checkRoomExistance(to_string(iHotelID), sRoomInput))
						{
							int iRoomInput = stoi(sRoomInput);
							newRSMg->checkRoomServices(iHotelID, iRoomInput);
							break;
						}
					}
					else
					{
						continue;
					}
				}
			}
			else if (iUserInput == 3)
			{
				while (true)
				{
					cout << "---- Please enter the room number:" << endl;
					cout << "---- Enter 1 to quit" << endl;
					cin >> sRoomInput;

					if (integerCheck(sRoomInput) && sRoomInput.length() < 10 && stoi(sRoomInput) != 1)
					{
						if (newRSMg->checkRoomExistance(to_string(iHotelID), sRoomInput))
						{
							int iRoomInput = stoi(sRoomInput);
							while (true)
							{
								cout << "------  Please update the servies provided:" << endl;
								cout << "------  Enter 1 for laundry" << endl;
								cout << "------  Enter 2 for dry clean" << endl;
								cout << "------  Enter 3 for tea" << endl;
								cout << "------  Enter 4 for coffee" << endl;
								cout << "------  Enter 5 for bedsheets change" << endl;
								cout << "------  Enter 6 for wake up service" << endl;
								cout << "------  Enter 8 for text message" << endl;
								cout << "------  Enter 9 to quit" << endl;
								cin >> sServiceInputChange;

								if (integerCheck(sServiceInputChange) && sServiceInputChange.length() < 10 && (stoi(sServiceInputChange) == 1 || stoi(sServiceInputChange) == 2 || stoi(sServiceInputChange) == 3 || stoi(sServiceInputChange) == 4 || stoi(sServiceInputChange) == 5 || stoi(sServiceInputChange) == 6 || stoi(sServiceInputChange) == 8))
								{
									int iServiceInputChange = stoi(sServiceInputChange);
									while (true)
									{
										cout << "Enter the number of services provided (enter 0 if number is not applicable)" << endl;
										cin >> sServiceNum;
										if (integerCheck(sServiceNum) && sServiceNum.length() < 10)
										{

											int iServiceNum = stoi(sServiceNum);
											newRSMg->modifyRoomServicesP(iHotelID, stoi(sRoomInput), stoi(sServiceInputChange), iServiceNum, "None");

											break;
										}
										else
										{
											continue;
										}
									}
								}
								else if (integerCheck(sServiceInputChange) && stoi(sServiceInputChange) == 9)
								{
									break;
								}

								else
								{
									continue;
								}
							}
						}
						else
						{
							cout << "Room not exist" << endl;
						}
					}
					else if (integerCheck(sRoomInput) && sRoomInput.length() < 10 && stoi(sRoomInput) == 1)
					{
						break;
					}
					else
					{
						continue;
					}
				}
			}

			else if (iUserInput == 4)
			{
				break;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}
}

CRoomServicesInterfaceP::CRoomServicesInterfaceP()
{
}

CRoomServicesInterfaceP::~CRoomServicesInterfaceP()
{
	vecHotels.clear();
	vSelectedServices.clear();
	vServicesList.clear();
}