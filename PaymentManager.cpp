////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#include "PaymentManager.h"
using namespace std;
CPaymentManager::CPaymentManager(int iHotelID)
{
	//insert all the info in PaymentInfo.csv to the map
	string line;
	ifstream file;
	file.open("PaymentInfo.csv");

	while (getline(file, line))
	{
		stringstream s_stream(line);
		while (s_stream.good())
		{
			string substr;
			getline(s_stream, substr, ',');
			vecPaymentString.push_back(substr);
		}
		if (vecPaymentString[0] == to_string(iHotelID))
		{
			//create obj
			CPayment *paymentObj = new CPayment(stoi(vecPaymentString[2]), stoi(vecPaymentString[3]), stoi(vecPaymentString[4]), stoi(vecPaymentString[5]), stoi(vecPaymentString[6]), stoi(vecPaymentString[7]));
			//insert into map
			mapRoomNumAndPaymentInfo.insert({ stoi(vecPaymentString[1]), paymentObj }); //room # & payment obj
																						//empty the vecPaymentString and free the memory
																						//free(paymentObj);
		}
		vecPaymentString.clear();
	}
}

CPaymentManager::~CPaymentManager()
{

	for (const auto &info : mapRoomNumAndPaymentInfo) {
		info.second->~CPayment();
	}
	mapRoomNumAndPaymentInfo.clear();
	vecPaymentString.clear();

	vecCCPendingPayment.clear();
	vecDCPendingPayment.clear();
	vecGCPendingPayment.clear();
}

/**
* format the display staff
* @param statusNum
*/
void CPaymentManager::statusFormatingAndDisplay(int statusNum)
{
	if (statusNum == 0)
	{
		cout << "------ Status: Paid" << endl;
	}
	else if (statusNum == 1)
	{
		cout << "------ Status: Waiting for the confirmation from hotels..." << endl;
	}
	// only take 0,1,2
	else
	{
		cout << "------ Status: Not paid or payment denied" << endl;
	}
}

/**
* display room payment info
* @param
*/
void CPaymentManager::displayPaymentInfo(int iRoomNum)
{
	cout << "------ Room #: " << iRoomNum << endl;
	cout << "------ Bills:" << endl;
	//room
	if (mapRoomNumAndPaymentInfo.at(iRoomNum)->getRoomPayment() == 0)
	{
		cout << "------ Room: $0" << endl;
	}
	else
	{
		cout << "------ Room: $" << mapRoomNumAndPaymentInfo.at(iRoomNum)->getRoomPayment() << endl;
		statusFormatingAndDisplay(mapRoomNumAndPaymentInfo.at(iRoomNum)->getRoomStatus());
	}
	cout << "-------------------------------------------------------------" << endl;
	//room services
	if (mapRoomNumAndPaymentInfo.at(iRoomNum)->getRoomServicesPayment() == 0)
	{
		cout << "------ Room Services: $0" << endl;
	}
	else
	{
		cout << "------ Room Services: $" << mapRoomNumAndPaymentInfo.at(iRoomNum)->getRoomServicesPayment() << endl;
		statusFormatingAndDisplay(mapRoomNumAndPaymentInfo.at(iRoomNum)->getRoomServicesStatus());
	}
	cout << "-------------------------------------------------------------" << endl;
	//extra services
	if (mapRoomNumAndPaymentInfo.at(iRoomNum)->getRoomServicesPayment() == 0)
	{
		cout << "------ Extra Services: $0" << endl;
	}
	else
	{
		cout << "------ Extra Services: $" << mapRoomNumAndPaymentInfo.at(iRoomNum)->getExtraServicesPayment() << endl;
		statusFormatingAndDisplay(mapRoomNumAndPaymentInfo.at(iRoomNum)->getExtraServicesStatus());
	}
}
/**
* check if the room exist
* @param iRoomNum
*/
bool CPaymentManager::checkRoomExistance(int iRoomNum)
{
	//true if room # appears in the map
	return (mapRoomNumAndPaymentInfo.count(iRoomNum));
}

/**
* credit card info and bill(s) that customers want to pay

*/
void CPaymentManager::updateCreditCardPaymentInfo(int iHotelID, string sRoomNum, string sType, string sCCHName, string sCCNum, string sEDate, string sSecCode)
{
	string temp = iHotelID + "," + sRoomNum + "," + sType + "," + sCCHName + "," + sCCNum + "," + sEDate + "," + sSecCode + "\n";
	string line;

	ifstream file;
	file.open("CreditCardInfo.csv");
	ofstream tempFile;
	tempFile.open("temp.csv");

	while (getline(file, line))
	{

		tempFile << line << endl;
	}
	tempFile << temp << endl;
	tempFile.close();

	file.close();
	remove("CreditCardInfo.csv");
	rename("temp.csv", "CreditCardInfo.csv");
}
/**
* debit card info and bill(s) that customers want to pay
*/
void CPaymentManager::updateDebitCardPaymentInfo(int iHotelID, string sRoomNum, string sType, string sDCHName, string sDCNum, string sEDate, string sSecCode)
{
	string temp = iHotelID + "," + sRoomNum + "," + sType + "," + sDCHName + "," + sDCNum + "," + sEDate + "," + sSecCode + "\n";
	string line;
	ifstream file;
	file.open("DebitCardInfo.csv");
	ofstream tempFile;
	tempFile.open("temp.csv");

	while (getline(file, line))
	{

		tempFile << line << endl;
	}
	tempFile << temp << endl;
	tempFile.close();

	file.close();
	remove("DebitCardInfo.csv");
	rename("temp.csv", "DebitCardInfo.csv");
}
/**
* gift card info and bill(s) that customers want to pay
*/
void CPaymentManager::updateGiftCardPaymentInfo(int iHotelID, string sRoomNum, string sType, string sGCNum)
{
	string temp = iHotelID + "," + sRoomNum + "," + sType + "," + sGCNum + "\n";
	string line;
	ifstream file;
	file.open("GiftCardInfo.csv");
	ofstream tempFile;
	tempFile.open("temp.csv");

	while (getline(file, line))
	{

		tempFile << line << endl;
	}
	tempFile << temp << endl;
	tempFile.close();

	file.close();
	remove("GiftCardInfo.csv");
	rename("temp.csv", "GiftCardInfo.csv");
}
//update pending amount if status is 0(paid)
//payment type and status type
/*
payment types:
type 1: room
type 2: room services
type 3: extra services
type 4: all
status types:
type 0: paid
type 1: pending
type 2:not paid or denied
*/
void CPaymentManager::updatePaymentStatus(int iHotelID, string sRoomNum, int iType, int iStatusType)
{
	int iRoomNum = stoi(sRoomNum);
	if (iType == 1)
	{
		if (iStatusType == 0)
		{
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomStatus(iStatusType);
			// set amount to be 0 is payment is confirmed
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomPayment(0);
		}
		else
		{
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomStatus(iStatusType);
		}
	}
	else if (iType == 2)
	{
		if (iStatusType == 0)
		{
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomServicesStatus(iStatusType);
			// set amount to be 0 is payment is confirmed
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomServicesPayment(0);
		}
		else
		{
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomServicesStatus(iStatusType);
		}
	}
	else if (iType == 3)
	{
		if (iStatusType == 0)
		{
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setExtraServicesStatus(iStatusType);
			// set amount to be 0 is payment is confirmed
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setExtraServicesPayment(0);
		}
		else
		{
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setExtraServicesStatus(iStatusType);
		}
	}
	else
	{
		if (iStatusType == 0)
		{
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomStatus(iStatusType);
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomServicesStatus(iStatusType);
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setExtraServicesStatus(iStatusType);
			//set pending amount to 0 when payment is confirmed
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomPayment(0);
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomServicesPayment(0);
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setExtraServicesPayment(0);
		}
		else
		{
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomServicesStatus(iStatusType);
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomServicesStatus(iStatusType);
			mapRoomNumAndPaymentInfo.at(iRoomNum)->setRoomServicesStatus(iStatusType);
		}
	}

	updatePaymentInfoFile(iHotelID, iRoomNum);
}
/**
* update the payment info
*/
void CPaymentManager::updatePaymentInfoFile(int iHotelID, int iRoomNum)
{
	string temp;
	for (const auto &info : mapRoomNumAndPaymentInfo)
	{
		if (info.first == iRoomNum)
		{

			temp = info.second->paymentFormatting();
		}
	}
	string line;
	ifstream file;
	file.open("PaymentInfo.csv");
	string slineNeedToReplace = to_string(iHotelID);
	vector<string> vecPString;
	while (getline(file, line))
	{
		stringstream s_stream(line);
		while (s_stream.good())
		{
			string substr;
			getline(s_stream, substr, ',');
			vecPString.push_back(substr);
		}

		if (vecPString[0] == to_string(iHotelID) && vecPString[1] == to_string(iRoomNum))
		{
			for (int i = 1; i < vecPString.size(); i++)
			{
				slineNeedToReplace.append(",");
				slineNeedToReplace.append(vecPString[i]);
			}

			break;
		}
		else
		{
			vecPString.clear();
		}
	}

	//the updated info
	string replacedLine = to_string(iHotelID);
	replacedLine.append(",");
	replacedLine.append(to_string(iRoomNum));
	replacedLine.append(temp);
	string line_1;
	ifstream fin;
	fin.open("PaymentInfo.csv");
	ofstream tempFile;
	tempFile.open("temp.csv");

	while (getline(fin, line_1))
	{
		if (line_1 != slineNeedToReplace)
		{
			tempFile << line_1 << endl;
		}
		else
		{
			tempFile << replacedLine << endl;
		}
	}
	tempFile.close();
	fin.close();
	remove("PaymentInfo.csv");
	rename("temp.csv", "PaymentInfo.csv");
}
/**
* private method to assist with displayAllPendingPayment
* @param iHotelID
* @param sRoomNum
*/
void CPaymentManager::displayCreditCardPendingPayment(int iHotelID, string sRoomNum)
{
	string line;
	ifstream file;
	file.open("CreditCardInfo.csv");

	while (getline(file, line))
	{
		stringstream s_stream(line);
		while (s_stream.good())
		{
			string substr;
			getline(s_stream, substr, ',');
			vecCCPendingPayment.push_back(substr);
		}
		if (vecCCPendingPayment[0] == to_string(iHotelID) && vecCCPendingPayment[1] == sRoomNum)
		{
			cout << "------ Room #:" << vecCCPendingPayment[1] << endl;
			int iPaymentType = stoi(vecCCPendingPayment[2]);
			if (iPaymentType == 1)
			{
				cout << "------ Room Bill\nCredit Card Info:";
			}
			else if (iPaymentType == 2)
			{
				cout << "------ Room Services Bill\nCredit Card Info:";
			}
			else if (iPaymentType == 3)
			{
				cout << "------ Extra Services Bill\nCredit Card Info:";
			}
			else
			{
				cout << "------ Total Bill\nCredit Card Info:";
			}
			cout << "------ CardHolder Name: " << vecCCPendingPayment[3] << endl;
			cout << "------ Card #:          " << vecCCPendingPayment[4] << endl;
			cout << "------ Expiration Date: " << vecCCPendingPayment[5] << endl;
			cout << "------ Security Code:   " << vecCCPendingPayment[6] << endl;
		}
		vecCCPendingPayment.clear();
	}
}
/**
* dispaly debit pay info
*/
void CPaymentManager::displayDebitCardPendingPayment(int iHotelID, string sRoomNum)
{
	string line;
	ifstream file;
	file.open("DebitCardInfo.csv");

	while (getline(file, line))
	{
		stringstream s_stream(line);
		while (s_stream.good())
		{
			string substr;
			getline(s_stream, substr, ',');
			vecDCPendingPayment.push_back(substr);
			if (vecDCPendingPayment[0] == to_string(iHotelID) && vecDCPendingPayment[1] == sRoomNum)
			{
				cout << "------ Room #:" << vecDCPendingPayment[1] << endl;
				int iPaymentType = stoi(vecDCPendingPayment[2]);
				if (iPaymentType == 1)
				{
					cout << "------ Room Bill\nDebit Card Info:";
				}
				else if (iPaymentType == 2)
				{
					cout << "------ Room Services Bill\nDebit Card Info:";
				}
				else if (iPaymentType == 3)
				{
					cout << "------ Extra Services Bill\nDebit Card Info:";
				}
				else
				{
					cout << "------ Total Bill\nDebit Card Info:";
				}
				cout << "------ CardHolder Name: " << vecDCPendingPayment[3] << endl;
				cout << "------ Card #:          " << vecDCPendingPayment[4] << endl;
				cout << "------ Expiration Date: " << vecDCPendingPayment[5] << endl;
				cout << "------ Security Code:   " << vecDCPendingPayment[6] << endl;
			}
			vecDCPendingPayment.clear();
		}
	}
}
void CPaymentManager::displayGiftCardPendingPayment(int iHotelID, string sRoomNum)
{
	string line;
	ifstream file;
	file.open("GiftCardInfo.csv");

	while (getline(file, line))
	{
		stringstream s_stream(line);
		while (s_stream.good())
		{
			string substr;
			getline(s_stream, substr, ',');
			vecGCPendingPayment.push_back(substr);
			if (vecGCPendingPayment[0] == to_string(iHotelID) && vecGCPendingPayment[1] == sRoomNum)
			{
				cout << "------ Room #:" << vecGCPendingPayment[1] << endl;
				cout << "------ Gift Card #:" << vecGCPendingPayment[2] << endl;
			}
			vecGCPendingPayment.clear();
		}
	}
}
//get the info from the credit,debit,gift card info.
void CPaymentManager::displayAllPendingPayment(int iHotelID, string sRoomNum)
{
	cout << "------ All pending transaction and payment methods:" << endl;
	displayCreditCardPendingPayment(iHotelID, sRoomNum);
	displayDebitCardPendingPayment(iHotelID, sRoomNum);
	displayGiftCardPendingPayment(iHotelID, sRoomNum);
}

void CPaymentManager::updateRoomServicePrice(int iRoomNum, int price)
{
	string temp;
	for (const auto &info : mapRoomNumAndPaymentInfo)
	{
		if (info.first == iRoomNum)
		{
			info.second->setRoomServicesPayment(price);
			info.second->setRoomServicesStatus(2);
			temp = info.second->paymentFormatting();
			break;
		}
	}
}
/**
* update the room price
*/
void CPaymentManager::updateRoomPrice(int iRoomNum, int price)
{
	string temp;
	for (const auto &info : mapRoomNumAndPaymentInfo)
	{
		if (info.first == iRoomNum)
		{
			info.second->setRoomPayment(price);
			info.second->setRoomStatus(2);
			temp = info.second->paymentFormatting();
			break;
		}
	}
}
void CPaymentManager::updateExtraServicePrice(int iRoomNum, int price)
{
	string temp;
	for (const auto &info : mapRoomNumAndPaymentInfo)
	{
		if (info.first == iRoomNum)
		{
			info.second->setExtraServicesPayment(price);
			info.second->setExtraServicesStatus(2);
			temp = info.second->paymentFormatting();
			break;
		}
	}
}
