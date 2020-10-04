/**
*	Author: Josh Ibad
*	Date:	20-APR-2020	
*	Class: 	CPSC131-05
*	Assignment:		Part 4 - Associative Containers
*/
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include "GroceryItemDatabase.hpp"
#include "OnlineOrder.hpp"

//Providing a filename will use that file to initialize data
OnlineOrder::OnlineOrder(std::string filename){
	std::ifstream fin;
	fin.open(filename);
	
	std::string upcTemp;
	int countTemp;
	while( fin.peek() != -1){
		try{
			fin >> upcTemp >> countTemp;
			_data.insert( std::pair<std::string, int>(upcTemp, countTemp) );
		}catch(std::exception){
			break;
		}
	}
	
	fin.close();
}

//Symmetrical save operation that is used with the file based initializeInventory overload
void OnlineOrder::saveInventory(std::string filename){
	std::ofstream fout;
	fout.open(filename);
	
	for(auto it = _data.begin(); it!= _data.end(); it++){
		fout << (it->first) << " " << (it->second) << std::endl;
	}
	
	fout.close();
}

//Returns the receipt for this cart against an argument store
std::string OnlineOrder::checkOut(OnlineOrder & storeInventory){
	GroceryItemDatabase & storeDB = GroceryItemDatabase::instance();
	std::stringstream receipt;
	double total;
	
	for(auto it = _data.begin(); it!= _data.end(); it++){
		try{
			auto it2 = storeInventory.find(it->first);
			if( it2 == storeInventory.end() ){
				receipt << "Invalid UPC\n";
			}else if ( (it2->second) > (it->second) ){
				GroceryItem item = *(storeDB.find( it->first ));
				receipt << item << "\n\t\t\t\t" << (it->second) << "\t\t" 
					<< ((it->second)*item.price()) << "\n" ;
				total += ((it->second)*item.price());
				(it2->second) -= (it->second);
				(it->second) = 0;
			}else if ( (it2->second) > 0 ){
				GroceryItem item = *(storeDB.find( it->first ));
				receipt << item << "\n\t\t\t\t" << (it2->second) << "\t\t" 
					<< ((it2->second)*item.price()) << "\n";
				receipt << (it2->second) << " units of item " << (it2->first) <<
					" were avaialbe and sold, further items could not be served.\n";
				total += ((it2->second)*item.price());
				(it->second) -= (it2->second);
				(it2->second) = 0;
			}else{
				receipt << "Item UPC: " << (it->first) << 
					" is currently unavailable in this store.\n";
			}
		}catch(std::exception){}
	}
	receipt << "Total cost: $" << total << "\n";
	return receipt.str();
	//pseudocode
    //declarations
		//(for)iterate through cart _data (range based loop, structured bindings, reference)
		//if key not found in store: Invalid upc
    //else: find grocery item where upc == key, then
    //if storeQnt >= cartQuant: full checkout
    //else: if storeQnt > 0: partial sale
    //else: no stock available, no sale
    //post-loop: total payment due
}

//Returns a map iterator, which behaves like a pointer to an std::pair
OnlineOrder::StockMap::iterator OnlineOrder::find(std::string searchedUPC){
	for(auto it = _data.begin(); it!= _data.end(); it++){
		if( (it -> first) == searchedUPC){
			return it;
		}
	}
	return _data.end();
}

//Remove a specified quantity of items of a given UPC
void OnlineOrder::remove(std::string key, unsigned int amount){
	try{
		_data.at(key) -= amount;
		//What if too many removed, or zero left?
	}catch(std::out_of_range){
		//
	}
}
