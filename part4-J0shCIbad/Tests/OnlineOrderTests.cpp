#include <cmath>      // abs()
#include <cstdlib>    // exit()
#include <exception>
#include <iomanip>    // setprecision()
#include <iostream>   // boolalpha(), showpoint(), fixed()
#include <sstream>
#include <string>     // to_string()
#include <cctype>

#include "CheckResults.hpp"
#include "GroceryItemDatabase.hpp"
#include "OnlineOrder.hpp"

namespace  // anonymous
{
  class OnlineOrderRegressionTest
  {
    public:
      OnlineOrderRegressionTest();

    private:
      void tests();

      Regression::CheckResults affirm;
  } run_onlineOrdering_tests;




  void OnlineOrderRegressionTest::tests()
  {
    OnlineOrder teststore("StoreStock.dat"), testcart("ShoppingCart.dat");
    std::string receipt = testcart.checkOut(teststore);
    affirm.is_equal( "Inventory default args - Expected size", static_cast<unsigned int>(9), testcart.size() );


    affirm.is_equal("Inventory file - Expected entry 00027018302933", 78, testcart.find("00027018302933")->second);

    affirm.is_not_equal("Inventory - item not in store", receipt.size(), receipt.find("00000000004459 is currently unavailable in this store."));
    affirm.is_equal("Inventory - item not in store false positive", receipt.rfind("00000000004459 is currently unavailable in this store."), receipt.find("00000000004459 is currently unavailable in this store."));


    affirm.is_not_equal("Inventory - item not in store",
      receipt.size(),
      receipt.find("00000000004459 is currently unavailable in this store."));
    affirm.is_equal("Inventory - item not in store false positive",
      receipt.rfind("00000000004459 is currently unavailable in this store."),
      receipt.find("00000000004459 is currently unavailable in this store."));

    affirm.is_not_equal("Inventory - Invalid UPC",
      receipt.size(),
      receipt.find("Invalid UPC"));
    affirm.is_equal("Inventory - item not in store false positive",
      receipt.rfind("Invalid UPC"),
      receipt.find("Invalid UPC"));

    std::string tempstring = "10               52.40\n10 units of item 00027018302933 were available and sold, further items could not be served.";
    affirm.is_not_equal("Inventory - Invalid UPC",
      receipt.size(),
      receipt.find(tempstring));
    affirm.is_equal("Inventory - item not in store false positive",
      receipt.rfind(tempstring),
      receipt.find(tempstring));

      OnlineOrder storeupdate1("ShoppingCart.dat"), storeupdate2("ShoppingCart.dat");
      receipt = storeupdate1.checkOut(storeupdate2);
    affirm.is_equal("Inventory - Store updates quantities",
      0,
      storeupdate2.find("00027018302933")->second);


  }



  OnlineOrderRegressionTest::OnlineOrderRegressionTest()
  {
    std::clog << std::boolalpha << std::showpoint << std::fixed << std::setprecision( 2 );


    try
    {
      std::clog << "\nOnline Ordering System Regression Test:\n";
      tests();

      std::clog << affirm << '\n';
    }
    catch( const std::exception & ex )
    {
      std::clog << "FAILURE:  Regression test for \"Online Ordering System\" failed with an unhandled exception. \n\n\n"
                << ex.what() << std::endl;

      // Reminder:  Objects with automatic storage are not destroyed by calling std::exit().  In this case, this is okay.
      // std::exit( -__LINE__ ); // uncomment to terminate program with test failures
    }
  }
} // namespace
