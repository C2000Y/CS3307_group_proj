////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#ifndef PaymentInterfaceP_h__
#define PaymentInterfaceP_h__
#include "Headers.h"
#include "PaymentManager.h"
#include <sstream>
using namespace std;

class CPaymentInterfaceP
{
private:
    vector<string> vecHotels; //store all the names of hotels
    bool integerCheck(string);
    bool bHotelExistance;
    int iHotelID=1223;
    string sPartnerSelection;
    string sRoomNumber;
    string sPaymentTypeInput;
    string sStatusInput;

public:
    CPaymentInterfaceP();
    ~CPaymentInterfaceP();
    void paymentPartnerDisplay();
};

#endif