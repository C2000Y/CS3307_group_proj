////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  C's extra services interface
////////////////////////////////////////////////////////////////////
#include "ExtraServicesInterfaceC.h"
using namespace std;
bool CExtraServicesInterfaceC::integerCheck(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
	return true;
}
bool CExtraServicesInterfaceC::hotelCheck(string sHotelID)
{

	string line;
	ifstream file;
	file.open("ExtraServicesAv.csv");
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

		if (result[0] == sHotelID)
		{
			return true;
		}
		else
		{
			result.clear();
		}
	}
	return false;
}
/**
* interface for customer
*/
void CExtraServicesInterfaceC::customerDisplay()
{

	iHotelID = stoi(sHotelID);

	cout << "Availability of the following services: " << endl;
	CExtraServicesManager *ESManagerC = new (CExtraServicesManager);
	ESManagerC->displayExtraServicesAv(iHotelID);
}
CExtraServicesInterfaceC::CExtraServicesInterfaceC()
{

}

CExtraServicesInterfaceC::~CExtraServicesInterfaceC()
{
}