////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#include "PaymentInterface.h"
using namespace std;
CPaymentInterface::CPaymentInterface()
{

}
CPaymentInterface::~CPaymentInterface()
{
}
bool CPaymentInterface::integerCheck(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}
/**
* display paymnet interface
*/
void CPaymentInterface::paymentDisplay()
{
	while (true)
	{
		cout << "------ PaymentInterface:" << endl;
		cout << "------ Are you partner or customer?" << endl;
		cout << "------ 1. Customer" << endl;
		cout << "------ 2. Partner" << endl;
		cout << "------ 3. exit" << endl;
		cin >> sInput;

		if (integerCheck(sInput) && sInput.length() < int(10))
		{
			if (stoi(sInput) == 1)
			{
				CPaymentInterfaceC *payInterfaceC = new CPaymentInterfaceC();
				payInterfaceC->paymentDisplay();

			}
			else if (stoi(sInput) == 2)
			{
				CPaymentInterfaceP *payInterfaceP = new CPaymentInterfaceP();
				payInterfaceP->paymentPartnerDisplay();

			}
			else if (stoi(sInput) == 3)
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
/**
* add pending payment (used by booking manager)
*/
void CPaymentInterface::addPendingPayment(int iHotelID, int iRoomID, int iPrice)
{
	string sAddedStr;
	sAddedStr = to_string(iHotelID) + "," + to_string(iRoomID) + "," + to_string(iPrice) + "," + "2,0,0,0,0";
	string replacedLine;
	string line;
	ifstream file;
	vector<string> result;
	file.open("PaymentInfo.csv");

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
			replacedLine = result[0];
			for (int i = 1; i < result.size(); i++)
			{
				replacedLine.append(",");
				replacedLine.append(result[i]);
			}
			break;
		}

		else
		{
			result.clear();
		}
	}
	file.close();

	string line_1;
	ifstream fin;
	fin.open("PaymentInfo.csv");
	ofstream tempFile;
	tempFile.open("temp.csv");

	while (getline(fin, line_1))
	{
		if (line_1 != replacedLine)
		{
			tempFile << line_1 << endl;
		}
		else
		{
			tempFile << sAddedStr << endl;
		}
	}
	tempFile.close();
	fin.close();
	remove("PaymentInfo.csv");
	rename("temp.csv", "PaymentInfo.csv");
}