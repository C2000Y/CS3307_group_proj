////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  C's extra services interface
////////////////////////////////////////////////////////////////////
#ifndef ExtraServicesInterfaceC_h__
#define ExtraServicesInterfaceC_h__
#include "Headers.h"
#include "Gym.h"
#include "Arcade.h"
#include "Dining.h"
#include "ExtraServicesManager.h"
#include <sstream>
class CGym;
class CArcade;
class CDining;
class CExtraServicesManager;
using namespace std;
class CExtraServicesInterfaceC
{

private:
	int iUserinput;
	int iHotelID;
	string sHotelID;
	bool integerCheck(string);
	bool hotelCheck(string);

public:
	void customerDisplay();

public:
	CExtraServicesInterfaceC();
	~CExtraServicesInterfaceC(void);
};

#endif