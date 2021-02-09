////////////////////////////////////////////////////////////////////
//  Written by: Haoran Xu
//  This is class for User
////////////////////////////////////////////////////////////////////

#include "User.h"
#include "Headers.h"

using namespace std;

CUser::CUser()
{
	m_tInfo = {};
}

CUser::~CUser()
{
}

int CUser::getUserID()
{
	return m_tInfo.iUserID;
}

string CUser::get_UserName()
{
	return m_tInfo.strUserName;
}

string CUser::get_Name()
{
	return m_tInfo.strName;
}

string CUser::get_Password()
{
	return m_tInfo.strPassword;
}

string CUser::get_PhoneNum()
{
	return m_tInfo.strPhoneNum;
}

string CUser::get_Address()
{
	return m_tInfo.strAddress;
}

string CUser::get_Date()
{
	return m_tInfo.date;
}

int CUser::get_Age()
{
	return m_tInfo.iAge;
}

bool CUser::isGuest()
{
	return guest;
}

void CUser::set_UserID(int _iID)
{
	m_tInfo.iUserID = _iID;
}

void CUser::set_UserName(string _userName)
{
	m_tInfo.strUserName = _userName;
}

void CUser::set_Name(string _strName)
{
	m_tInfo.strName = _strName;
}

void CUser::set_Password(string _strPassword)
{
	m_tInfo.strPassword = _strPassword;
}

void CUser::set_PhoneNum(string _strPhoneNum)
{
	m_tInfo.strPhoneNum = _strPhoneNum;
}

void CUser::set_Address(string _strAddress)
{
	m_tInfo.strAddress = _strAddress;
}

void CUser::set_Date(string _date)
{
	m_tInfo.date = _date;
}

void CUser::set_Age(int _iAge)
{
	m_tInfo.iAge = _iAge;
}

tInfo CUser::get_UserInfo()
{
	return m_tInfo;
}
