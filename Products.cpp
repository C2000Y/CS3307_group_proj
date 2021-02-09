#include "Products.h"
#include "Headers.h"

CProducts::CProducts(void)
{
}
CProducts::~CProducts(void)
{
}

CProducts::CProducts(std::string name, int price, int inv)
{
	sProductName = name;
	iProductPrice = price;
	iProductInventory = inv;
}
void CProducts::setProductName(std::string name)
{
	sProductName = name;
}
void CProducts::setProductPrice(int price)
{
	iProductPrice = price;
}
void CProducts::setProductInventory(int inv)
{
	iProductInventory = inv;
}
std::string CProducts::getProductName()
{
	return sProductName;
}
int CProducts::getProductPrice()
{
	return iProductPrice;
}
int CProducts::getProductInventory()
{
	return iProductInventory;
}