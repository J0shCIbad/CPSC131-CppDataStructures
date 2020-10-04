#include <cmath>       // abs()
#include <cstdlib>     // exit()
#include <exception>
#include <iomanip>     // setprecision()
#include <iostream>    // boolalpha(), showpoint(), fixed()
#include <sstream>

#include "CheckResults.hpp"
#include "GroceryItem.hpp"

namespace  // anonymous
{
  constexpr auto EPSILON = 1E-4;

  class GroceryItemRegressionTest
  {
    public:
      GroceryItemRegressionTest();
    
    private:
      void construction();
      void io          ();
      void comparison  ();
  
      Regression::CheckResults affirm;
  } run_groceryItem_tests;




  void GroceryItemRegressionTest::construction()
  {
    GroceryItem g1,
                g2( "product name"                               ),
                g3( "product name",  "brand name"                ),
                g4( "product name",  "brand name", "UPC"         ),
                g5( "product name",  "brand name", "UPC", 123.79 );

    affirm.is_equal( "Default price", g1.price(), 0.0 );

    g1.productName( "1-3-5" );
    affirm.is_equal( "Symmetrical product name mutator/query", "1-3-5", g1.productName() );

    g1.brandName( "21-23-25" );
    affirm.is_equal( "Symmetrical brand name mutator/query", "21-23-25", g1.brandName() );

    g1.upcCode( "11-13-15" );
    affirm.is_equal( "Symmetrical UPC code mutator/query", "11-13-15", g1.upcCode() );

    g1.price( 31.11 );
    affirm.is_equal( "Symmetrical price mutator/query", 31.11, g1.price() );

    affirm.is_true
    ( "Grocery Item construction with arguments",
           g2.productName() == "product name"
        && g3.productName() == "product name" && g3.brandName() == "brand name"
        && g4.productName() == "product name" && g4.brandName() == "brand name" && g4.upcCode() == "UPC"
        && g5.productName() == "product name" && g5.brandName() == "brand name" && g5.upcCode() == "UPC" && std::abs(g5.price() - 123.79) < EPSILON 
     );

    GroceryItem g6( g5 );
    affirm.is_true
    ("Copy construction",
          g6.productName() ==  g5.productName()
       && g6.brandName()   ==  g5.brandName()
       && g6.upcCode()     ==  g5.upcCode()
       && std::abs(g6.price() - g5.price()) < EPSILON
    );

    g6 = g4;
    affirm.is_true
    ("Copy construction",
          g6.productName() ==  g4.productName()
       && g6.brandName()   ==  g4.brandName()
       && g6.upcCode()     ==  g4.upcCode()
       && std::abs(g6.price() - g4.price()) < EPSILON
    );
  }



  void GroceryItemRegressionTest::io()
  {
    GroceryItem g1,
                g2( "product name" ),
                g3( "product name", "brand name" ),
                g4( "product name", "brand name", "UPC" ),
                g5( "product name", "brand name", "UPC", 123.79 );

    std::stringstream stream;

    stream << g1 << '\n'
           << g2 << '\n'
           << g3 << '\n'
           << g4 << '\n'
           << g5;

    GroceryItem t1, t2, t3, t4, t5;
    stream >> t1 >> t2 >> t3 >> t4 >> t5;

    affirm.is_equal( "Symmetrical Grocery Item insertion and extraction 1", g1, t1 );
    affirm.is_equal( "Symmetrical Grocery Item insertion and extraction 2", g2, t2 );
    affirm.is_equal( "Symmetrical Grocery Item insertion and extraction 3", g3, t3 );
    affirm.is_equal( "Symmetrical Grocery Item insertion and extraction 4", g4, t4 );
    affirm.is_equal( "Symmetrical Grocery Item insertion and extraction 5", g5, t5 );
  }



  void GroceryItemRegressionTest::comparison()
  {
    GroceryItem less( "a1", "a1", "a1", 10.0 ), more(less);

    // Be careful - using affirm.xxx() may hide the class-under-test overloaded operators.  But affirm.is_true() doesn't provide as
    // much information when the test fails.
    affirm.is_equal( "Equality test - is equal", less, more );
    affirm.is_true ( "Equality test - is not equal", !( less != more ) );
    affirm.is_equal( "Equality test - floating point lower bound ", less, GroceryItem {"a1", "a1", "a1", 9.9999} );
    affirm.is_equal( "Equality test - floating point upper bound ", less, GroceryItem {"a1", "a1", "a1", 10.0001} );

    auto check = [&]()
    {
      // Exercise all relational operators for the class-under-test.
      return less < more
          && less <= more
          && more > less
          && more >= less;
    };

    more = {"a1", "a1", "a1", 11.0};
    affirm.is_true( "Inequality test by Price", check() );

    more = {"a2", "a1", "a1", 9.0};
    affirm.is_true( "Inequality test by Product Name", check() );

    more = {"a0", "a2", "a1", 9.0};
    affirm.is_true( "Inequality test by Brand Name", check() );

    more = {"a0", "a0", "a2", 9.0};
    affirm.is_true( "Inequality test by UPC", check() );
  }



  GroceryItemRegressionTest::GroceryItemRegressionTest()
  {
    std::clog << std::boolalpha << std::showpoint << std::fixed << std::setprecision( 2 );


    try
    {
      std::clog << "\nGrocery Item Regression Test:  Construction\n";
      construction();

      std::clog << "\nGrocery Item Regression Test:  Relational comparisons\n";
      comparison();

      std::clog << "\nGrocery Item Regression Test:  Input/Output\n";
      io ();

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
