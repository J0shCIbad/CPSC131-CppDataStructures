#include <cmath>      // abs()
#include <cstdlib>    // exit()
#include <exception>
#include <iomanip>    // setprecision()
#include <iostream>   // boolalpha(), showpoint(), fixed()
#include <sstream>
#include <string>     // to_string()

#include "CheckResults.hpp"
#include "GroceryItemDatabase.hpp"

namespace  // anonymous
{
  class GroceryItemDatabaseRegressionTest
  {
    public:
      GroceryItemDatabaseRegressionTest();

    private:
      void tests();

      Regression::CheckResults affirm;
  } run_groceryItemDatabase_tests;




  void GroceryItemDatabaseRegressionTest::tests()
  {
    GroceryItemDatabase & db = GroceryItemDatabase::instance();
    affirm.is_equal( "Database construction - Expected size", 104361U, db.size() );

    if( auto item = db.find( "00312843555419" ); item == nullptr )
    {
      affirm.is_equal( "Database query - existing item should have been found, but it wasn't", "non-null pointer", "nullptr" );
    }
    else
    {
      affirm.is_equal( "Database query - existing item located",
                        GroceryItem( "Bayer Asprin Plus Extra Strength 500mg - 50 Ct",
                                    "Bayer",
                                    "00312843555419",
                                    19.41 ),
                        *item );
    }

    {
      auto item = db.find( "--------------" );

      #if !defined(__GNUC__) ||  __GNUC__>= 9
        affirm.is_equal( "Database query - non-existing item found when it shouldn't have been", nullptr, item );
      #else
        // Error in g++ version 8, fixed in 9
        //   std::cout << nullptr << '\n';
        //
        // workaround:
        //   Printing a nullptr was added in C++17 but gcc wasn't compliant until version 9. Tuffix 2019 Edition r2 has both gcc
        //   version 8 and 9, but many (most? all?) students still have the default set to version 8.  Once version 9 or above is
        //   the default version in Tuffix this workaround can be removed.
        decltype(item) i = nullptr;
        affirm.is_equal( "Database query - non-existing item found when it shouldn't have been", i, item );
      #endif
    }
  }



  GroceryItemDatabaseRegressionTest::GroceryItemDatabaseRegressionTest()
  {
    std::clog << std::boolalpha << std::showpoint << std::fixed << std::setprecision( 2 );


    try
    {
      std::clog << "\nGrocery Item Database Regression Test:\n";
      tests();

      std::clog << affirm << '\n';
    }
    catch( const std::exception & ex )
    {
      std::clog << "FAILURE:  Regression test for \"class GroceryItem\" failed with an unhandled exception. \n\n\n"
                << ex.what() << std::endl;

      // Reminder:  Objects with automatic storage are not destroyed by calling std::exit().  In this case, this is okay.
      // std::exit( -__LINE__ ); // uncomment to terminate program with test failures
    }
  }
} // namespace
