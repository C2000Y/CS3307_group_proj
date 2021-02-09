////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#include "PaymentInterfaceP.h"
using namespace std;
bool CPaymentInterfaceP::integerCheck(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}
/**
* inteface for partner payment manage
*/
void CPaymentInterfaceP::paymentPartnerDisplay()
{

	CPaymentManager *newPMgrP = new CPaymentManager(iHotelID);
	while (true)
	{
		cout << "---------------------------------------------------------------" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "------   1. Check payment info of rooms                  ------" << endl;
		cout << "------   2. Confirm payment of rooms                     ------" << endl;
		cout << "------   3. update payment info                          ------" << endl;
		cout << "------   4. exit current Interface                       ------" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cin >> sPartnerSelection;
		if (integerCheck(sPartnerSelection) && sPartnerSelection.length() < int(2))
		{
			int iSelection = stoi(sPartnerSelection);
			if (iSelection == 1)
			{
				while (true)
				{
					cout << "------ Please enter the room number:" << endl;
					cin >> sRoomNumber;

					if (integerCheck(sRoomNumber) && sRoomNumber.length() < int(10))
					{
						if (newPMgrP->checkRoomExistance(stoi(sRoomNumber)))
						{
							newPMgrP->displayPaymentInfo(stoi(sRoomNumber));
							break;
						}
						else
						{
							cout << "------ !!!Room does not exist!!! ------" << endl;
							continue;
						}
					}
					else
					{
						cout << "------ !!!Invalid Input!!! ------" << endl;
						continue;
					}
				}
			}
			else if (iSelection == 2)
			{
				while (true)
				{
					cout << "------ Please enter the room number you want to confirm:" << endl;
					cin >> sRoomNumber;

					if (integerCheck(sRoomNumber) && sRoomNumber.length() < int(10))
					{
						if (newPMgrP->checkRoomExistance(stoi(sRoomNumber)))
						{
							newPMgrP->displayAllPendingPayment(iHotelID, sRoomNumber); //display file of credit,debit,gift card
																					   //***update credit card details...
							break;
						}
						else
						{
							cout << "------ !!!Room does not exist!!! ------" << endl;
							continue;
						}
					}
					else
					{
						cout << "------ !!!Invalid Input!!! ------" << endl;
						continue;
					}
				}
			}
			else if (iSelection == 3)
			{
				while (true)
				{
					cout << "------ Which room do you want to update:" << endl;
					cin >> sRoomNumber;
					if (integerCheck(sRoomNumber) && sRoomNumber.length() < int(10))
					{
						if (newPMgrP->checkRoomExistance(stoi(sRoomNumber)))
						{
							while (true)
							{
								cout << "------ What payment do you want to update?  " << endl;
								cout << "------ 1. Room payment                      " << endl;
								cout << "------ 2. Room services payment             " << endl;
								cout << "------ 3. Extra services payment            " << endl;
								cout << "------ 4. All of the above                  " << endl;
								cout << "------ 5. update another room               " << endl;
								cin >> sPaymentTypeInput;
								if (integerCheck(sPaymentTypeInput) && sPaymentTypeInput.length() < int(2))
								{
									int iType = stoi(sPaymentTypeInput);
									if (iType == 1)
									{
										while (true)
										{
											cout << "------ Update or change the status:" << endl;
											cout << "------ 1. Payment is successful    " << endl;
											cout << "------ 2. Payment is denied        " << endl;
											cout << "------ 3. update another payment   " << endl;
											cout << "------ 4. exit" << endl;
											cin >> sStatusInput;
											if (integerCheck(sStatusInput) && sStatusInput.length() < int(2))
											{
												int iStatus = stoi(sStatusInput);
												if (iStatus == 1)
												{
													newPMgrP->updatePaymentStatus(iHotelID, sRoomNumber, 1, 0);
													cout << "test" << endl;
													break;
												}
												else if (iStatus == 2)
												{
													newPMgrP->updatePaymentStatus(iHotelID, sRoomNumber, 1, 2);
													break;
												}
												else if (iStatus == 3)
												{
													break;
												}
												else if (iStatus == 4)
												{
													return;
												}
												else
												{
													cout << "------ !!!Invalid Input!!! ------" << endl;
													continue;
												}
											}
										}
									}
									else if (iType == 2)
									{
										while (true)
										{
											cout << "------ Update or change the status:" << endl;
											cout << "------ 1. Payment is successful    " << endl;
											cout << "------ 2. Payment is denied        " << endl;
											cout << "------ 3. update another payment   " << endl;
											cout << "------ 4. exit" << endl;
											cin >> sStatusInput;
											if (integerCheck(sStatusInput) && sStatusInput.length() < int(2))
											{
												int iStatus = stoi(sStatusInput);
												if (iStatus == 1)
												{
													newPMgrP->updatePaymentStatus(iHotelID, sRoomNumber, 2, 0);
													break;
												}
												else if (iStatus == 2)
												{
													newPMgrP->updatePaymentStatus(iHotelID, sRoomNumber, 2, 2);
													break;
												}
												else if (iStatus == 3)
												{
													break;
												}
												else if (iStatus == 4)
												{
													break;
												}

												else
												{
													cout << "------ !!!Invalid Input!!! ------" << endl;
													continue;
												}
											}
										}
									}
									else if (iType == 3)
									{
										while (true)
										{
											cout << "------ Update or change the status:" << endl;
											cout << "------ 1. Payment is successful    " << endl;
											cout << "------ 2. Payment is denied        " << endl;
											cout << "------ 3. update another payment   " << endl;
											cout << "------ 4. exit " << endl;
											cin >> sStatusInput;
											if (integerCheck(sStatusInput) && sStatusInput.length() < int(2))
											{
												int iStatus = stoi(sStatusInput);
												if (iStatus == 1)
												{
													newPMgrP->updatePaymentStatus(iHotelID, sRoomNumber, 3, 0);
													break;
												}
												else if (iStatus == 2)
												{
													newPMgrP->updatePaymentStatus(iHotelID, sRoomNumber, 3, 2);
													break;
												}
												else if (iStatus == 3)
												{
													break;
												}
												else if (iStatus == 4)
												{
													return;
												}
												else
												{
													cout << "------ !!!Invalid Input!!! ------" << endl;
													continue;
												}
											}
										}
									}
									else if (iType == 4)
									{
										while (true)
										{
											cout << "------ Update or change the status:" << endl;
											cout << "------ 1. Payment is successful    " << endl;
											cout << "------ 2. Payment is denied        " << endl;
											cout << "------ 3. update another payment   " << endl;
											cout << "------ 4. exit" << endl;
											cin >> sStatusInput;
											if (integerCheck(sStatusInput) && sStatusInput.length() < int(2))
											{
												int iStatus = stoi(sStatusInput);
												if (iStatus == 1)
												{
													newPMgrP->updatePaymentStatus(iHotelID, sRoomNumber, 4, 0);
													break;
												}
												else if (iStatus == 2)
												{
													newPMgrP->updatePaymentStatus(iHotelID, sRoomNumber, 4, 2);
													break;
												}
												else if (iStatus == 3)
												{
													break;
												}
												else if (iStatus == 4)
												{
													return;
												}
												else
												{
													cout << "------ !!!Invalid Input!!! ------" << endl;
													continue;
												}
											}
										}
									}
									else if (iType == 5)
									{
										break;
									}
									else
									{
										cout << "------ !!!Invalid Input!!! ------" << endl;
										continue;
									}
								}
								else
								{
									cout << "------ !!!Invalid Input!!! ------" << endl;
									continue;
								}
							}
						}
						else
						{
							cout << "------ !!!Room does not exist!!! ------" << endl;
							continue;
						}
					}
					else
					{
						cout << "------ !!!Invalid Input!!! ------" << endl;
						continue;
					}
				}
			}
			else if (iSelection == 4)
			{
				break;
			}
			else
			{
				cout << "------ !!!Invalid Input!!! ------" << endl;
				continue;
			}
		}
		else
		{
			cout << "------ !!!Invalid Input!!! ------" << endl;
			continue;
		}
	}
}

CPaymentInterfaceP::CPaymentInterfaceP()
{
}

CPaymentInterfaceP::~CPaymentInterfaceP()
{
}