////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#ifndef PaymentManager_h__
#define PaymentManager_h__

#include "Headers.h"
#include "Payment.h"
#include <sstream>
#include <fstream>
using namespace std;
class CPayment;
class CPaymentManager
{
private:
    map<int, CPayment *> mapRoomNumAndPaymentInfo;
    vector<string> vecPaymentString;
    //print status info accoring to status #
    void statusFormatingAndDisplay(int);
    vector<string> vecCCPendingPayment;
    vector<string> vecDCPendingPayment;
    vector<string> vecGCPendingPayment;
    void displayCreditCardPendingPayment(int, string);
    void displayDebitCardPendingPayment(int, string);
    void displayGiftCardPendingPayment(int, string);

public:
    CPaymentManager(int); //hotel name

    ~CPaymentManager();

    void displayPaymentInfo(int); //display room payment info
    bool checkRoomExistance(int);
    //credit card info and bill(s) that customers want to pay
    void updateCreditCardPaymentInfo(int, string, string, string, string, string, string);
    //debit card info and bill(s) that customers want to pay
    void updateDebitCardPaymentInfo(int, string, string, string, string, string, string);
    //gift card info and bill(s) that customers want to pay
    void updateGiftCardPaymentInfo(int, string, string, string);
    //update pending amount if status is 0(paid)
    void updatePaymentStatus(int, string, int, int); //hotelname, room#,payment type and status type
    void displayAllPendingPayment(int, string);
    void updatePaymentInfoFile(int, int);
    //test
    void print_map();
    void updateRoomServicePrice(int, int);//room# and price
    void updateRoomPrice(int,int);
    void updateExtraServicePrice(int,int);
};

#endif