////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  gym class and methods
////////////////////////////////////////////////////////////////////
#ifndef Gym_h__
#define Gym_h__
#include "Headers.h"

class CGym
{
public:
	CGym(void);
	~CGym(void);

private:
	bool bTennisStatus;
	bool bTableTennisStatus;
	bool bBadmintonStatus;
	bool bSwimmingStatus;
	bool bSpinningBikeStatus;
	bool bBasketballStatus;
	bool bWorkOutEquipmentStatus;
	bool bSquashStatus;
	int iOpenTime;
	int iCloseTime;


public:

	void setTennisStatus();
	void setTableTennisStatus();
	void setBadmintonStatus();
	void setSwimmingStatus();
	void setSpinningBikeStatus();
	void setBasketballStatus();
	void setWorkOutEquipmentStatus();
	void setSquashStatus();
	void setOpenTime(int);
	void setCloseTime(int);
	int getOpenTime();
	int getCloseTime();
	void disPlayoperationTime();
	void displayAvailableActivities();


};

#endif
