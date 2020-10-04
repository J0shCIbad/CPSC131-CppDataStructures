/**
*	Author: Josh Ibad
*	Date:	09-Feb-2020	
*	Class: 	CPSC131-05
*	Assignment:		Part 0 - GroceryItem
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "GroceryItem.hpp"

int main(int argc, char** argv){
	char c;
	std::vector<GroceryItem*> vec;
	while(c = std::cin.get() != std::char_traits<char>::eof()){
		std::cin.putback(c);
		GroceryItem* gi = new GroceryItem();
		std::cin >> *gi;
		vec.push_back(gi);
	}
	
	std::cout << (*vec[0] > *vec[1]);
	
	std::vector<GroceryItem*>::reverse_iterator ir = vec.rbegin()+1;
	for(; ir != vec.rend(); ir++){
		std::cout << **ir << std::endl;
		delete *ir;
	}
	return 0;
}
