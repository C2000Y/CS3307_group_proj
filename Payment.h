////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//
////////////////////////////////////////////////////////////////////
#ifndef Payment_h__
#define Payment_h__

#include "Headers.h"
#include <sstream>
using namespace std;
class CPayment
{
private:
    int iRoomPayment = 0;
    int iRoomServicesPayment = 0;
    int iExtraServicesPayment = 0;
    /*status
    0 is paid
    1 is pending
    2 is not paid*/
    int iRoomStatus = 0;
    int iRoomServicesStatus = 0;
    int iExtraServicesStatus = 0;

public:
    CPayment(int, int, int, int, int, int);
    ~CPayment();
    int getRoomPayment();
    int getRoomServicesPayment();
    int getExtraServicesPayment();
    void setRoomPayment(int);
    void setRoomServicesPayment(int);
    void setExtraServicesPayment(int);
    int getRoomStatus();
    int getRoomServicesStatus();
    int getExtraServicesStatus();
    void setRoomStatus(int);
    void setRoomServicesStatus(int);
    void setExtraServicesStatus(int);
    string paymentFormatting();
};

#endif