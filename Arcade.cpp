////////////////////////////////////////////////////////////////////
//  Written by: Wenxuan Dai
//  arcade class & methods for shopping arcade
////////////////////////////////////////////////////////////////////
#include "Arcade.h"

// more details in stage 4 not using this in stage 3
CArcade::CArcade(void)
{
}

CArcade::~CArcade(void)
{
}
// add procucts to shopping cart
void CArcade::addProducts(std::string name, int price, int inv)
{
	CProducts newProduct = CProducts(name, price, inv);
	vecProducts.push_back(&newProduct);
}
// remove products in shopping cart
void CArcade::removeProducts(std::string name)
{
	for (int i = 0; i < vecProducts.size(); i++)
	{
		if (vecProducts[i]->getProductName() == name)
		{
			vecProducts.erase(vecProducts.begin() + i);
		}
	}
}

void CArcade::modifyPrice(std::string name, int price)
{
	for (int i = 0; i < vecProducts.size(); i++)
	{
		if (vecProducts[i]->getProductName() == name)
		{
			vecProducts[i]->setProductPrice(price);
		}
	}
}
void CArcade::modifyQuantity(std::string name, int quantity)
{
	for (int i = 0; i < vecProducts.size(); i++)
	{
		if (vecProducts[i]->getProductName() == name)
		{
			vecProducts[i]->setProductInventory(quantity);
		}
	}

}
void CArcade::displayAllProducts()
{
	for (int i = 0; i < vecProducts.size(); i++)
	{
		std::cout << vecProducts[i]->getProductName() << std::endl;
		std::cout << "Price: " << vecProducts[i]->getProductPrice() << std::endl;
		std::cout << "Quantity available: " << vecProducts[i]->getProductInventory() << std::endl;
	}
}
void CArcade::addToShoppingCart(std::string name, int quantity)
{
	for (int i = 0; i < vecProducts.size(); i++)
	{
		if (vecProducts[i]->getProductName() == name)
		{
			vecShooppingCart.push_back(vecProducts[i]);
			vecShooppingCart[vecShooppingCart.size() - 1]->setProductInventory(quantity);
		}
	}
}
void CArcade::removeFromShoppingCart(std::string name)
{
	for (int i = 0; i < vecShooppingCart.size(); i++)
	{
		if (vecShooppingCart[i]->getProductName() == name)
		{
			vecShooppingCart.erase(vecShooppingCart.begin() + i);
		}
	}
}
int CArcade::calculateTotalPrice()
{
	int iTotalPrice = 0;
	for (int i = 0; i < vecShooppingCart.size(); i++)
	{
		iTotalPrice += vecShooppingCart[i]->getProductPrice();
	}
	return iTotalPrice;
}
