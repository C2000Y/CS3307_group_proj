//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// This will be our whole app's state 
// and there is a initilaiztion state that prepares the app 
// and running state which will be the constant state that will keep running 
// and will have all of the interactiosn happening there
// and the end state whcih will hapen when the user decides to end the app
//////////////////////////////////////////////////////////////
#ifndef HotelApp_h__
#define HotelApp_h__


class CBookingManager;
class CHotelManager;
class CUser;
class CHotelSearchInterface;
class CBookingInterface;
class CUserInterface;
class CServicesInterface;
class CPaymentInterface;
class CHangedManInterface;
//Cy
class CPartnerAddListInterface;

class CHotelApp
{
public:
	explicit CHotelApp(CHotelManager* _pHotelMan,CBookingManager* _pBookingMan);
	~CHotelApp();

public:
	void AppInitializeState(void); // Initializes all the classes when app starts
	void AppRunningState(void); // our main function that will be running while app is running.
	void AppEndState(void); // cleans all the classes when app ends

private:// managers and interfaces 
	CHotelManager* m_pHotelMan;
	CBookingManager* m_pBookingMan;
	CUser* m_pUser;
	CHotelSearchInterface* m_pHotelSearchInterface;
	CBookingInterface* m_pBookingInterface;
private:// login
	CUserInterface* m_pLoginInterface;

private: // service
	CServicesInterface* m_pServiceInterface;

private:// cy
	CPartnerAddListInterface* m_pPartnerAddlistInterface;
private:// new
	CPaymentInterface *payInterface;
	CHangedManInterface *hObj;
};

#endif

