//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description:
// Interface to interact with the user
// in this case the hotels and user's preference regards to the hotels
// they are looking for and their rooms.
// Searching algorithm is also used here, preferrenced by the user
// i.e. location, number of rooms, number of people in thoses rooms.. etc
//////////////////////////////////////////////////////////////
#ifndef HotelSearchInterface_H__
#define HotelSearchInterface_H__

#include "Headers.h"

#define DEFAULT_YEAR 2020
#define DEFAULT_MONTH 11
#define DEFAULT_DAY 1
#define DEFAULT_HOUR 11
#define DEFAULT_MINUTE 55

#define LIST_PER_PAGE 15

class CRoom;
class CHotel;
class CHotelManager;
class CHotelSuggInterface;

class CHotelSearchInterface
{
public:
	explicit CHotelSearchInterface(CHotelManager* _pHotelManager);
	~CHotelSearchInterface(void);

private:
	enum eMAINMENU 
	{ 
		OPT_LOCATION = 1,
		OPT_CHECKIN,
		OPT_CHECKOUT,
		OPT_NUMROOM,
		OPT_NUMPEOPLE,
		OPT_CONFIRM,
		OPT_SUGG,
		OPT_EXIT,
		OPT_END
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
	enum eCheckMode
	{
		MODE_YEAR,
		MODE_MONTH,
		MODE_DAY,
		MODE_END
	};

public:
	bool Run_Interface(void); // main interface for hotel fidnings
	bool Run_Search(void); // main search

private:
	bool Search_Hotel_Interface_SameHotel(void); // searche algorithm from user's choice of rooms, room size, checkin/out date, location.. etc

private:
	void Display_NoResult(void);
	bool Display_Results(void);

private:
	void Menu_Location(void);
	void Menu_CheckIn(void);
	void Menu_CheckOut(void);
	void Menu_NumRoom(void);
	void Menu_NumPeople(void);

private:
	void Show_SearchDisplay(void); 

private:
	bool Prompt_User( int _iMin, int _iMax,  int _imaxstrlen = 7); // promts user input  from min value to max
	bool Check_IfNumber(std::string str); // checks if string is a number 
private:
	void Default_CheckOutDay(void); // 48 hr + default check out date depedning on check in date

	void Recalc_num_people(void); // relcaluates the number ofpeople 

public:
	void N_Format(int _iDigit); // formats its so if single digit put "0" infront for nice interface
private:
	void Clear_ResultMap(void); // clears map
	void Clear_ResultVector(void); // clears vector
private:
	// returns 1  if src Older Date
	// returns 0  if both Same Date
	// returns -1 if src Younger Date
	int Compare_Dates(int _SrcYear, int _SrcMonth, int _SrcDay, int _DstYear, int _DstMonth, int _DstDay);

public:
	CHotel* Get_SelectedHotel(void); // returns user's choice of hotel
	int		Get_SelectedNumPeople(void); // grabs the selected number of people 


public: // sugg
	std::vector<std::string>* Get_Cities(void);

	bool CheckSuggChosen(void);

	void UseSuggChoice(void);

private: // advanced search?
	void MoreSearchOptions(void);
	void Adv_DisplayCheckMenu(void);
	void Adv_ChangeRatingSettings(void);

public: //adv
	bool Get_UsedAdvOption(void);
	void Set_UsedAdvOption(bool _bOpt);

private:
	// this will be the results
	//std::map<std::string, std::vector<CHotel*>> m_mapvecSearchResults;
	// just need vector of hotels from results found.
	// and need room numbers that are selected.
	std::vector<CHotel*> m_vecResultHotels;
	std::map<std::string, std::vector<int>>  m_mapvecRoomNumbers;


private:
	CHotelManager* m_pHotelManager;
	std::string m_strUserInput;

	std::string m_strLocation;

	int m_iNumberOfPeople;

	int m_iCheckInYear;
	int m_iCheckInMonth;
	int m_iCheckInDay;
	int m_iCheckInHour;
	int m_iCheckInMinute;

	int m_iCheckOutYear;
	int m_iCheckOutMonth;
	int m_iCheckOutDay;
	int m_iCheckOutHour;
	int m_iCheckOutMinute;

	std::vector<int> m_vecNumPeoplePerRoom;

private:
	// for flipping pages
	int m_iPageNum;
	int m_iIndexForPage;
private:
	// for check in/out mode
	eCheckMode m_eCheckMode;
private:
	// If the user Selects the hotel, then
	// return that information

	CHotel* m_pHotelThatIsSelected;

private:
	// for suggested

	CHotelSuggInterface* m_pSuggInterface;

	bool m_bCheckIfWeAreUsingSuggested;

private:// for adv
	bool m_bSearchPetAllowed;
	bool m_bSearchSmokeAllowed;
	bool m_bSearchRatingAllowed;
	int m_iCurrMinRating;

	bool m_bCheckUseAdvfilters;

	bool m_bUsedAdvOption;

// list of cities 
private:
	std::vector<std::string> m_vecCities =
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
