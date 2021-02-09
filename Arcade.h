////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  arcade class & methods for shopping arcade
////////////////////////////////////////////////////////////////////
#ifndef Arcade_h__
#define Arcade_h__
#include "Headers.h"
#include "Products.h"

class CProducts;
class CArcade
{
public:
	CArcade(void);
	~CArcade(void);

private:
	std::vector<CProducts *> vecProducts;
	std::vector<CProducts *> vecShooppingCart;

public:
	void addProducts(std::string, int, int);
	void removeProducts(std::string);
	void modifyPrice(std::string, int);
	void modifyQuantity(std::string, int);

	void displayAllProducts();

	void addToShoppingCart(std::string, int);
	void removeFromShoppingCart(std::string);
	int calculateTotalPrice();

};
#endif
