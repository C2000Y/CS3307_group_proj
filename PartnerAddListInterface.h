#ifndef PartnerAddListInterface_H__
#define PartnerAddListInterface_H__
#include "Headers.h"
#include <sstream> 
#include <algorithm> 
#include <iomanip>
#define HOTEL_PER_PAGE 5

class CRoom;
class CHotel;
class CHotelManager;
class CHotelSearchInterface;
class CUser;

class CPartnerAddListInterface
{
public:
	explicit CPartnerAddListInterface(CHotelManager* _pHotelManager);
	~CPartnerAddListInterface(void);

private:
	enum eMAINMENU
	{
		OPT_ADDLIST = 1,
		OPT_UPDATELIST,
		OPT_ViewList,
		OPT_EXIT,
	};
private:
	enum eLOCMENU
	{
		LOC_PREV = 16,
		LOC_NEXT,
		LOC_BACK,
		LOC_END
	};
private:
	enum eENTERMode
	{
		MODE_LOCATION,
		MODE_ROOMSIZE,
		MODE_BEDTYPE,
		MODE_PRICE,
		MODE_PARKINGSPOT,
		MODE_END
	};

public:
	bool Run_Interface(int PartnerID);

private:
	void Menu_createList(int PartnerID);
	void Menu_Location(void);
	void Menu_addRoom(void);
	void Menu_Parkingspot(void);


	void Menu_updateList(int PartnerID);
	void Menu_SelectList(int PartnerID);

	void Menu_viewList(int PartnerID);
	void Menu_HotelName(void);


	void Menu_DeleteList(void);
	void Menu_EditList(void);
	void Menu_EditPrice(void);

private:
	void Show_Display(void);

private:
	bool Prompt_User(int _iMin, int _iMax, size_t _imaxstrlen = 7);
	bool FPrompt_User(float _iMin, float _iMax, size_t _imaxstrlen = 11);
	bool Check_IfNumber(std::string str);
	bool Check_IfNumberF(std::string str);

private:
	void Recalc_num_people(void);

private:
	void N_Format(int _iDigit);
	void Clear_ResultMap(void);
	void Clear_ResultVector(void);
	void SaveCreation(int PartnerID);
	void SaveEdition(int PartnerID);

	void SizetoString(int size);
	bool ifexist(int arr[], int size, int input);
	void signtoarr(int arr[4], int input, int num);
	bool hascomma(std::string str);
	int GenerateHotelID(std::string FileName);
	void createHotelList(int PartnerID, std::string FileName);
	void GetAllHotelElement(int PartnerID, std::string FileName, int HotelID);
	void DeleteHotel(int PartnerID, int HotelID, std::string FileName);
	void ResetVariable(void);
	bool ifroomhasprice(void);
	bool hasroom(void);
	int totalrooms(void);
	bool hasprice(void);



private:
	CHotelManager* m_pHotelManager;
	std::string m_strUserInput;

	std::string m_strLocation;
	std::vector<int> m_vecHotelID;
	std::vector<std::string> m_vecHotelName;
	std::vector<std::string> m_vecHotelLocation;
	std::string HotelName;
	float price[4];
	int m_numRoom[4];
	int parkingspot;
	bool PetFriendly;
	bool SmokeFriendly;
	int rating;

	const int NUM_OF_ROOMSIZE = 4;
	const int NUM_OF_BEDTYPE = 4;
	const std::string HOTELFILE = "PartnerHotel.txt";
	int HotelID;
private:

	// for flipping pages
	int m_iPageNum;
	int m_iIndexForPage;
	std::string location;

private:
	eENTERMode m_eEnter;
	std::vector<std::string> m_vecCities2 =
	{
		"Airdrie"
		, "Beaumont"
		, "Brooks"
		, "Calgary"
		, "Camrose"
		, "Chestermere"
		, "Cold_Lake"
		, "Edmonton"
		, "Fort_Saskatchewan"
		, "Grande_Prairie"
		, "Lacombe"
		, "Leduc"
		, "Lethbridge"
		, "Lloydminster"
		, "Medicine_Hat"
		, "Red_Deer"
		, "Spruce_Grove"
		, "St_Albert"
		, "Wetaskiwin"
		, "Abbotsford"
		, "Armstrong"
		, "Burnaby_Burnaby"
		, "Campbell_River"
		, "Castlegar"
		, "Chilliwack"
		, "Colwood_Colwood"
		, "Coquitlam"
		, "Courtenay"
		, "Cranbrook"
		, "Dawson_Creek"
		, "Delta"
		, "Duncan"
		, "Enderby"
		, "Fernie"
		, "Grand_Forks"
		, "Greenwood"
		, "Kamloops"
		, "Kelowna"
		, "Kimberley"
		, "Langford"
		, "Langley"
		, "Maple"
		, "Merritt"
		, "Nanaimo"
		, "Nelson"
		, "New_Westminster"
		, "North_Vancouver"
		, "Parksville"
		, "Penticton"
		, "Pitt_Meadows"
		, "Port_Alberni"
		, "Port_Coquitlam"
		, "Port_Moody"
		, "Powell_River"
		, "Prince_George"
		, "Prince_Rupert"
		, "Quesnel"
		, "Revelstoke"
		, "Richmond"
		, "Rossland"
		, "Salmon_Arm"
		, "Surrey"
		, "Terrace"
		, "Trail"
		, "Vancouver"
		, "Vernon"
		, "Victoria"
		, "West_Kelowna"
		, "White_Rock"
		, "Williams_Lake"
		, "Brandon"
		, "Dauphin"
		, "Flin_Flon"
		, "Morden"
		, "Portage_la_Prairi"
		, "Selkirk"
		, "Steinbach"
		, "Thompson"
		, "Winkler"
		, "Winnipeg"
		, "Bathurst"
		, "Campbellton"
		, "Dieppe"
		, "Edmundston"
		, "Fredericton"
		, "Miramichi"
		, "Moncton"
		, "Saint_John"
		, "Yellowknife"
		, "Iqaluit"
		, "Barrie"
		, "Belleville"
		, "Brampton"
		, "Brant"
		, "Brantford"
		, "Brockville"
		, "Burlington"
		, "Cambridge"
		, "Clarence_Rockland"
		, "Cornwall"
		, "Dryden"
		, "Elliot_Lake"
		, "Greater_Sudbury"
		, "Guelph"
		, "Haldimand_County"
		, "Hamilton"
		, "Kawartha_Lakes"
		, "Kenora"
		, "Kingston"
		, "Kitchener"
		, "London"
		, "Markham"
		, "Mississauga"
		, "Niagara_Falls"
		, "Norfolk_County"
		, "North_Bay"
		, "Orillia"
		, "Oshawa"
		, "Ottawa"
		, "Owen_Sound"
		, "Pembroke"
		, "Peterborough"
		, "Pickering"
		, "Port_Colborne"
		, "Prince_Edward_Cou"
		, "Quinte_West"
		, "Richmond_Hill"
		, "Sarnia"
		, "St_Catharines"
		, "St_Thomas"
		, "Stratford"
		, "Temiskaming_Shore"
		, "Thorold"
		, "Thunder_Bay"
		, "Timmins"
		, "Toronto"
		, "Vaughan"
		, "Waterloo"
		, "Welland"
		, "Windsor"
		, "Woodstock"
		, "Charlottetown"
		, "Summerside"
		, "Yorkton"
		, "Gotham_City"
		, "Raccoon_City"
		, "Vice_City"
		, "Goron_City"
		, "Arkham_City"
		, "Silent_Hill"
	};
};
#endif
