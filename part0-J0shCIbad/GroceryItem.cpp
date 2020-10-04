/**
*	Author: Josh Ibad
*	Date:	09-Feb-2020	
*	Class: 	CPSC131-05
*	Assignment:		Part 0 - GroceryItem
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <vector>

#include "GroceryItem.hpp"

// Constructors
    GroceryItem::GroceryItem( const std::string & productName,
                 const std::string & brandName,
                 const std::string & upcCode,
                 double              price)
                 : _productName(productName),
                 _brandName(brandName),
                 _upcCode(upcCode),
                 _price(price) {}

    // Queries
    std::string GroceryItem::upcCode     () const{
		return GroceryItem::_upcCode;
	}
    std::string GroceryItem::brandName   () const{
		return GroceryItem::_brandName;
	}
    std::string GroceryItem::productName () const{
		return GroceryItem::_productName;
	}
    double      GroceryItem::price       () const{
		return GroceryItem::_price;
	}

    // Mutators
    //Double check string copying
    void GroceryItem::upcCode      ( const std::string & upcCode     ){
    	GroceryItem::_upcCode = upcCode;
	}
    void GroceryItem::brandName    ( const std::string & brandName   ){
    	GroceryItem::_brandName = brandName;
	}
    void GroceryItem::productName  ( const std::string & productName ){
    	GroceryItem::_productName = productName;
	}
    void GroceryItem::price        ( double              price       ){
    	GroceryItem::_price = price;
    }
    
    //Insertion and extraction operators
    std::ostream & operator<<(std::ostream &out, const GroceryItem &obj){
    	std::string sep = ", ";
    	std::string temp = "\"" + obj.upcCode() + "\"" + sep; 
    	out.write(temp.c_str(), temp.length());
    	temp = "\"" + obj.brandName() + "\"" + sep; 
    	out.write(temp.c_str(), temp.length());
    	temp = "\"" + obj.productName() + "\"" + sep; 
    	out.write(temp.c_str(), temp.length());
    	out << obj.price();
    	return out;
	}
	std::istream & operator>>(std::istream &in, GroceryItem &obj){
		std::string str, temp, temp2;
		std::getline(in, str);
		std::stringstream stream;
		stream << str;
		
		if(stream.eof()) {return in;}
		do{
			stream >> temp;
			temp2 += temp + " ";
		}while(temp2[temp2.length()-2] != ',');
		obj.upcCode( temp2.substr(1, temp2.length()-4) );
		temp2 = "";
		
		if(stream.eof()) {return in;}
		do{
			stream >> temp;
			temp2 += temp + " ";
		}while(temp2[temp2.length()-2] != ',');
		obj.brandName( temp2.substr(1, temp2.length()-4) );
		temp2 = "";
		
		if(stream.eof()) {return in;}
		do{
			stream >> temp;
			temp2 += temp + " ";
		}while(temp2[temp2.length()-2] != ',');
		obj.productName( temp2.substr(1, temp2.length()-4) );
		temp2 = "";
		
		if(stream.eof()) {return in;}
		double db;
		stream >> db;
		obj.price(db);
		return in;
	}
	
	//Relational operators
	bool operator<(const GroceryItem &lhs, const GroceryItem &rhs)	{
		if(lhs.upcCode() < rhs.upcCode())
			return true;	
		else if(lhs.upcCode() != rhs.upcCode())
			return false;
		else{
			if(lhs.brandName() < rhs.brandName())
				return true;	
			else if(lhs.brandName() != rhs.brandName())
				return false;
			else{
				if(lhs.productName() < rhs.productName())
					return true;	
				else if(lhs.productName() != rhs.productName())
					return false;
				else{
					return lhs.price() < rhs.price();
				}
			}
		}
	}
	bool operator==(const GroceryItem &lhs, const GroceryItem &rhs){
		return ( lhs.upcCode() == rhs.upcCode() ) &&
			( lhs.brandName() == rhs.brandName() ) &&
			( lhs.productName() == rhs.productName() ) &&
			( lhs.price()-rhs.price() ) < 1E-4;
	}
	bool operator>(const GroceryItem &lhs, const GroceryItem &rhs){
		return !(lhs==rhs || lhs<rhs);	
	}
	bool operator>=(const GroceryItem &lhs, const GroceryItem &rhs){
		return !(lhs<rhs);	
	}
	bool operator<=(const GroceryItem &lhs, const GroceryItem &rhs){
		return (lhs==rhs || lhs<rhs);	
	}
	bool operator!=(const GroceryItem &lhs, const GroceryItem &rhs){
		return !(lhs==rhs);	
	}     
