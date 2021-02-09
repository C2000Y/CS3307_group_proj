//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// This class is used to display to the user a randomized hotels and rooms
// It will display and ther user will be able to use the suggested option for their choice
//////////////////////////////////////////////////////////////

#ifndef HotelSuggestedInterface_H__
#define HotelSuggestedInterface_H__

#include "Headers.h"

class CHotelManager;
class CHotel;
class CHotelSearchInterface;

class CHotelSuggInterface
{
public:
	/**
	A constructor that allows the sugg interface to use hotelmanager and search interfaces's functions
	@param _hotelmanager a object pointer
	@param _pSearchInterface a object pointer
	*/
	explicit CHotelSuggInterface(CHotelManager* _pHotelManager, CHotelSearchInterface* _pSearchInterface);
	/**
	A Deconstructor
	*/
	~CHotelSuggInterface(void);


// this class need to take a look at the rooms in the hotels
// and randomly suggest a room
// or randomly suggested based on rating

public:

	/**
	@param void
	@return void
	*/
	void Ready_Sugg(void);
	
	
	void Display_Sugg(void);

public:
	CHotel* Grab_SuggHotel(void);

private:
	void Clean_Sugg(void);

private:
	void Select_Random_HotelRooms(void);

private:
	std::random_device m_randomDevice;

	CHotelManager* m_pHotelManager;
	CHotelSearchInterface* m_pSearchInterface;

	std::map<std::string, std::vector<CHotel*>>* m_pMapVecHotelRooms;
	std::vector<std::string>* m_pCities;


	int m_iSelValueLocations;
	int m_iSelValueHotels;
	int m_iSelValueRooms;

};

#endif // HotelSuggestedInterface_H__
