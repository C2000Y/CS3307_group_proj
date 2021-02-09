////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  P's extra services interface
////////////////////////////////////////////////////////////////////
#ifndef ExtraServicesInterfaceP_h__
#define ExtraServicesInterfaceP_h__
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
class CExtraServicesInterfaceP
{

private:
	std::string sUserinput;
	std::string sServiceInput;
	int iHotelID;
	bool integerCheck(std::string);

public:
	void partnerDisplay();

public:
	CExtraServicesInterfaceP();
	~CExtraServicesInterfaceP(void);
};

#endif