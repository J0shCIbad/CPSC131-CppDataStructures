/**
*	Author: Josh Ibad
*	Date:	20-APR-2020	
*	Class: 	CPSC131-05
*	Assignment:		Part 4 - Associative Containers
*/
#pragma once

#include <map>
#include <string>
#include "GroceryItemDatabase.hpp"


class OnlineOrder
{
  public:
    //Establishes easily used alias for this multiple templated type definition
    using StockMap = std::map<std::string,int>;

    //Providing a filename will use that file to initialize data
    OnlineOrder(std::string filename);

    //Returns the receipt for this cart against an argument store
    std::string checkOut(OnlineOrder & storeInventory);

    //pseudocode
    //declarations
    //(for)iterate through cart _data (range based loop, structured bindings, reference)
    //if key not found in store: Invalid upc
    //else: find grocery item where upc == key, then
    //if storeQnt >= cartQuant: full checkout
    //else: if storeQnt > 0: partial sale
    //else: no stock available, no sale
    //post-loop: total payment due

    //Symmetrical save operation that is used with the file based initializeInventory overload
    void saveInventory(std::string filename);

    //Returns a map iterator, which behaves like a pointer to an std::pair
    StockMap::iterator find(std::string searchedUPC);

    //Used to detect missed values
    StockMap::const_iterator end() { return _data.end(); }

    //Allows public access to size member of data
    std::size_t size() { return _data.size(); }

    //Remove a specified quantity of items of a given UPC
    void remove(std::string key, unsigned int amount);


  private:
    //The data portion of the class
    StockMap _data;

	  //Since we only have to worry about loading inventory/carts from files, we won't be needing our default constructor
    OnlineOrder() = delete;
};
