////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  gym class and methods
////////////////////////////////////////////////////////////////////
#include "Gym.h"
#include "Headers.h"
// more details in stage 4 not using this in stage 3
CGym::CGym(void)
{
}

void CGym::setTennisStatus()
{
	bTennisStatus = !bTennisStatus;
}
void CGym::setTableTennisStatus()
{
	bTableTennisStatus = !bTableTennisStatus;
}
void CGym::setBadmintonStatus()
{
	bBadmintonStatus = !bBadmintonStatus;
}
void CGym::setSwimmingStatus()
{
	bSwimmingStatus = !bSwimmingStatus;
}
void CGym::setSpinningBikeStatus()
{
	bSpinningBikeStatus = !bSpinningBikeStatus;
}
void CGym::setBasketballStatus()
{
	bBasketballStatus = !bBasketballStatus;
}
void CGym::setWorkOutEquipmentStatus()
{
	bWorkOutEquipmentStatus = !bWorkOutEquipmentStatus;
}
void CGym::setSquashStatus()
{
	bSquashStatus = !bSquashStatus;
}
void CGym::setOpenTime(int openT)
{
	iOpenTime = openT;
}
void CGym::setCloseTime(int closeT)
{
	iCloseTime = closeT;
}

void CGym::disPlayoperationTime()
{
	std::cout << "Open:" << iOpenTime << " - " << iCloseTime << std::endl;
}
void CGym::displayAvailableActivities()
{
	std::vector<bool> gymExStatus = { bTennisStatus, bTableTennisStatus, bBadmintonStatus, bSwimmingStatus, bSpinningBikeStatus, bBasketballStatus, bWorkOutEquipmentStatus, bSquashStatus };
	std::vector<std::string> gymEx = { "Tennis", "Table Tennis", "Badminton", "Swimming", "Spinning Bike", "Basketball", "Work Out Equipment", "Squash" };

	std::cout << "Current Available: ";
	for (int i = 0; i < gymExStatus.size(); i++)
	{
		if (gymExStatus[i] == true)
		{
			std::cout << gymEx[i] << std::endl;
		}
	}
}

CGym::~CGym(void)
{
}
