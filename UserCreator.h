////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  Header file for UserCreator.cpp
////////////////////////////////////////////////////////////////////

#ifndef UserCreator_H__
#define UserCreator_H__

// abstract class that provides default implementation of the factory method

class CUser;
class CUserGuest;
class CUserPartner;

class CUserCreator
{
public:
	virtual ~CUserCreator() {};
	virtual CUser* FactoryMethod() const = 0;
};

class CUserGuestCreator : public CUserCreator
{
public:
	virtual CUser* FactoryMethod() const override;
};

class CUserPartnerCreator : public CUserCreator
{
public:
	virtual CUser* FactoryMethod() const override;
};

#endif