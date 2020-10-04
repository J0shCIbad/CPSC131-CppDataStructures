/**
 *  Name:   Josh Ibad
 *  CWID:   888880036
 *  Assigment:  Part 3
 *  Professor:  Professor May
 *  Class:  CPSC131
 */

#include <cstddef>      // size_t
#include <fstream>
#include <string>
#include <utility>      // move()

#include "GroceryItemDatabase.hpp"



// Return a reference to the one and only instance of the database
GroceryItemDatabase & GroceryItemDatabase::instance( const std::string & filename )
{
  static GroceryItemDatabase theInstance( filename );
  return theInstance;
}




// Construction
GroceryItemDatabase::GroceryItemDatabase( const std::string & filename )
{
  std::ifstream fin( filename, std::ios::binary );


  ///////////////////////// TO-DO //////////////////////////////
    /// The file contains one record of data on each line of text.  See Grocery_UPC_Database_Sample.dat.  A record has 4 pieces of
    /// data delimited with a comma.  (This exactly matches how Grocery Items are read) 
    ///
    ///       Field            Type            Notes
    ///  1.   UPC Code         String          Unique identifier (primary key), always enclosed in double quotes
    ///  2.   Brand Name       String          May contain spaces, always enclosed in double quotes
    ///  3.   Product Name     String          May contain spaces, always enclosed in double quotes
    ///  4.   Price            Floating Point  In dollars
    ///
    ///  Example:
    ///    "00024600017008",   "Morton",         "Morton Kosher Salt Coarse",                                    15.17
    ///    "00033674100066",   "Nature's Way",   "Nature's Way Forskohlii - 60 Ct",                              6.11
    ///    "00041520893307",   "Smart Living",   "Smart Living 10.5\" X 8\" 3 Subject Notebook College Ruled",   18.98
    ///
    ///  Note: double quotes within the string are escaped with the backslash character
    ///  mySol
    GroceryItem tempGroceryItem;
    while( fin.peek() != -1){
        fin >> tempGroceryItem;
        _data.push_back(tempGroceryItem);
    }
  /////////////////////// END-TO-DO ////////////////////////////

  // Note:  The file is intentionally not explicitly closed.  The file is closed when fin goes out of scope - for whatever
  //        reason.  More precisely, the object named "fin" is destroyed when it goes out of scope and the file is closed in the
  //        destructor. See RAII
}



GroceryItem * GroceryItemDatabase::find( const std::string & upc )
{
  ///////////////////////// TO-DO //////////////////////////////
    /// Walk the memory resident container named "_data" looking for a grocery item with a matching UPC.  If found, return a pointer
    /// to that grocery item.  Otherwise return a null pointer.
    for(int i=0; i<_data.size(); i++){
        if( (_data[i]).upcCode() == upc )
            return &(_data[i]);
    }
    return nullptr;
  /////////////////////// END-TO-DO ////////////////////////////
}


std::size_t GroceryItemDatabase::size() const
{
  // Returns the number of grocery items in the grocery item database.
  ///////////////////////// TO-DO //////////////////////////////
    /// Delegate the actual work of determining how many items are stored to the underlying container named "data"
    return _data.size();
  /////////////////////// END-TO-DO ////////////////////////////
}
