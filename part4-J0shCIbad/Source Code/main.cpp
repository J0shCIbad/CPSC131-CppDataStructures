#include "GroceryItem.hpp"
#include "GroceryItemDatabase.hpp"
#include <iostream>
#include <map>
#include <string>

#include "OnlineOrder.hpp"

//This file does not need to be altered, and will be replaced with the original
//version while grading.
int main()
{
  OnlineOrder currentShoppingCart("ShoppingCart.dat"), storeInventory("StoreStock.dat");
  std::cout << currentShoppingCart.checkOut(storeInventory);
  //Save both the shopping cart and the store inventory for assessment
  storeInventory.saveInventory("_currentStoreInventory.dat");
  currentShoppingCart.saveInventory("_currentShoppingCart.dat");
  return 0;
}
