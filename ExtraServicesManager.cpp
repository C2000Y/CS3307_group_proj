////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  methods used by C & P to manage extra services
////////////////////////////////////////////////////////////////////
#include "ExtraServicesManager.h"
using namespace std;

// more methods in stage 4

// get the services info from the file
CExtraServicesManager::CExtraServicesManager()
{
}
CExtraServicesManager::~CExtraServicesManager()
{
}
vector<string> CExtraServicesManager::getServiceString(string sHotelName)
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

		if (result[0] == sHotelName)
		{
			return result;
		}
		else
		{
			result.clear();
		}
	}
	return vector<string>();
}
/**
* update ESAV file
*/
void CExtraServicesManager::updateESAvFile(int sHotelName, vector<string> result)
{
	string sHotelID = to_string(sHotelName);
	string line;
	ifstream file;
	file.open("ExtraServicesAv.csv");
	vector<string> templine;
	string sNeedtoReplace = to_string(sHotelName);
	while (getline(file, line))
	{
		stringstream s_stream(line);
		while (s_stream.good())
		{
			string substr;
			getline(s_stream, substr, ',');
			templine.push_back(substr);
		}

		if (templine[0] == sHotelID)
		{
			for (int i = 1; i < templine.size(); i++)
			{
				sNeedtoReplace.append(",");
				sNeedtoReplace.append(templine[i]);
			}
			break;
		}
		else
		{
			templine.clear();
		}
	}
	file.close();
	string replacedLine = sHotelID;
	for (int i = 1; i < result.size(); i++)
	{
		replacedLine.append(",");
		replacedLine.append(result[i]);
	}
	string line_1;
	ifstream fin;
	fin.open("ExtraServicesAv.csv");
	ofstream tempFile;
	tempFile.open("temp.csv");
	while (getline(fin, line_1))
	{
		if (line_1 != sNeedtoReplace)
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
	remove("ExtraServicesAv.csv");
	rename("temp.csv", "ExtraServicesAv.csv");
}
/**
* display the extra services availbility
*/
void CExtraServicesManager::displayExtraServicesAv(int sHotelName)
{

	string sHotelID = to_string(sHotelName);
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
			if (result[1] == "true")
			{
				cout << "Gym is available" << endl;
			}
			if (result[2] != "false")
			{
				cout << "Shopping Arcade is available" << endl;
			}
			if (result[3] != "false")
			{
				cout << "Dining services is available" << endl;
			}
			break;
		}
		else
		{
			result.clear();
		}
	}
	file.close();
}

/**
* change the availebility of extra servies
* @param sHotelName Hotel id
* @param iServicesID serivecsid
*/
void CExtraServicesManager::modifyExtraServicesAv(int sHotelName, int iServicesID)
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

		if (result[0] == to_string(sHotelName))
		{
			break;
		}
		else
		{
			result.clear();
		}
	}
	if (result[0] == to_string(sHotelName))
	{

		if (result[iServicesID] == "true")
		{

			result[iServicesID] = "false";
		}
		else
		{

			result[iServicesID] = "true";
		}
	}
	updateESAvFile(sHotelName, result);
}