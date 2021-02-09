////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#ifndef PaymentInterface_h__
#define PaymentInterface_h__
#include "Headers.h"
#include "PaymentInterfaceC.h"
#include "PaymentInterfaceP.h"
#include "BookingManager.h"
#include "UserGuest.h"
#include <sstream>
#include "Booking.h"
using namespace std;
class CPaymentInterfaceC;
class CPaymentInterfaceP;
class CPaymentInterface
{
private:
    string sBookingID;
    string sInput;
    bool integerCheck(string);
    int iHotelID = 1223;

public:
    CPaymentInterface();
    ~CPaymentInterface();
    void paymentDisplay();
    void addPendingPayment(int, int, int);
};

#endif