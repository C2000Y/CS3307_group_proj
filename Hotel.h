//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// Contains information of basic hotel to function as one.
// contains hotelspec object which has all the hotel information
//
//////////////////////////////////////////////////////////////

#ifndef Hotel_h__
#define Hotel_h__

#include "Headers.h"

#define ROOMSIZETYPES 4

class CRoom;
class CHotelSpecContainer;
class CHotel
{
public:
	CHotel(CHotelSpecContainer* _pHotelSpec);
public:
	CHotel(void);
	~CHotel(void);

public:

public:
	void Create_Room_WithSize(int eSize);
	// creating rooms should be for partner's user stories as well.

public:
	void PushTo_Vector(CRoom* _pRoom); // pushes to vector.. in the future will recalculate number of sized rooms 
	std::vector<CRoom*>* Get_RoomVector(void);

public:
	CHotelSpecContainer* Get_HotelSpec(void); // only use it for saving 

public:
	void Set_HotelName(std::string _strHotelName);
	void Set_Location(std::string _strLocation);

	void Set_NumberOfRooms(int _iNumRoom);

public:
	int Get_NumberofRooms(void);
	int Get_NumberofSizedRooms(int _iRoomSize);

	int Get_HotelRating(void);

	float Get_RoomCost(int _iRoomSize);

	std::string Get_HotelName(void);
	
	int Get_HotelRegID(void);

	int Get_OwnderID(void);


private:
	void Clean_Storage(void);

private:
	std::vector<CRoom*> m_vecRooms;
private:
	CHotelSpecContainer* m_pHotelSpec;
	CRoom* m_pRoomShell;
private:
	// number of room sizes

	int m_iNumRoomSize[ROOMSIZETYPES];


};

#endif
