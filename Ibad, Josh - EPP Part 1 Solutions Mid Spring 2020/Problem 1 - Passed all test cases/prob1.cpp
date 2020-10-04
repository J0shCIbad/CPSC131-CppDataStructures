/**
 * @author	Josh Ibad
 *	CWID:	888880036
 * 	Date:	EPP Mid-Spring 2020, 10 AM
 */
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
bool checkAnswer(const string &nameOfTest, bool received, bool expected);

// Implement printString here
void printString(const std::string & str){
	for(int i=0; i<str.size(); i++){
		std::cout << str[i] << " ";
	}
	std::cout << std::endl;
}


// Implement testString here
bool testString(const std::string & str){
	if(str.size() <= 1) {return true;}
	
	for(int i=1; i<str.size(); i++){
		if(str[0] != str[i]){
			return false;
		}
	}
	return true;
}



// EDIT CODE BELOW *ONLY* FOR TESTING (ANY CODE BELOW WILL BE OVER-WRITTEN DURING GRADING WITH DIFFERENT TESTS)

int main() {
  cout << "Test if all the characters in the string are the same" << endl;
  {
    string s = "www";
    cout << "Contents of array : ";
    printString(s);
	  checkAnswer(s, testString(s), true);
  }
  {
    string s = "world";
    cout << "Contents of array : ";
    printString(s);
	  checkAnswer(s, testString(s), false);
  }
  {
    string s = "zzzzz";
    cout << "Contents of array : ";
    printString(s);
	  checkAnswer(s, testString(s), true);
  }
  {
    string s = "a";
    cout << "Contents of array : ";
    printString(s);
	  checkAnswer(s, testString(s), true);
  }
  //	system("pause"); // comment/uncomment if needed

  return 0;
}

bool checkAnswer(const string &nameOfTest, bool received, bool expected) {
    if (received == expected) {
        cout << "PASSED " << nameOfTest << ": expected and received " << received << endl;
        return true;
    }
    cout << "FAILED " << nameOfTest << ": expected " << expected << " but received " << received << endl;
    return false;
}
