////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  Header file for UserPartner.h
////////////////////////////////////////////////////////////////////

#ifndef UserPartner_h__
#define UserPartner_h__

#include "UserInterface.h" 
#include "Headers.h"
#include "User.h"

class CUserPartner : public CUser
{
public:
	CUserPartner();

	void input_data(CUserInterface* _pInterface);
	void write_account(CUserInterface* _pInterface);
	void read_account(std::string username);
};

#endif
