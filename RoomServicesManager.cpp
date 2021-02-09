////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  methods that used by customer or partner to manage the roomserives
////////////////////////////////////////////////////////////////////

#include "RoomServicesManager.h"

using namespace std;

CRoomServicesManager::CRoomServicesManager(int iHotelID, int iRoomNum)
{

	getServicesString(iHotelID, iRoomNum);//get the info from the CustomerServicesInfo.csv
	priceInit(iHotelID);//initialize the price
}
CRoomServicesManager::CRoomServicesManager(void)
{
}
CRoomServicesManager::~CRoomServicesManager(void)
{

	for (const auto &info : mapRoomNumAndRoomServices)
	{
		info.second->~CRoomServices();
	}
	mapRoomNumAndRoomServices.clear();
	for (const auto &info : mapNewRoomNumAndRoomServices)
	{
		info.second->~CRoomServices();
	}
	mapNewRoomNumAndRoomServices.clear();
	vServicesList.clear();
	vecHotelServices.clear();
	vecHotelServicesPrices.clear();
}

//  private methods
////////////////////
/**
* get the info from the file and change it to a string vector
* @param ihotelID hotelid
* @param iroomNum room#
*/
vector<string> CRoomServicesManager::getServicesString(int iHotelID, int iRoomNum)
{
	string line;
	ifstream file;
	file.open("CustomerServicesInfo.csv");
	vector<string> vecRoomServicesString;
	while (getline(file, line))
	{
		stringstream s_stream(line);
		while (s_stream.good())
		{
			string substr;
			getline(s_stream, substr, ',');
			vecRoomServicesString.push_back(substr);
		}

		if (vecRoomServicesString[0] == to_string(iHotelID) && vecRoomServicesString[1] == to_string(iRoomNum))
		{
			return vecRoomServicesString;
		}
		vecRoomServicesString.clear();
	}

	return vector<string>();
}


/**
* initialize the price
* @param iHotelID hotel id
*/
void CRoomServicesManager::priceInit(int iHotelID)
{
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
			for (const auto &info : mapNewRoomNumAndRoomServices)
			{

				info.second->setLaundryPrice(stoi(result[2]));
				info.second->setDryCleanPrice(stoi(result[4]));
				info.second->setTeaPrice(stoi(result[6]));
				info.second->setCoffeePrice(stoi(result[8]));
				info.second->setBedSheetsPrice(stoi(result[10]));
			}
			for (const auto &info : mapRoomNumAndRoomServices)
			{

				info.second->setLaundryPrice(stoi(result[2]));
				info.second->setDryCleanPrice(stoi(result[4]));
				info.second->setTeaPrice(stoi(result[6]));
				info.second->setCoffeePrice(stoi(result[8]));
				info.second->setBedSheetsPrice(stoi(result[10]));
			}
		}
		else
		{
			result.clear();
		}
	}
}
/**
* create room services object and add to the map
* @param iHotelID hotel id
* @param iRoomNum room #
*/
void CRoomServicesManager::getRoomServices(int iHotelID, int iRoomNum)
{

	vector<string> vecRoomServicesString = getServicesString(iHotelID, iRoomNum);

	if (vecRoomServicesString[0] == to_string(iHotelID) && vecRoomServicesString[1] == to_string(iRoomNum))
	{
		CRoomServices *newRoomServices = new CRoomServices(stoi(vecRoomServicesString[2]), stoi(vecRoomServicesString[3]), stoi(vecRoomServicesString[4]), stoi(vecRoomServicesString[5]), stoi(vecRoomServicesString[6]), stoi(vecRoomServicesString[7]), stoi(vecRoomServicesString[8]), stoi(vecRoomServicesString[9]), stoi(vecRoomServicesString[10]), stoi(vecRoomServicesString[11]), stoi(vecRoomServicesString[12]), stoi(vecRoomServicesString[13]), stoi(vecRoomServicesString[14]), stoi(vecRoomServicesString[15]), stoi(vecRoomServicesString[16]), vecRoomServicesString[17]);
		mapRoomNumAndRoomServices.insert({ stoi(vecRoomServicesString[1]), newRoomServices });
	}
}

//  methods for partners
////////////////////////////

/**
* display all the services required by the customer
* @param iHotelID hotel id
* @param iRoomNum room #
*/
void CRoomServicesManager::checkRoomServices(int iHotelID, int iRoomNum)
{
	string line;
	ifstream file;
	file.open("CustomerServicesInfo.csv");
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

		if (result[0] == to_string(iHotelID) && result[1] == to_string(iRoomNum))
		{
			//laundry
			if (result[2] != "0")
			{
				cout << "Laundry Service: " << result[3] << endl;
			}
			//dry clean
			if (result[4] != "0")
			{
				cout << "Dry Clean Service: " << result[5] << endl;
			}
			if (result[6] != "0")
			{
				cout << "Tea Service: " << result[7] << endl;
			}
			if (result[8] != "0")
			{
				cout << "Coffee Service: " << result[9] << endl;
			}
			if (result[10] != "0")
			{
				cout << "Bed Sheets Service: " << result[11] << endl;
			}
			if (result[12] != "0")
			{
				cout << "Wake Up Time: " << result[13] << endl;
			}
			if (result[14] != "0")
			{
				cout << "Room Clean Service: ordered" << endl;
			}
			if (result[16] != "0")
			{
				cout << " DO NOT DISTURB " << endl;
			}
			if (result[18] != "0")
			{
				cout << "Msg:" << result[19] << endl;
			}

			break;
		}
		else
		{
			result.clear();
		}
	}
}
/**
* check whether the room exist and return a boolean
* @param sHotelInput the input of hotel
* @param sRoomNum room# as a string
*/
bool CRoomServicesManager::checkRoomExistance(string sHotelInput, string sRoomNum)
{

	string line;
	ifstream file;
	file.open("CustomerServicesInfo.csv");
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

		if (result[0] == sHotelInput)
		{
			if (result[1] == sRoomNum)
			{
				return true;
			}
			else
			{
				result.clear();
				continue;
			}
		}
		result.clear();
	}
	return false;
}
/**
* change the availability of certain room services
* @param iHotelID HotelID as integer
* @param iSeriveInput input implies what services are chosen
*/
void CRoomServicesManager::modifyRoomServicesAv(int iHotelID, int iServiceInput)
{
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
			//text msg stay as default
			for (int i = 1; i < result.size() - 2; i = i + 2)
			{
				vecHotelServices.push_back(result[i]);
				vecHotelServicesPrices.push_back(result[i + 1]);
			}
			break;
		}
		result.clear();
	}
	vecHotelServices.push_back("1");
	vecHotelServices.push_back("0");
	int temp = 1 - stoi(vecHotelServices[iServiceInput - 1]);
	vecHotelServices[iServiceInput - 1] = to_string(temp);
}

/**
* change the price of certain room services
* @param iHotelID hotel id
* @param iPriceSelect price
* @param iPriceInput price amount
*/
void CRoomServicesManager::modifyRoomServicesPrice(int iHotelID, int iPriceSelect, int iPriceInput)
{
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
			//text msg should not change
			for (int i = 1; i < result.size() - 2; i = i + 2)
			{
				vecHotelServicesPrices.push_back(result[i + 1]);
			}
			result.clear();
			break;
		}
		result.clear();
	}
	vecHotelServicesPrices[iPriceSelect - 1] = to_string(iPriceInput);
}

/**
* update the room services availability filr every time changes are benn made
* @param iHotelID
*/
void CRoomServicesManager::updateRSAvFile(int iHotelID)
{
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
			break;
		}
	}
	string replacedLine = to_string(iHotelID);
	for (int i = 0; i < vecHotelServices.size(); i++)
	{
		replacedLine.append(vecHotelServices[i]);
		replacedLine.append(",");
		replacedLine.append(vecHotelServicesPrices[i]);
	}
	//text Msg
	replacedLine.append("1", "0");

	string line_1;
	ifstream fin;
	fin.open("RoomServicesAv.csv");
	ofstream temp;
	temp.open("temp.csv");

	while (getline(fin, line_1))
	{
		if (line_1 != line)
		{
			temp << line_1 << endl;
		}
		else
		{
			temp << replacedLine << endl;
		}
	}

	temp.close();
	fin.close();
	remove("RoomServicesAv.csv");
	rename("temp.csv", "RoomServicesAv.csv");
}

/**
*  display the notification and remove automatically after the P see it
* @param iHotelID
*/
void CRoomServicesManager::displayNotification(int iHotelID)
{
	string line;
	ifstream file;
	file.open("newRequiredServicesInfo.csv");
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
			cout << result[1] << ":" << endl;
			int j = -1;
			for (int i = 2; i <= 11; i = i + 2)
			{
				j++;
				if (result[i] != "0")
				{
					cout << vServicesList[j] << ":" << result[i + 1] << endl;
				}
			}
			if (result[12] != "0")
			{
				cout << "Wake up Time: " << result[13] << endl;
			}
			if (result[14] != "0")
			{
				cout << "Room clean." << endl;
			}
			if (result[16] != "0")
			{
				cout << "DO NOT DISTURB!" << endl;
			}
			cout << result[19] << endl;
			break;
		}
	}
}
/**
* remove the notification file
*/
void CRoomServicesManager::removeNotification()
{
	remove("Notification.csv");
}

/**
* change the prices of room services
* @param iHotelID
* @param iRoomNum
* @param iServiceID
* @param iServiceNum
* @param string sMsg msg they input
*/
void CRoomServicesManager::modifyRoomServicesP(int iHotelID, int iRoomNum, int iServiceID, int iServiceNum, string sMsg)
{
	getRoomServices(iHotelID, iRoomNum);
	int currentNum;
	int newNum;

	for (const auto &info : mapRoomNumAndRoomServices)
	{
		if (info.first == iRoomNum)
		{
			if (iServiceID == 1)
			{

				currentNum = info.second->getLaundryNum();
				newNum = currentNum - iServiceNum;
				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
					break;
				}
				else if (newNum == 0)
				{
					info.second->changeLaundryStatus();
				}
				else
				{

					info.second->setLaundryNum(newNum);
					cout << "updated" << endl;
					cout << "Amount not provided: " << newNum << endl;
				}
			}

			else if (iServiceID == 2)
			{

				currentNum = info.second->getDryCleanNum();
				newNum = currentNum - iServiceNum;

				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
					break;
				}
				else if (newNum == 0)
				{
					info.second->changeDryCleanStatus();
				}
				else
				{
					info.second->setDryCleanNum(newNum);
					cout << "updated" << endl;
					cout << "Amount not provided: " << newNum << endl;
				}
			}
			else if (iServiceID == 3)
			{

				currentNum = info.second->getTeaNum();
				newNum = currentNum - iServiceNum;

				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
					break;
				}
				else if (newNum == 0)
				{
					info.second->changeTeaStatus();
				}
				else
				{
					info.second->setTeaNum(newNum);
					cout << "updated" << endl;
					cout << "Amount not provided: " << newNum << endl;
				}
			}
			else if (iServiceID == 4)
			{

				currentNum = info.second->getCoffeeNum();
				newNum = currentNum - iServiceNum;

				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
					break;
				}
				else if (newNum == 0)
				{
					info.second->changeCoffeeStatus();
				}
				else
				{
					info.second->setCoffeeNum(newNum);
					cout << "updated" << endl;
					cout << "Amount not provided: " << newNum << endl;
				}
			}
			else if (iServiceID == 5)
			{

				currentNum = info.second->getBedSheetsNum();
				newNum = currentNum - iServiceNum;

				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
					break;
				}
				else if (newNum == 0)
				{
					info.second->changeBedSheetsStatus();
				}
				else
				{
					info.second->setBedSheetsNum(newNum);
					cout << "updated" << endl;
					cout << "Amount not provided: " << newNum << endl;
				}
			}

			else if (iServiceID == 6)
			{
				info.second->changeWakeUpStatus();
				info.second->setWakeUpTime(iServiceNum);
				cout << "updated" << endl;
				cout << "Current Wake Up Time: " << info.second->getWakeUpTime() << ":00" << endl;
			}
			else if (iServiceID == 7)
			{
				info.second->changeRoomCleanStatus();
				cout << "updated" << endl;
				cout << info.second->getRoomCleanStatus() << endl;
			}

			else if (iServiceID == 8)
			{
				info.second->changeDoNotDisturbStatus();
				cout << "updated" << endl;
				cout << info.second->getDNDStatus() << endl;
			}

			else if (iServiceID == 9)
			{
				info.second->changeTextMsgStatus();
				info.second->setTextMsg(sMsg);
				cout << "updated" << endl;
				cout << info.second->getTextMsgStatus() << endl;
			}
			return;
		}
	}
}



/**
* only add the room services that the customer currently add to the notification file
* @param iHotelID
* @param iRoomNum
* @param iServiceID
* @param iServiceNum
* @param string sMsg msg they input
*/
void CRoomServicesManager::addRoomServicesC(int iHotelID, int iRoomNum, int iServiceID, int iServiceNum, string sMsg)
{
	//find whether some services is already added to the new required serveices file
	string line;
	ifstream file;
	file.open("newRequiredServicesInfo.csv");
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

		if (result[0] == to_string(iHotelID) && result[1] == to_string(iRoomNum))
		{
			break;
		}
		result.clear();
	}

	CRoomServices *newRoomServices = new CRoomServices(stoi(result[2]), stoi(result[3]), stoi(result[4]), stoi(result[5]), stoi(result[6]), stoi(result[7]), stoi(result[8]), stoi(result[9]), stoi(result[10]), stoi(result[11]), stoi(result[12]), stoi(result[13]), stoi(result[14]), stoi(result[15]), stoi(result[16]), result[17]);
	if (iServiceID == 1)
	{
		if (newRoomServices->getLaundryStatus() == 0)
		{
			newRoomServices->changeLaundryStatus();
		}

		newRoomServices->setLaundryNum(iServiceNum);
	}
	else if (iServiceID == 2)
	{
		if (newRoomServices->getDryCleanStatus() == 0)
		{
			newRoomServices->changeDryCleanStatus();
		}
		newRoomServices->setDryCleanNum(iServiceNum);
	}
	else if (iServiceID == 3)
	{

		if (newRoomServices->getTeaStatus() == 0)
		{

			newRoomServices->changeTeaStatus();
		}
		newRoomServices->setTeaNum(iServiceNum);
		cout << newRoomServices->getTeaNum() << endl;
	}
	else if (iServiceID == 4)
	{
		if (newRoomServices->getCoffeeStatus() == 0)
		{
			newRoomServices->changeCoffeeStatus();
		}
		newRoomServices->setCoffeeNum(iServiceNum);
	}
	else if (iServiceID == 5)
	{
		if (newRoomServices->getBedSheetsStatus() == 0)
		{

			newRoomServices->changeBedSheetsStatus();
		}
		newRoomServices->setBedSheetsNum(iServiceNum);
	}
	else if (iServiceID == 6)
	{
		if (newRoomServices->getWakeUpStatus() == 0)
		{
			newRoomServices->changeWakeUpStatus();
		}
		newRoomServices->setWakeUpTime(iServiceNum);
	}
	else if (iServiceID == 7)
		newRoomServices->changeRoomCleanStatus();
	else if (iServiceID == 8)
		newRoomServices->changeDoNotDisturbStatus();
	else if (iServiceID == 9)
	{
		if (newRoomServices->getTextMsgStatus() == 0)
		{
			newRoomServices->changeTextMsgStatus();
		}

		newRoomServices->setTextMsg(sMsg);
	}
	mapNewRoomNumAndRoomServices.clear();
	mapNewRoomNumAndRoomServices.insert({ iRoomNum, newRoomServices });
}

/**
* create the default entry for file so that we can easily perform operation on that
* @param iHotelID
* @param iRoomNum
*/
void CRoomServicesManager::createAnEntryInNRSInfoFile(int iHotelID, int iRoomNum)
{
	ofstream fin;
	fin.open("newRequiredServicesInfo.csv");

	string entry = to_string(iHotelID) + "," + to_string(iRoomNum) + ",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,None";
	fin << entry << endl;
}
/**
* delete the entry if no services added
* @param iHotelID
* @param iRoomNum
*/
void CRoomServicesManager::deleteIfNoServicesAdded(int iHotelID, int iRoomNum)
{
	string temp = to_string(iHotelID) + "," + to_string(iRoomNum) + ",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,None";
	ifstream nRSInfo;
	string line;
	nRSInfo.open("newRequiredServicesInfo.csv");
	ofstream tempFile;
	tempFile.open("temp.csv");
	while (getline(nRSInfo, line))
	{
		if (line != temp)
		{
			tempFile << line << endl;
		}

		tempFile.close();
		nRSInfo.close();
		remove("newRequiredServicesInfo.csv");
		rename("temp.csv", "newRequiredServicesInfo.csv");
	}
}
/**
* update the notification file when after customer add some services
* @param iHotelID
* @param iRoomNum
*/
void CRoomServicesManager::updateNotificationFile(int iHotelID, int iRoomNum)
{

	ofstream fin;
	fin.open("newRequiredServicesInfo.csv");
	string temp = to_string(iHotelID) + "," + to_string(iRoomNum) + "," + mapNewRoomNumAndRoomServices.begin()->second->RSFormating();
	fin << temp << endl;
}
/**
* add the new required service to notification
*/
void CRoomServicesManager::addToNotificationFile()
{

	ofstream noteFile;
	string line;
	ifstream newRSInfoFile;
	newRSInfoFile.open("newRequiredServicesInfo.csv");
	noteFile.open("Notification.csv");
	while (getline(newRSInfoFile, line))
	{
		noteFile << line;
	}
}

/**
* modify the room services (combine old room services and new)
* @param iHotelID
* @param iRoomNum
* @param iServiceID
* @param iServiceNum
* @param string
*/
void CRoomServicesManager::modifyRoomServicesC(int iHotelID, int iRoomNum, int iServiceID, int iServiceNum = 0, string sMsg = "None")
{
	getRoomServices(iHotelID, iRoomNum);
	int currentNum;
	int newNum;
	for (const auto &info : mapRoomNumAndRoomServices)
	{
		if (info.first == iRoomNum)
		{
			if (iServiceID == 1)
			{
				if (info.second->getLaundryStatus() == 0)
				{
					info.second->changeLaundryStatus();
				}

				currentNum = info.second->getLaundryNum();
				newNum = currentNum + iServiceNum;
				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
				}
				else
				{
					info.second->setLaundryNum(newNum);
				}
			}

			else if (iServiceID == 2)
			{
				if (info.second->getDryCleanStatus() == 0)
				{
					info.second->changeDryCleanStatus();
				}

				currentNum = info.second->getDryCleanNum();
				newNum = currentNum + iServiceNum;
				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
				}
				else
				{
					info.second->setDryCleanNum(newNum);
				}
			}
			else if (iServiceID == 3)
			{
				if (info.second->getTeaStatus() == 0)
				{
					info.second->changeTeaStatus();
				}

				currentNum = info.second->getTeaNum();
				newNum = currentNum + iServiceNum;
				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
				}
				else
				{
					info.second->setTeaNum(newNum);
				}
			}
			else if (iServiceID == 4)
			{
				if (info.second->getCoffeeStatus() == 0)
				{
					info.second->changeCoffeeStatus();
				}

				currentNum = info.second->getCoffeeNum();
				newNum = currentNum + iServiceNum;
				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
				}
				else
				{
					info.second->setCoffeeNum(newNum);
				}
			}
			else if (iServiceID == 5)
			{
				if (info.second->getBedSheetsStatus() == 0)
				{
					info.second->changeBedSheetsStatus();
				}

				currentNum = info.second->getBedSheetsNum();
				newNum = currentNum + iServiceNum;
				if (newNum < 0)
				{
					cout << "!!!Wrong input number!!!" << endl;
				}
				else
				{
					info.second->setBedSheetsNum(newNum);
				}
			}

			else if (iServiceID == 6)
			{
				if (info.second->getWakeUpStatus() == 0)
				{
					info.second->changeWakeUpStatus();
				}

				info.second->setWakeUpTime(iServiceNum);
			}
			else if (iServiceID == 7)
			{
				info.second->changeRoomCleanStatus();
				if (info.second->getRoomCleanStatus() == 0)
				{
					cout << "Current: No Room Clean Services" << endl;
				}
				else
				{
					cout << "Room Clean Services already ordered" << endl;
				}
			}
			else if (iServiceID == 8)
			{
				info.second->changeDoNotDisturbStatus();
				if (info.second->getDNDStatus() == 0)
				{
					cout << "Current: DO NOT DISTRUB NOT SELECTED" << endl;
				}
				else
				{
					cout << "DO NOT DISTRUB already SELECTED" << endl;
				}
			}
			else if (iServiceID == 9)
			{
				if (info.second->getTextMsgStatus() == 0)
				{
					info.second->changeTextMsgStatus();
				}
				info.second->setTextMsg(sMsg);
			}
		}
		break;
	}
}

/**
* calculate total price of the room services
* @param iHotelID
* @param iRoomNum
*/
int CRoomServicesManager::calculateTotalPrice(int iHotelID, int iRoomNum)
{
	getRoomServices(iHotelID, iRoomNum);
	for (const auto &info : mapRoomNumAndRoomServices)
	{
		if (info.first == iRoomNum)
		{

			return info.second->calculateTotalRoomServicesPrice();
		}
	}
	return 0;
}

/**
* update the customer services information file (used by both C and P)
* @param iHotelID
* @param iroomNum
* @param msg
*/
void CRoomServicesManager::updateCSIFile(int iHotelID, int iRoomNum, string msg)
{
	string temp;
	for (const auto &info : mapRoomNumAndRoomServices)
	{
		if (info.first == iRoomNum)
		{

			temp = info.second->RSFormating();
		}
	}

	// find the line that need to update
	string line;
	ifstream file;
	file.open("CustomerServicesInfo.csv");
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

		if (result[0] == to_string(iHotelID) && result[1] == to_string(iRoomNum))
		{
			break;
		}
		result.clear();
	}
	//the updated info
	string replacedLine = to_string(iHotelID);
	replacedLine.append(",");
	replacedLine.append(to_string(iRoomNum));
	replacedLine.append(",");
	replacedLine.append(temp);
	replacedLine.append(msg);

	string line_1;
	ifstream fin;
	fin.open("CustomerServicesInfo.csv");
	ofstream tempFile;
	tempFile.open("temp.csv");
	while (getline(fin, line_1))
	{
		if (line_1 != line)
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
	remove("CustomerServicesInfo.csv");
	rename("temp.csv", "CustomerServicesInfo.csv");
}
/**
* get the current price of the servies
* @param HotelID
* @param iRoomNum
*/
int CRoomServicesManager::getCurrentPrice(int iHotelID, int iRoomNum)
{
	int currentP;
	string line_1;
	ifstream file_1;
	file_1.open("RoomServicesAv.csv");
	vector<string> result_1;
	vector<int> pricelist;
	while (getline(file_1, line_1))
	{
		stringstream s_stream(line_1);
		while (s_stream.good())
		{
			string substr_1;
			getline(s_stream, substr_1, ',');
			result_1.push_back(substr_1);
		}
		if (result_1[0] == to_string(iHotelID))
		{
			pricelist = { stoi(result_1[2]), stoi(result_1[4]), stoi(result_1[6]), stoi(result_1[8]), stoi(result_1[10]) };
		}

		else
		{
			result_1.clear();
		}
	}
	string line;
	ifstream file;
	file.open("CustomerServicesInfo.csv");
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

		if (result[0] == to_string(iHotelID) && result[1] == to_string(iRoomNum))
		{
			currentP = pricelist[0] * stoi(result[3]) + pricelist[1] * stoi(result[5]) + pricelist[2] * stoi(result[7]) + pricelist[3] * stoi(result[9]) + pricelist[4] * stoi(result[11]);
			return currentP;
		}
		else
		{
			result.clear();
		}
	}
	return 0;
}
/**
* get the price of new added services
* @param iHotelID
* @param iRoomNum
*/
int CRoomServicesManager::getNewAddedPrice(int iHotelID, int iRoomNum)
{
	int currentP;
	string line_1;
	ifstream file_1;
	file_1.open("RoomServicesAv.csv");
	vector<string> result_1;
	vector<int> pricelist;
	while (getline(file_1, line_1))
	{
		stringstream s_stream(line_1);
		while (s_stream.good())
		{
			string substr_1;
			getline(s_stream, substr_1, ',');
			result_1.push_back(substr_1);
		}
		if (result_1[0] == to_string(iHotelID))
		{
			pricelist = { stoi(result_1[2]), stoi(result_1[4]), stoi(result_1[6]), stoi(result_1[8]), stoi(result_1[10]) };
		}

		else
		{
			result_1.clear();
		}
	}
	//
	string line;
	ifstream file;
	file.open("newRequiredServicesInfo.csv");
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

		if (result[0] == to_string(iHotelID) && result[1] == to_string(iRoomNum))
		{
			currentP = pricelist[0] * stoi(result[3]) + pricelist[1] * stoi(result[5]) + pricelist[2] * stoi(result[7]) + pricelist[3] * stoi(result[9]) + pricelist[4] * stoi(result[11]);
			return currentP;
		}
		else
		{
			result.clear();
		}
	}
	return 0;
}