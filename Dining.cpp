////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  dining class & methods for dining services
////////////////////////////////////////////////////////////////////
#include "Dining.h"

// more details in stage 4 not using this in stage 3
CDining::CDining(void)
{
}

CDining::~CDining(void)
{
}
bool CDining::getAvailability()
{
	return bAvailability;
}
void CDining::setAvailability()
{
	bAvailability = !bAvailability;
}
std::string CDining::disPlayMenu()
{
	for (int i = 0; i < int(vecMenu.size()); i++)
	{
		std::cout << vecMenu[i] << std::endl;
	}
	return "";
}
void CDining::displayDiningBooking()
{
	for (const auto &info : mapDiningBooking)
	{
		std::cout << info.first << ": " << info.second << std::endl;
	}
}
void CDining::addBooking(int iRoomNum, int iTime)
{
	mapDiningBooking.insert({ iRoomNum, iTime });
}

void CDining::cancelBooking(int iRoomNum)
{
	for (const auto &info : mapDiningBooking)
	{
		if (info.first == iRoomNum)
		{
			mapDiningBooking.erase(iRoomNum);
		}
	}
}
