////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  methods used by C & P to manage extra services
////////////////////////////////////////////////////////////////////
#ifndef ExtraServicesManager_h__
#define ExtraServicesManager_h__

#include "Headers.h"
#include "Gym.h"
#include "Arcade.h"
#include "Dining.h"
#include <sstream>
class Gym;
class Arcade;
class Dining;
using namespace std;
class CExtraServicesManager
{

private:
	//availbility
	map<string, vector<bool> *> mapHotelNameAndExtraSAv;
	vector<string> vecExtraSAv;

	vector<string> vecExtraS = { "Gym", "Dining", "Arcade" };

public:
	vector<string> getServiceString(string);

	//customer
	void displayExtraServicesAv(int);
	//partner
	void modifyExtraServicesAv(int, int);     //hotelname,Services ID(1,2,3)
	void updateESAvFile(int, vector<string>); //hotelname, info
	int calculateTotalPrice(int);
	CExtraServicesManager();
	~CExtraServicesManager();
};

#endif