/**
 *  Name:   Josh Ibad
 *  CWID:   888880036
 *  Assigment:  Part 4
 *  Professor:  Professor May
 *  Class:  CPSC131
 */
#include <map>
#include <cstddef>      // size_t
#include <fstream>
#include <string>
#include <utility>      // move()

#include "GroceryItemDatabase.hpp"



// Return a reference to the one and only instance of the database
GroceryItemDatabase & GroceryItemDatabase::instance( const std::string & filename ){
	static GroceryItemDatabase theInstance( filename );
	return theInstance;
}

// Construction
GroceryItemDatabase::GroceryItemDatabase( const std::string & filename ){
	std::ifstream fin( filename, std::ios::binary );


	GroceryItem tempGroceryItem;
    while( fin.peek() != -1 ){
	try{
        	fin >> tempGroceryItem;
        	_data.insert( std::pair<std::string, GroceryItem>(tempGroceryItem.upcCode(), tempGroceryItem) );
	}catch(std::exception){
		break;
	}
    }
}

GroceryItem * GroceryItemDatabase::find( const std::string & upc ){
	try{
		return &(_data.at(upc));
	}catch(std::out_of_range){
	}
	return nullptr;
}

std::size_t GroceryItemDatabase::size() const{
	return _data.size();
}
