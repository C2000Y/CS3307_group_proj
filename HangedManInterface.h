#ifndef HangedManInterface_H__
#define HangedManInterface_H__
#include "Headers.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
class CHangedManInterface
{
private:
    vector<string> words = {"when", "Federal", "Reserve", "start", "purchase", "corporate", "stock", "that", "volatile", "instrument", "value", "general", "fluctuate", "volatility", "exposure", "market", "maintain", "stability", "economy", "consequence", "disastrous", "Normal", "liquidity"};

public:
    void HangedManGameDisplay();
    CHangedManInterface();
    ~CHangedManInterface();
};
#endif