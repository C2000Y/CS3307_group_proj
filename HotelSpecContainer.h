//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// Created a seperate object just to keep all the hotel information for conivence
// when changes are mode.	
//////////////////////////////////////////////////////////////
#ifndef HotelSpecContainer_h__
#define HotelSpecContainer_h__

#include "Headers.h"

class CHotelSpecContainer
{
public:
	/*
	Constructor
	*/
	CHotelSpecContainer(void);
	/*
	deConstructor
	*/
	~CHotelSpecContainer(void);

public:
	/*
	@Param void
	@return int OwnderId
	*/
	int getOwnderID(void);
	/*
	@Param void
	@return int 
	*/
	int getHotelReg(void);
	/*
	@Param void
	@return int 
	*/
	int getRating(void);
	/*
	@Param void
	@return int 
	*/
	int getContractYear(void);
	/*
	@Param void
	@return int 
	*/
	int getContractRemain(void);
	/*
	@Param void
	@return int 
	*/
	int getNumEmployee(void);
	/*
	@Param void
	@return int 
	*/
	int getNumOfRoom(void);
	/*
	@Param void
	@return float 
	*/
	float getMantainCost(void);
	/*
	@Param void
	@return float 
	*/
	float getEarning(void);
	/*
	@Param void
	@return string 
	*/
	std::string getHotelName(void);
	/*
	@Param void
	@return string 
	*/
	std::string getHotelCode(void);
	/*
	@Param void
	@return string 
	*/
	std::string getLocation(void);

public:
	/*
	@Param int
	@return void
	*/
	void setOwnderID(int _iOwnerID);
	/*
	@Param int
	@return void
	*/
	void setHotelReg(int _iHotelReg);
	/*
	@Param int
	@return void
	*/
	void setRating(int _iRating);
	/*
	@Param int
	@return void
	*/
	void setContractYear(int _iContractYear);
	/*
	@Param int
	@return void
	*/
	void setContractRemain(int _iContractRemain);
	/*
	@Param int
	@return void
	*/
	void setNumEmployee(int _iNumEmployee);
	/*
	@Param int
	@return void
	*/
	void setNumOfRoom(int _iNumOfRoom);
	/*
	@Param float
	@return void
	*/
	void setMantainCost(float _fMantainCost);
	/*
	@Param float
	@return void
	*/
	void setEarning(float _fEarning);

	/*
	@Param string
	@return void
	*/
	void setHotelName(std::string _strHotelName);
	/*
	@Param string
	@return void
	*/
	void setHotelCode(std::string _strHotelCode);
	/*
	@Param string
	@return void
	*/
	void setLocation(std::string _strLocation);

private:
	int m_iOwnerID; 
	int m_iHotelReg; // hotel registration number.
	int m_iRating; 
	int m_iContractYear;
	int m_iContractRemain;
	int m_iNumEmployee;
	int m_iNumOfRooms;

	float m_fMantainCost;
	float m_fEarning;

	std::string m_strHotelName;
	std::string m_strHotelCode;
	std::string m_strLocation;
};

#endif

