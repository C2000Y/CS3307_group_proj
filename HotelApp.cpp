//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// most of the classes will interact with each other here.
// especially the managers and their interfaces.
//////////////////////////////////////////////////////////////
#include "HotelApp.h"

#include "BookingManager.h"
#include "HotelManager.h"
#include "User.h"
#include "HotelSearchInterface.h"
#include "UserGuest.h"

#include "Room.h"
#include "Room.h"
#include "HotelSpecContainer.h"
#include "UserGuest.h"
#include "Hotel.h"
#include "BookInterface.h"

#include "UserInterface.h"

#include "ServicesInterface.h"

//Cy
#include "PartnerAddListInterface.h"

// new
#include "PaymentInterface.h"
#include "HangedManInterface.h"

using namespace std;

CHotelApp::CHotelApp(CHotelManager * _pHotelMan, CBookingManager * _pBookingMan)
	: m_pHotelMan(_pHotelMan)
	, m_pBookingMan(_pBookingMan)
	, m_pUser(NULL)
	, m_pHotelSearchInterface(nullptr)
	, m_pBookingInterface(nullptr)
	, m_pLoginInterface(nullptr)
	, m_pServiceInterface(nullptr)
	, m_pPartnerAddlistInterface(nullptr)
	, payInterface(nullptr)
	, hObj(nullptr)
{
}

CHotelApp::~CHotelApp()
{
	if (nullptr != m_pUser)
	{
		delete m_pUser;
	}
}

void CHotelApp::AppInitializeState(void)
{
	if (nullptr == m_pHotelMan || nullptr == m_pBookingMan)
	{
		cout << "nullptr == m_pHotelMan || nullptr == m_pBookingMan !!!" << endl;
		return;
	}
	///Jong/// 
	// They have a reference to each other now.
	///Jong/// 

	m_pHotelMan->Init_Manager(m_pBookingMan);
	m_pBookingMan->Init_Manager(m_pHotelMan);

	m_pHotelSearchInterface = new CHotelSearchInterface(m_pHotelMan);

	// booking
	m_pBookingInterface = new CBookingInterface();

	// login
	m_pLoginInterface = new CUserInterface;

	m_pUser = new CUserGuest();


	// service
	m_pServiceInterface = new CServicesInterface;
	payInterface = new CPaymentInterface();
	hObj = new CHangedManInterface();

	//Cy
	m_pPartnerAddlistInterface = new CPartnerAddListInterface( m_pHotelMan);
	

	cout << "Initialized app" << endl;
}

void CHotelApp::AppRunningState(void)
{
	///Jong/// 
	// this is where the program is constantly running.
	///Jong/// 

	string strUserinput = "";

	cout << "Running State" << endl;

	bool _bExitProg = false;
	bool _bEscape = false;

	m_pUser->set_UserID(1); 

	int _iCompareValue = 0;

	while (!_bExitProg)
	{
		//m_pLoginInterface->TakeUserInfo(CUser* pUser);

		// if user is partner is guest

		_iCompareValue = m_pLoginInterface->FirstMenu();
		if (_iCompareValue == -1)
		{
			break;
		}
		else if (_iCompareValue == 1)  // Partner
		{
			m_pPartnerAddlistInterface->Run_Interface(m_pUser->getUserID());

			continue; // goes back to login
		}
		else if (_iCompareValue == 0)// guest
		{
			while (!_bExitProg) // program loop
			{
				while (true) // looping for search interface
				{
					if (m_pHotelSearchInterface->Get_UsedAdvOption()) //if used 
					{
						m_pHotelSearchInterface->Set_UsedAdvOption(false);
						if (m_pHotelSearchInterface->Run_Search())
						{
							// result is found
							// toss information to other person. 

							// need to grab user from login interface
							if (m_pBookingInterface->runInterface(m_pBookingMan, m_pHotelSearchInterface->Get_SelectedHotel(), to_string(1), dynamic_cast<CUserGuest*>(m_pUser)))
							{
								// go to services

								cout << "-----------------------------------------------------------------------" << endl;
								cout << "BOOKING COMPLETE!" << endl;
								cout << "-----------------------------------------------------------------------" << endl;

								// temp switch to get to extra services as it is prototype stage
								//  the logic of the whole program skeleton is there
								// but the meaty parts are not completed ... thus lack of connectivity

								while (true)
								{

									cout << "-----------------------------------------------------------------------" << endl;
									cout << "------------------- Would you like to use services? -------------------" << endl;
									cout << "-----------------------------------------------------------------------" << endl;
									cout << "1. Yes. Take me to services " << endl;
									cout << "2. No. please exit program " << endl;
									cout << "-----------------------------------------------------------------------" << endl;
									cout << "-----------------------------------------------------------------------" << endl;

									cout << "Your choice: (1 to 2) :"; cin >> strUserinput;


									if (strUserinput.length() > 3)
									{
										system("clear");
										continue;
									}
									if (stoi(strUserinput) == 1)
									{
										if (m_pServiceInterface->services_display())
										{
											hObj->HangedManGameDisplay(); // hangman

											// exit 
											_bExitProg = true;
											break;
										}

										break;
									}
									else if (stoi(strUserinput) == 2)
									{
										_bExitProg = true;
										break;
									}
									else
									{
										system("clear");
										continue;
									}
								}
							}
							else // if something else like exiting 
							{

							}
							break;// exit search loop
						}
						else
						{
							// no result
							// have to catch here rather if we are using adv search or
							// we are simply exiting

							continue; // search again 
						}
					}
					else
					{
						if (m_pHotelSearchInterface->Run_Interface()) // search using the parameters 
						{
							// did user choose suggested?
							if (m_pHotelSearchInterface->CheckSuggChosen())
							{
								m_pHotelSearchInterface->UseSuggChoice();

								if (m_pBookingInterface->runInterface(m_pBookingMan, m_pHotelSearchInterface->Get_SelectedHotel(), to_string(1), dynamic_cast<CUserGuest*>(m_pUser)))
								{
									// go to services
									cout << "-----------------------------------------------------------------------" << endl;
									cout << "BOOKING COMPLETE!" << endl;
									cout << "-----------------------------------------------------------------------" << endl;

									// temp switch to get to extra services as it is prototype stage
									//  the logic of the whole program skeleton is there
									// but the meaty parts are not completed ... thus lack of connectivity
									while (true)
									{
										cout << "-----------------------------------------------------------------------" << endl;
										cout << "------------------- Would you like to use services? -------------------" << endl;
										cout << "-----------------------------------------------------------------------" << endl;
										cout << "1. Yes. Take me to services " << endl;
										cout << "2. No. please exit program " << endl;
										cout << "-----------------------------------------------------------------------" << endl;
										cout << "-----------------------------------------------------------------------" << endl;

										cout << "Your choice: (1 to 2) :"; cin >> strUserinput;

										if (strUserinput.length() > 3)
										{
											system("clear");
											continue;
										}
										if (stoi(strUserinput) == 1)
										{
											if (m_pServiceInterface->services_display())
											{
												hObj->HangedManGameDisplay(); // hangman

												// exit 
												_bExitProg = true;
												break;
											}

											break;
										}
										else if (stoi(strUserinput) == 2)
										{
											_bExitProg = true;
											break;
										}
										else
										{
											system("clear");
											continue;
										}
									}
								}
								else // if something else like exiting 
								{

								}
								break;// exit search loop
							}
							else // regular search
							{
								if (m_pHotelSearchInterface->Run_Search())
								{
									// result is found
									// toss information to other person. 

									// need to grab user from login interface
									//m_pBookingInterface->runInterface(m_pBookingMan, m_pHotelSearchInterface->Get_SelectedHotel(), to_string(m_pHotelSearchInterface->Get_SelectedNumPeople()), dynamic_cast<CUserGuest*>(m_pUser));
									if (m_pBookingInterface->runInterface(m_pBookingMan, m_pHotelSearchInterface->Get_SelectedHotel(), to_string(1), dynamic_cast<CUserGuest*>(m_pUser)))
									{
										// go to services

										cout << "-----------------------------------------------------------------------" << endl;
										cout << "BOOKING COMPLETE!" << endl;
										cout << "-----------------------------------------------------------------------" << endl;

										// temp switch to get to extra services as it is prototype stage
										//  the logic of the whole program skeleton is there
										// but the meaty parts are not completed ... thus lack of connectivity

										while (true)
										{

											cout << "-----------------------------------------------------------------------" << endl;
											cout << "------------------- Would you like to use services? -------------------" << endl;
											cout << "-----------------------------------------------------------------------" << endl;
											cout << "1. Yes. Take me to services " << endl;
											cout << "2. No. please exit program " << endl;
											cout << "-----------------------------------------------------------------------" << endl;
											cout << "-----------------------------------------------------------------------" << endl;

											cout << "Your choice: (1 to 2) :"; cin >> strUserinput;


											if (strUserinput.length() > 3)
											{
												system("clear");
												continue;
											}
											if (stoi(strUserinput) == 1)
											{
												if (m_pServiceInterface->services_display())
												{
													hObj->HangedManGameDisplay(); // hangman

													// exit 
													_bExitProg = true;
													break;
												}

												break;
											}
											else if (stoi(strUserinput) == 2)
											{
												_bExitProg = true;
												break;
											}
											else
											{
												system("clear");
												continue;
											}
										}
									}
									else // if something else like exiting 
									{

									}
									break;// exit search loop
								}
								else
								{
									// no result
									// have to catch here rather if we are using adv search or
									// we are simply exiting
									continue; // search again 
								}
							}
						}
						else // exit program or go back to login screen
						{
							_bEscape = true;
							break;// exit search loop
						}
					}
				}
				if (_bEscape)
				{
					_bEscape = false;
					break;
				}
			}
		}
	}
}

void CHotelApp::AppEndState(void)
{
	if (nullptr != m_pUser)
	{
		delete m_pUser;
		m_pUser = nullptr;
	}

	if (nullptr != m_pLoginInterface)
	{
	delete m_pLoginInterface;
	m_pLoginInterface = nullptr;
	}

	if (nullptr != m_pBookingInterface)
	{
	delete m_pBookingInterface;
	m_pBookingInterface = nullptr;
	}

	if (nullptr != m_pHotelSearchInterface)
	{
	delete m_pHotelSearchInterface;
	m_pHotelSearchInterface = nullptr;
	}

	if (nullptr != m_pServiceInterface)
	{
		delete m_pServiceInterface;
		m_pServiceInterface = nullptr;
	}

	if (nullptr != payInterface)
	{
		delete payInterface;
		payInterface = nullptr;
	}

	if (nullptr != hObj)
	{
		delete hObj;
		hObj = nullptr;
	}

	if (nullptr != m_pPartnerAddlistInterface)
	{
		delete m_pPartnerAddlistInterface;
		m_pPartnerAddlistInterface = nullptr;
	}

	if (nullptr != m_pHotelMan)
	{
		delete m_pHotelMan;
		m_pHotelMan = nullptr;
	}
	if (nullptr != m_pBookingMan)
	{
		delete m_pBookingMan;
		m_pBookingMan = nullptr;
	}

	cout << "App Ended" << endl;
}
