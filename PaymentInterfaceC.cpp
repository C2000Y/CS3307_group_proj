////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  customer's room services Interface
////////////////////////////////////////////////////////////////////
#include "PaymentInterfaceC.h"
using namespace std;
bool CPaymentInterfaceC::integerCheck(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}

void CPaymentInterfaceC::paymentDisplay()
{

	//payment manger obj
	CPaymentManager *newPayMgrC = new CPaymentManager(iHotelID);
	while (true)
	{
		cout << "Step 1:" << endl;
		cout << "------ Enter the Room Number:" << endl;
		cout << "------ Enter q to exit" << endl;
		//newPayMgrC->print_map();//test
		cin >> sRoomNumInput;
		//check input validity of Room #
		if (sRoomNumInput == "q")
		{
			break;
		}
		else if (integerCheck(sRoomNumInput) && sRoomNumInput.length() < int(10))
		{
			//newPayMgrC->print_map();
			if (newPayMgrC->checkRoomExistance(stoi(sRoomNumInput)))
			{
				while (true)
				{
					cout << "Step 2:" << endl;
					cout << "------ Enter 1 to check pending payment info" << endl;
					cout << "------ Enter 2 to go back to room number selection (Step 2)" << endl;
					cin >> sPaymentInfoInput;
					if (integerCheck(sPaymentInfoInput) && sPaymentInfoInput.length() < int(2) && stoi(sPaymentInfoInput) == 1)
					{
						//display current status of payment and other payment info
						newPayMgrC->displayPaymentInfo(stoi(sRoomNumInput));
						while (true)
						{
							cout << "Step 3:" << endl;
							cout << "------ What would you like to pay?" << endl;
							cout << "------ 1. Room" << endl;
							cout << "------ 2. Room Services" << endl;
							cout << "------ 3. Extra Services" << endl;
							cout << "------ 4. All the bills" << endl;
							cout << "------ 5. Go back to Step 2" << endl;
							cout << "------ 6. Exit Payment system" << endl;
							cin >> sPaymentSelectionInput;
							//check input validity of payment selection
							if (integerCheck(sPaymentSelectionInput) && sPaymentSelectionInput.length() < int(10))
							{
								int iSelection = stoi(sPaymentSelectionInput);
								if (iSelection == 1 || iSelection == 2 || iSelection == 3 || iSelection == 4)
								{
									while (true)
									{
										cout << "Step 4:" << endl;
										cout << "------ How would you like to pay?" << endl;
										cout << "------ 1. Credit card" << endl;
										cout << "------ 2. Debit card" << endl;
										cout << "------ 3. Gift card" << endl;
										cout << "------ 4. Go back to payment selection(Step 3)" << endl;
										cout << "------ 5. Exit Payment" << endl;
										cout << "------ You can also pay the bills at the front desk" << endl;
										cin >> sPaymentTypeInput;
										if (integerCheck(sPaymentTypeInput) && sPaymentTypeInput.length() < int(10))
										{
											int iType = stoi(sPaymentTypeInput);
											//credit card
											if (iType == 1)
											{
												while (true)
												{
													cout << "Step 5:" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  Enter or change the credit card information:           " << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  1. CREDIT CARD HOLDER NAME:  " << vecCreditCardInfo[0] << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  2. CREDIT CARD NUMBER:       " << vecCreditCardInfo[1] << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  3. EXPIRATION DATE:          " << vecCreditCardInfo[2] << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  4. SECURITY CODE:            " << vecCreditCardInfo[3] << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  Enter or change info by entering corresponding number  " << endl;
													cout << "------  5. Change payment method                               " << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  !!!Please make sure all the info is correct !!! -------" << endl;
													cout << "------  !!! Late penalty may apply if info is wrong !!! -------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  6. Confirm the payment                                 " << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cin >> sCreditCardInput;
													if (integerCheck(sCreditCardInput) && sCreditCardInput.length() < int(10) && (stoi(sCreditCardInput) == 1 || stoi(sCreditCardInput) == 2 || stoi(sCreditCardInput) == 3 || stoi(sCreditCardInput) == 4))
													{
														int iCardInfo = stoi(sCreditCardInput);
														//cardholder name
														if (iCardInfo == 1)
														{
															cout << "------ Please enter the First Name:" << endl;
															cin >> sCreditCardFirstName;
															cout << "------ Please enter the Last Name:" << endl;
															cin >> sCreditCardLastName;
															sCreditCardName = sCreditCardFirstName + " " + sCreditCardLastName;
															vecCreditCardInfo[0] = sCreditCardName;
															continue;
														}
														//credit card #
														else if (iCardInfo == 2)
														{
															cout << "------ Please enter the credit card #:" << endl;
															cin >> sCreditCardNumber;
															vecCreditCardInfo[1] = sCreditCardNumber;
															continue;
														}
														//expiration date
														else if (iCardInfo == 3)
														{
															cout << "------ Please enter the expiration date in the format Month/Year:" << endl;
															cin >> sCreditCardExpireDate;
															vecCreditCardInfo[2] = sCreditCardExpireDate;
															continue;
														}
														//security code
														else
														{
															cout << "------ Please enter the security code:" << endl;
															cin >> sCreditCardSecurityCode;
															vecCreditCardInfo[3] = sCreditCardSecurityCode;
															continue;
														}
													}
													else if (integerCheck(sCreditCardInput) && sCreditCardInput.length() < int(10) && stoi(sCreditCardInput) == 5)
													{
														//restore the initialization info
														vecCreditCardInfo = { "First name, Last Name", "xxxx xxxx xxxx xxxx", "Month/Year", "xxx" };
														break;
													}
													//confirmation of payment
													else if (integerCheck(sCreditCardInput) && sCreditCardInput.length() < int(10) && stoi(sCreditCardInput) == 6)
													{
														cout << "------ Your payment is Processing..." << endl;
														//refresh the default setting
														//update CreditCardInfo.csv
														newPayMgrC->updateCreditCardPaymentInfo(iHotelID, sRoomNumInput, sPaymentSelectionInput, sCreditCardName, sCreditCardNumber, sCreditCardExpireDate, sCreditCardSecurityCode);
														vecCreditCardInfo = { "First name, Last Name", "xxxx xxxx xxxx xxxx", "Month/Year", "xxx" };
														cout << "------ You can check the payment status by entering 1 in step 3." << endl;

														//update Paymentinfo.csv (1 means pending)
														newPayMgrC->updatePaymentStatus(iHotelID, sRoomNumInput, iSelection, 1);

														break;
													}
													else
													{
														cout << "------ !!!Invalid Input!!! ------" << endl;
														continue;
													}
												}
											}
											//debit card
											else if (iType == 2)
											{
												while (true)
												{
													cout << "Step 5:" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  Enter or change the debit card information:            " << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  1. DEBIT CARD HOLDER NAME:  " << vecDebitCardInfo[0] << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  2. DEBIT CARD NUMBER:       " << vecDebitCardInfo[1] << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  3. EXPIRATION DATE:         " << vecDebitCardInfo[2] << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  4. SECURITY CODE:           " << vecDebitCardInfo[3] << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  Enter or change info by entering corresponding number  " << endl;
													cout << "------  5. Change payment method                               " << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  !!!Please make sure all the info is correct !!! -------" << endl;
													cout << "------  !!! Late penalty may apply if info is wrong !!! -------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  6. Confirm the payment                                 " << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cin >> sDebitCardInput;
													if (integerCheck(sDebitCardInput) && sDebitCardInput.length() < int(10) && (stoi(sDebitCardInput) == 1 || stoi(sDebitCardInput) == 2 || stoi(sDebitCardInput) == 3 || stoi(sDebitCardInput) == 4))
													{
														int iCardInfo = stoi(sDebitCardInput);
														//cardholder name
														if (iCardInfo == 1)
														{
															cout << "------ Please enter the First Name:" << endl;
															cin >> sDebitCardFirstName;
															cout << "------ Please enter the Last Name:" << endl;
															cin >> sDebitCardLastName;
															sDebitCardName = sDebitCardFirstName + " " + sDebitCardLastName;
															vecDebitCardInfo[0] = sDebitCardName;
															continue;
														}
														//debit card #
														else if (iCardInfo == 2)
														{
															cout << "------ Please enter the debit card #:" << endl;
															cin >> sDebitCardNumber;
															vecDebitCardInfo[1] = sDebitCardNumber;
															continue;
														}
														//expiration date
														else if (iCardInfo == 3)
														{
															cout << "------ Please enter the expiration date in the format Month/Year:" << endl;
															cin >> sDebitCardExpireDate;
															vecDebitCardInfo[2] = sDebitCardExpireDate;
															continue;
														}
														//security code
														else
														{
															cout << "------ Please enter the security code:" << endl;
															cin >> sDebitCardSecurityCode;
															vecDebitCardInfo[3] = sDebitCardSecurityCode;
															continue;
														}
													}
													else if (integerCheck(sDebitCardInput) && sDebitCardInput.length() < int(10) && stoi(sDebitCardInput) == 5)
													{
														//restore the initialization info
														vecDebitCardInfo = { "First name, Last Name", "xxxx xxxx xxxx xxxx", "Month/Year", "xxx" };
														break;
													}
													//confirmation of payment
													else if (integerCheck(sDebitCardInput) && sDebitCardInput.length() < int(10) && stoi(sDebitCardInput) == 6)
													{
														cout << "------ Your payment is Processing..." << endl;
														//update DebitCardInfo.csv
														newPayMgrC->updateDebitCardPaymentInfo(iHotelID, sRoomNumInput, sPaymentSelectionInput, sDebitCardNumber, sDebitCardName, sDebitCardExpireDate, sDebitCardSecurityCode);
														//refresh the default setting
														vecDebitCardInfo = { "First name, Last Name", "xxxx xxxx xxxx xxxx", "Month/Year", "xxx" };
														cout << "------ You can check the payment status and pending payments by entering 1 in step 3." << endl;

														//update PaymentInfo.csv (1 means pending)
														newPayMgrC->updatePaymentStatus(iHotelID, sRoomNumInput, iSelection, 1);
														break;
													}
													else
													{
														cout << "------ !!!Invalid Input!!! ------" << endl;
														continue;
													}
												}
											}
											//gift card
											else if (iType == 3)
											{
												while (true)
												{
													cout << "Step 5:" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  1. Enter or change the gift card number:               " << endl;
													cout << "------     Gift Card #: " << sGiftCardNumberInput << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  2. Change payment method                               " << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  !!!Please make sure all the info is correct !!! -------" << endl;
													cout << "------  !!! Late penalty may apply if info is wrong !!! -------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "------  3. Confirm the payment                                 " << endl;
													cout << "---------------------------------------------------------------" << endl;
													cout << "---------------------------------------------------------------" << endl;
													cin >> sGiftCardInput;
													if (integerCheck(sGiftCardInput) && sGiftCardInput.length() < int(10) && stoi(sGiftCardInput) == 1)
													{
														cout << "------ Please enter the gift card number" << endl;
														cin >> sGiftCardNumberInput;
													}
													else if (integerCheck(sGiftCardInput) && sGiftCardInput.length() < int(10) && stoi(sGiftCardInput) == 2)
													{
														sGiftCardNumberInput = "xxxxxxxxxx";
														break;
													}
													else if (integerCheck(sGiftCardInput) && sGiftCardInput.length() < int(10) && stoi(sGiftCardInput) == 3)
													{
														cout << "------ Your payment is Processing..." << endl;
														//update GiftCardInfo.csv
														newPayMgrC->updateGiftCardPaymentInfo(iHotelID, sRoomNumInput, sPaymentSelectionInput, sGiftCardNumberInput);
														//refresh the default setting
														sGiftCardNumberInput = "xxxxxxxxxx";
														cout << "------ You can check the payment status by entering 1 in step 3." << endl;

														//update PaymentInfo.csv (1 means pending)
														newPayMgrC->updatePaymentStatus(iHotelID, sRoomNumInput, iSelection, 1);
														break;
													}
													else
													{
														cout << "------ !!!Invalid Input!!! ------" << endl;
														continue;
													}
												}
											}
											else if (iType == 4)
											{
												break;
											}
											else if (iType == 5)
											{
												return;
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
								else if (iSelection == 5)
								{
									break;
								}
								else if (iSelection == 6)
								{
									return;
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
					else if (integerCheck(sPaymentInfoInput) && sPaymentInfoInput.length() < int(2) && stoi(sPaymentInfoInput) == 2)
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
			else
			{
				cout << "------ !!!Room does not exist!!! ------" << endl;
				continue;
			}
		}
		else
		{
			cout << "test 2" << endl;
			cout << "------ !!!Invalid Input!!! ------" << endl;
			continue;
		}
	}

}

CPaymentInterfaceC::CPaymentInterfaceC()
{

}

CPaymentInterfaceC::~CPaymentInterfaceC()
{
}