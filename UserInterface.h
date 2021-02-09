////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  Header file for UserInterface.cpp
////////////////////////////////////////////////////////////////////

#ifndef UserInterface_H__
#define UserInterface_H__


#include "Headers.h"
#include "UserCreator.h"

class CUserGuest;
class CUserPartner;

class CUserInterface
{
public:
	~CUserInterface();

	bool Guest();
	bool Partner();
	bool DisplayUser();
	int FirstMenu();
	void Close();
	void Delay(int j);

	void AddGuest(CUserGuest* guest);
	void AddPartner(CUserPartner* partner);

private:
	void FirstMenuScreen();
	void GuestScreen();
	void PartnerScreen();

private:
	std::string strchoice;

	// list of pointers on guests and partners objects created by factory method in CUserCreator subclasses
	std::vector<CUserGuest*> guests;
	std::vector<CUserPartner*> partners;

	// creators
	CUserGuestCreator guestCreator;
	CUserPartnerCreator partnerCreator;

	// current user
	CUser* loggedInUser;

public:
	static constexpr const char* guestsInfoPath = "guest_info.txt";
	static constexpr const char* guestsAccountPath = "guest_account.txt";

	static constexpr const char* partnersInfoPath = "partner_info.txt";
	static constexpr const char* partnersAccountPath = "partner_account.txt";
};

#endif
