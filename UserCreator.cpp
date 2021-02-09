////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  User's Login Interface, system will determine the identity of user and login their account
////////////////////////////////////////////////////////////////////

#include "UserCreator.h"
#include "UserGuest.h"
#include "UserPartner.h"

// create new guest in factory method
CUser* CUserGuestCreator::FactoryMethod() const
{
	return new CUserGuest();
}

// create new partner in factory method
CUser* CUserPartnerCreator::FactoryMethod() const
{
	return new CUserPartner();
}
