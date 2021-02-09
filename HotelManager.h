//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// Manager used to manager all of the hotels classes with various STL containers
// Can pass information of hotels and their rooms to other classes
// saves and Loads Application's information of hotels and rooms
//////////////////////////////////////////////////////////////
#ifndef HotelManager_h__
#define HotelManager_h__

#include "Headers.h"

class CUser;
class CHotel;
class CRoom;

class CBookingManager;
class CHotelSpecContainer;
class CHotelManager
{
public:
	CHotelManager(void);
	~CHotelManager(void);
public:
	void Init_Manager(CBookingManager* _pBookingManager);// not implemented
public:// Not implemented yet. maybe for stage 4
	bool Create_Hotel(CUser* _pUser);// not implemented
	bool Remove_Hotel(std::string _strHotelID);// not implemented
	bool Modify_Hotel(std::string _strHotelID); // not implemented

private:
	bool Delete_Hotel(std::string _strHotelID); // deletes selected hotel// not implemented

public:
	CHotel* Find_Hotel(std::string _strHotelID); // returns hotel pointer with the desired hotel id

public: // to create based on partner listings
	void Partner_CreateHotel(std::string _strLocation, std::string _strHotelName, int _iNumberOfRooms, 
		int _iNumSmall, int _iNumMid, int _iNumBig, int _iNumHuge ,
		float _fpriceSmall, float _fpriceMid, float _fpriceBig, float _fpriceHuge,
		int _iHotelID, int _iPartnerID, bool _bPetFri, bool _bSmokeFri);

	void Partner_DeleteHotel(int _iOwnderID, int _iHotelID);


	void Partner_ChangeHotelName(int _iOwnderID, int _iHotelID, std::string _strHotelName);
	void Partner_ChangeLocation(int _iOwnderID, int _iHotelID, std::string _strLocation);

	void Partner_ChangePet(int _iOwnderID, int _iHotelID, bool _bPetFriendly);
	void Partner_ChangeSmoke(int _iOwnderID, int _iHotelID, bool _bSmokeFriendly);

	void Partner_ChangeRooms(int _iOwnderID, int _iHotelID, 
		int _iNumSmall, int _iNumMid, int _iNumBig, int _iNumHuge, 
		float _fpriceSmall, float _fpriceMid, float _fpriceBig, float _fpriceHuge,
		bool _bPetFriendly, bool _bSmokeFriendly);
	void Partner_ChangePrice(int _iOwnderID, int _iHotelID, float _fpriceSmall, float _fpriceMid, float _fpriceBig, float _fpriceHuge);

public:
	std::vector<CHotel*>* Get_HotelsBasedOnLocation(std::string _strLocation); // returns hotel vector based on location

private:
	bool Load_Manager(void); // calls load hotel and load room to load hotel on inital
	bool Save_Manager(void); // calls save hotel and save room to save upon exiting app

private: // functions for inner help
	void Tokenize_Comma(std::ifstream* _fp, std::string* _strToken); // tokenizes commas, unique way instead msdn provided method.
	void Load_Hotel(std::ifstream* _fp, CHotel** _pHotel, CHotelSpecContainer** _pHotelSpec); // loads all hotels per location
	void Load_Room(std::ifstream* _fp, CRoom** _pRoom); // Loads all the rooms per hotel

	void Save_Hotel(std::ofstream* _fp, CHotelSpecContainer* _pHotelSpec); // saves the hotels per location
	void Save_Room(std::ofstream* _fp, std::vector<CRoom*>* _pvecRooms); // saves the rooms her hotels

private:
	void Clean_Manager(void); // deallocates all memory and handle dangling pointers

public:// its not good practice... but just for this project

	std::map<std::string, std::vector<CHotel*>>* Get_HotelContainer(void);

private:
	//std::map<int, CHotel*> m_mapHotels;// think this needs to be map<location, vector<>>
	std::map<std::string, std::vector<CHotel*>> m_mapvecHotels;

	CBookingManager* m_pBookingManager;

	int m_iNumHotels;

private:
	// random
	std::random_device m_randomDevice;


};

#endif

