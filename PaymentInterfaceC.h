////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#ifndef PaymentInterfaceC_h__
#define PaymentInterfaceC_h__
#include "Headers.h"
#include "PaymentManager.h"
#include <sstream>
using namespace std;

class CPaymentInterfaceC
{
private:
    vector<string> vecHotels;

    string sRoomNumInput;

    int iHotelID=1223;
    string sPaymentInfoInput;
    string sPaymentSelectionInput;
    string sPaymentTypeInput;
    //credit card
    vector<string> vecCreditCardInfo = {"First name, Last Name", "xxxx xxxx xxxx xxxx", "Month/Year", "xxx"};
    string sCreditCardInput;
    string sCreditCardName;
    string sCreditCardFirstName;
    string sCreditCardLastName;
    string sCreditCardNumber;
    string sCreditCardExpireDate;
    string sCreditCardSecurityCode;
    //debit card
    vector<string> vecDebitCardInfo = {"First name, Last Name", "xxxx xxxx xxxx xxxx", "Month/Year", "xxx"};
    string sDebitCardInput;
    string sDebitCardFirstName;
    string sDebitCardLastName;
    string sDebitCardName;
    string sDebitCardNumber;
    string sDebitCardExpireDate;
    string sDebitCardSecurityCode;
    //gift card
    string sGiftCardNumberInput = "xxxxxxxxxx";
    string sGiftCardInput;


    bool integerCheck(string);

public:
    CPaymentInterfaceC();
    ~CPaymentInterfaceC();
    void paymentDisplay();
};

#endif