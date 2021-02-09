////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  Header file for User.cpp
////////////////////////////////////////////////////////////////////

#ifndef User_H__
#define User_H__


#include "Headers.h"

struct tInfo
{
	int		iUserID;
	int		iCreditCard;
	int		iAge;

	//haoran's code 
	std::string strUserID;
	std::string date;
	//haoran's code 
	std::string	strName;
	std::string	strPhoneNum;
	std::string	strUserName;
	std::string	strPassword;
	std::string	strAddress;
};

class CUserInterface;

class CUser
{
public:
	CUser();
	virtual ~CUser();

public:
	virtual int getUserID();
	virtual std::string	get_UserName();
	virtual std::string	get_Name();
	virtual std::string get_Password();
	virtual std::string get_PhoneNum();
	virtual std::string get_Address();
	virtual std::string get_Date();
	virtual bool isGuest();
	virtual int get_Age();

	virtual void set_UserID(int _iID);
	virtual void set_UserName(std::string _userName);
	virtual void set_Name(std::string _strName);
	virtual void set_Password(std::string _strPassword);
	virtual void set_PhoneNum(std::string _strPhoneNum);
	virtual void set_Address(std::string _strAddress);
	virtual void set_Date(std::string _date);
	virtual void set_Age(int _iAge);

	virtual void input_data(CUserInterface* _pInterface) = 0;
	virtual void write_account(CUserInterface* _pInterface) = 0;
	virtual void read_account(std::string username) = 0;

protected:
	tInfo get_UserInfo();

protected:
	tInfo m_tInfo;

	// bool variable to determine current user type
	// if true, it is a guest, otherwise it is a partner (if an object is not null)
	bool guest;
};

#endif
