// 3307 GROUP 36

// A hotel application that is able to search and provide all the necessary information for the user to find hotels,
//  book rooms, manage its bookings, and other services provided by their chosen hotels.



// Members: Jong Hoon Lim, Shehroze Alam, Wenxuan Dai, Haoran Xu, Jingxing Gao

// also when we are commenting.
// lets provide tags to who wrote them so we know.

// i.e. the bottom comment

///* Jong *///
// This is our main.
// We should only touch this as a group
///* Jong *///

#include "HotelManager.h"
#include "BookingManager.h"
#include "HotelApp.h"

///* Jong *///
// don't change main if it's not changing structure of code.
///* Jong *///

int main(void)
{
	CHotelManager* pHotelManager = new CHotelManager;
	CBookingManager* pBookingManager = new CBookingManager;

	CHotelApp* pApp = new CHotelApp(pHotelManager, pBookingManager);

	pApp->AppInitializeState();
	pApp->AppRunningState();
	pApp->AppEndState();

	if (nullptr != pApp)
	{
		delete pApp;
	}

	// for leak check
	//_CrtDumpMemoryLeaks();

	return 0;
}

