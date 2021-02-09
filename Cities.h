//////////////////////////////////////////////////////////////
///JONG
// Jong Hoon Lim
///JONG
// Short description: Just collect of Location data
// could have been a data txt file
// might change later. but made into vector for convient iterating.
//
//////////////////////////////////////////////////////////////
#ifndef Cities__H_
#define Cities__H_

#include "Headers.h"

//enum eLocation
//{
//	Airdrie = 1
//	, Beaumont
//	, Brooks
//	, Calgary
//	, Camrose
//	, Chestermere
//	, Cold_Lake
//	, Edmonton
//	, Fort_Saskatchewan
//	, Grande_Prairie
//	, Lacombe
//	, Leduc
//	, Lethbridge
//	, Lloydminster
//	, Medicine_Hat
//	, Red_Deer
//	, Spruce_Grove
//	, St_Albert
//	, Wetaskiwin
//	, Abbotsford
//	, Armstrong
//	, Burnaby_Burnaby
//	, Campbell_River
//	, Castlegar
//	, Chilliwack
//	, Colwood_Colwood
//	, Coquitlam
//	, Courtenay
//	, Cranbrook
//	, Dawson_Creek
//	, Delta
//	, Duncan
//	, Enderby
//	, Fernie
//	, Grand_Forks
//	, Greenwood
//	, Kamloops
//	, Kelowna
//	, Kimberley
//	, Langford
//	, Langley
//	, Maple
//	, Merritt
//	, Nanaimo
//	, Nelson
//	, New_Westminster
//	, North_Vancouver
//	, Parksville
//	, Penticton
//	, Pitt_Meadows
//	, Port_Alberni
//	, Port_Coquitlam
//	, Port_Moody
//	, Powell_River
//	, Prince_George
//	, Prince_Rupert
//	, Quesnel
//	, Revelstoke
//	, Richmond
//	, Rossland
//	, Salmon_Arm
//	, Surrey
//	, Terrace
//	, Trail
//	, Vancouver
//	, Vernon
//	, Victoria
//	, West_Kelowna
//	, White_Rock
//	, Williams_Lake
//	, Brandon
//	, Dauphin
//	, Flin_Flon
//	, Morden
//	, Portage_la_Prairie
//	, Selkirk
//	, Steinbach
//	, Thompson
//	, Winkler
//	, Winnipeg
//	, Bathurst
//	, Campbellton
//	, Dieppe
//	, Edmundston
//	, Fredericton
//	, Miramichi
//	, Moncton
//	, Saint_John
//	, Yellowknife
//	, Iqaluit
//	, Barrie
//	, Belleville
//	, Brampton
//	, Brant
//	, Brantford
//	, Brockville
//	, Burlington
//	, Cambridge
//	, Clarence_Rockland
//	, Cornwall
//	, Dryden
//	, Elliot_Lake
//	, Greater_Sudbury
//	, Guelph
//	, Haldimand_County
//	, Hamilton
//	, Kawartha_Lakes
//	, Kenora
//	, Kingston
//	, Kitchener
//	, London
//	, Markham
//	, Mississauga
//	, Niagara_Falls
//	, Norfolk_County
//	, North_Bay
//	, Orillia
//	, Oshawa
//	, Ottawa
//	, Owen_Sound
//	, Pembroke
//	, Peterborough
//	, Pickering
//	, Port_Colborne
//	, Prince_Edward_County
//	, Quinte_West
//	, Richmond_Hill
//	, Sarnia
//	, St_Catharines
//	, St_Thomas
//	, Stratford
//	, Temiskaming_Shores
//	, Thorold
//	, Thunder_Bay
//	, Timmins
//	, Toronto
//	, Vaughan
//	, Waterloo
//	, Welland
//	, Windsor
//	, Woodstock
//	, Charlottetown
//	, Summerside
//	, Yorkton
//	, Gotham_City
//	, Raccoon_City
//	, Vice_City
//	, Goron_City
//	, Arkham_City
//	, Silent_Hill
//};

//std::vector<std::string> m_vecCities =
//{
//	"Airdrie"
//	, "Beaumont"
//	, "Brooks"
//	, "Calgary"
//	, "Camrose"
//	, "Chestermere"
//	, "Cold_Lake"
//	, "Edmonton"
//	, "Fort_Saskatchewan"
//	, "Grande_Prairie"
//	, "Lacombe"
//	, "Leduc"
//	, "Lethbridge"
//	, "Lloydminster"
//	, "Medicine_Hat"
//	, "Red_Deer"
//	, "Spruce_Grove"
//	, "St_Albert"
//	, "Wetaskiwin"
//	, "Abbotsford"
//	, "Armstrong"
//	, "Burnaby_Burnaby"
//	, "Campbell_River"
//	, "Castlegar"
//	, "Chilliwack"
//	, "Colwood_Colwood"
//	, "Coquitlam"
//	, "Courtenay"
//	, "Cranbrook"
//	, "Dawson_Creek"
//	, "Delta"
//	, "Duncan"
//	, "Enderby"
//	, "Fernie"
//	, "Grand_Forks"
//	, "Greenwood"
//	, "Kamloops"
//	, "Kelowna"
//	, "Kimberley"
//	, "Langford"
//	, "Langley"
//	, "Maple"
//	, "Merritt"
//	, "Nanaimo"
//	, "Nelson"
//	, "New_Westminster"
//	, "North_Vancouver"
//	, "Parksville"
//	, "Penticton"
//	, "Pitt_Meadows"
//	, "Port_Alberni"
//	, "Port_Coquitlam"
//	, "Port_Moody"
//	, "Powell_River"
//	, "Prince_George"
//	, "Prince_Rupert"
//	, "Quesnel"
//	, "Revelstoke"
//	, "Richmond"
//	, "Rossland"
//	, "Salmon_Arm"
//	, "Surrey"
//	, "Terrace"
//	, "Trail"
//	, "Vancouver"
//	, "Vernon"
//	, "Victoria"
//	, "West_Kelowna"
//	, "White_Rock"
//	, "Williams_Lake"
//	, "Brandon"
//	, "Dauphin"
//	, "Flin_Flon"
//	, "Morden"
//	, "Portage_la_Prairi"
//	, "Selkirk"
//	, "Steinbach"
//	, "Thompson"
//	, "Winkler"
//	, "Winnipeg"
//	, "Bathurst"
//	, "Campbellton"
//	, "Dieppe"
//	, "Edmundston"
//	, "Fredericton"
//	, "Miramichi"
//	, "Moncton"
//	, "Saint_John"
//	, "Yellowknife"
//	, "Iqaluit"
//	, "Barrie"
//	, "Belleville"
//	, "Brampton"
//	, "Brant"
//	, "Brantford"
//	, "Brockville"
//	, "Burlington"
//	, "Cambridge"
//	, "Clarence_Rockland"
//	, "Cornwall"
//	, "Dryden"
//	, "Elliot_Lake"
//	, "Greater_Sudbury"
//	, "Guelph"
//	, "Haldimand_County"
//	, "Hamilton"
//	, "Kawartha_Lakes"
//	, "Kenora"
//	, "Kingston"
//	, "Kitchener"
//	, "London"
//	, "Markham"
//	, "Mississauga"
//	, "Niagara_Falls"
//	, "Norfolk_County"
//	, "North_Bay"
//	, "Orillia"
//	, "Oshawa"
//	, "Ottawa"
//	, "Owen_Sound"
//	, "Pembroke"
//	, "Peterborough"
//	, "Pickering"
//	, "Port_Colborne"
//	, "Prince_Edward_Cou"
//	, "Quinte_West"
//	, "Richmond_Hill"
//	, "Sarnia"
//	, "St_Catharines"
//	, "St_Thomas"
//	, "Stratford"
//	, "Temiskaming_Shore"
//	, "Thorold"
//	, "Thunder_Bay"
//	, "Timmins"
//	, "Toronto"
//	, "Vaughan"
//	, "Waterloo"
//	, "Welland"
//	, "Windsor"
//	, "Woodstock"
//	, "Charlottetown"
//	, "Summerside"
//	, "Yorkton"
//	, "Gotham_City"
//	, "Raccoon_City"
//	, "Vice_City"
//	, "Goron_City"
//	, "Arkham_City"
//	, "Silent_Hill"
//};




#endif // Cities__H_
