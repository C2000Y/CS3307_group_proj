#ifndef Products_h__
#define Products_h__
#include "Headers.h"
class CProducts
{
public:
	CProducts(void);
	~CProducts(void);
	CProducts(std::string, int, int);

private:
	std::string sProductName;
	int iProductPrice;
	int iProductInventory;

public:
	void setProductName(std::string);
	void setProductPrice(int);
	void setProductInventory(int);
	std::string getProductName();
	int getProductPrice();
	int getProductInventory();
};
#endif
