#pragma once
#include <cstddef>   // size_t
#include <string>
#include <map>

#include "GroceryItem.hpp"


// Singleton Design Pattern
class GroceryItemDatabase
{
  public:
    // Get a reference to the one and only instance of the database
    static GroceryItemDatabase & instance( const std::string & filename = "Grocery_UPC_Database_Sample.dat");

    // Locate and return a reference to a particular record
    GroceryItem * find( const std::string & upc );                              // Returns a pointer to the item in the database if
                                                                                // found, nullptr otherwise
    // Queries
    std::size_t size() const;                                                   // Returns the number of items in the database
    
  private:
    GroceryItemDatabase            ( const std::string & filename );

    GroceryItemDatabase            ( const GroceryItemDatabase & ) = delete;    // intentionally prohibit making copies
    GroceryItemDatabase & operator=( const GroceryItemDatabase & ) = delete;    // intentionally prohibit copy assignments

    // "Upgrade" from std::vector
    std::map<std::string,GroceryItem> _data;

    //Allows an initializing inventory to iterate through the container
    //Does not alter database in any capacity
    friend class OnlineShoppingInventory;
};