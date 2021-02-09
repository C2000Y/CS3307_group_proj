////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  dinning class & methods for dining services
////////////////////////////////////////////////////////////////////
#ifndef Dining_h__
#define Dining_h__
#include "Headers.h"
class CDining
{
public:
	CDining(void);
	~CDining(void);

private:
	bool bAvailability;
	std::map<int, int> mapDiningBooking;
	std::vector<std::string> vecMenu;

public:
	bool getAvailability();
	void setAvailability();
	std::string disPlayMenu();
	void displayDiningBooking();
	void addBooking(int, int);
	void cancelBooking(int);


};

#endif
