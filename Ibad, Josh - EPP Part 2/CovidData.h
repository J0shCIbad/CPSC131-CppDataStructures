/**
 *	Name: Josh Ibad
 *	CWID: 888880036
 *	Date: EPP Part 2 - March 26, 2020: 10:00 AM, Mid Spring
 *  
 * 	MAP STRUCTURE (std::map) used.
 *
 * 	CovidData reads data from a file and stores the minimum number of cases per country in a 
 * 	map structure with the country name as the key. More documentation below.
 */
 
#include <fstream>
#include <string>
#include <map>
using namespace std;

 /**
  *	A class for reading data on the number of cases in different countryies of the ongoing COVID-19 pandemic
  * and obtaining the minimum number of cases (as is required by the prompt). 
  * A standard library map is used to store country and mininimum number of cases tuples.
  *
  * MAP STRUCTURE (std::map) USED
  */
class CovidData{
	private:
		map<string, int> minCases; //a map containing the minimum number of cases (value) in each country (key)
		
	public:
		/**
		 * A default constructor for the CovidData class which does not do much
		 * since no explicit dynamic memory is used (no new's).
		 */
		CovidData()=default;
		
		/**
		 * Reads data from inputted filename and puts the minimum number of cases from
		 * each country into the minCases map.
		 * @param filename - The name of the file to read from.
		 * @return Number of lines read from file. 0 if none read.
		 */
		int readData(string filename){
			int counter = 0; //counter for number of lines read;
			string tempCountryName; //will store country name per iteration (or line)
			int tempNumCases; //will store number of cases per iteration (or line)
			
			ifstream in;
			in.open(filename); //opens an file input stream with given filename
			while(in >> tempCountryName >> tempNumCases >> tempNumCases){ //inputs data from line into respective variables (ignores first int [day number])
				minCases.insert( std::pair<string, int>(tempCountryName, tempNumCases) ); //inserts data if no data for country exists
				if( minCases[tempCountryName] > tempNumCases){ //if the value to be input is smaller than that which is already stored, store smaller value
					minCases[tempCountryName] = tempNumCases;
				}
				counter++;
			}
			return counter;
		}
		
		/**
		 * Returns the minimum number of cases from the input country name as stored
		 * in the minCases map.
		 * @param country - Name of country desired
		 * @return Minimum number of cases in the country inputted. -1 if country is not in dataset.
		 */
		int getMinCases(string country){
			try{ //Tries to access country's number of cases and return it.
				return minCases.at(country); 
			}catch(out_of_range){ //If no such country in data, out_of_range exception will be thrown and caught leading to this catch statement.
				return -1;
			}
		}
 };