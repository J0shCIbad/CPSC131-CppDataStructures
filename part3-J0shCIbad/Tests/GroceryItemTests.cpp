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
    {  // Input parsing
      std::istringstream stream( R"~~( "00072250018548","Nature's Own","Nature's Own Butter Buns Hotdog - 8 Ct",10.79

                                       "00028000517205", "Nestle"             ,
                                       "Nestle Media Crema Table Cream"       ,
                                       17.97

                                       "00034000020706"    ,
                                       "York",
                                       "York Peppermint Patties Dark Chocolate Covered Snack Size",
                                       12.64 "00038000570742",
                                       "Kellogg's", "Kellogg's Cereal Krave Chocolate",
                                         18.66

                                       "00014100072331" , "Pepperidge Farm", "Pepperidge Farm Classic Cookie Favorites", 14.43

                                       "00000000000000", "incomplete / invalid item"
                                 )~~" );

      GroceryItem t1, t2, t3, t4, t5, t6;
      stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;

      affirm.is_equal( "Grocery Item input parsing 1", GroceryItem {"Nature's Own Butter Buns Hotdog - 8 Ct",                    "Nature's Own",    "00072250018548", 10.79}, t1 );
      affirm.is_equal( "Grocery Item input parsing 2", GroceryItem {"Nestle Media Crema Table Cream",                            "Nestle",          "00028000517205", 17.97}, t2 );
      affirm.is_equal( "Grocery Item input parsing 3", GroceryItem {"York Peppermint Patties Dark Chocolate Covered Snack Size", "York",            "00034000020706", 12.64}, t3 );
      affirm.is_equal( "Grocery Item input parsing 4", GroceryItem {"Kellogg's Cereal Krave Chocolate",                          "Kellogg's",       "00038000570742", 18.66}, t4 );
      affirm.is_equal( "Grocery Item input parsing 5", GroceryItem {"Pepperidge Farm Classic Cookie Favorites",                  "Pepperidge Farm", "00014100072331", 14.43}, t5 );

      affirm.is_equal( "Grocery Item input parsing 6", GroceryItem(), t6 );
    }
    {  // read what you write
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
  }



  void GroceryItemRegressionTest::comparison()
  {
    GroceryItem less( "a1", "a1", "a1", 10.0 ), more(less);

    // Be careful - using affirm.xxx() may hide the class-under-test overloaded operators.  But affirm.is_true() doesn't provide as
    // much information when the test fails.
    affirm.is_equal    ( "Equality test - is equal                   ", less, more );
    affirm.is_equal    ( "Equality test - floating point lower limit ", less, GroceryItem {"a1", "a1", "a1", less.price() - EPSILON} );
    affirm.is_equal    ( "Equality test - floating point upper limit ", less, GroceryItem {"a1", "a1", "a1", less.price() + EPSILON} );

    affirm.is_not_equal( "Inequality Product Name test               ", less, GroceryItem {"b1", "a1", "a1", 10.0} );
    affirm.is_not_equal( "Inequality Brand Name test                 ", less, GroceryItem {"a1", "b1", "a1", 10.0} );
    affirm.is_not_equal( "Inequality UPC test                        ", less, GroceryItem {"a1", "a1", "b1", 10.0} );
    affirm.is_not_equal( "Inequality Price test - lower limit        ", less, GroceryItem {"a1", "a1", "a1", less.price() - ( 2 * EPSILON )} );
    affirm.is_not_equal( "Inequality Price test - upper limit        ", less, GroceryItem {"a1", "a1", "a1", less.price() + ( 2 * EPSILON )} );


    auto check = [&]()
    {
      // Exercise all relational operators for the class-under-test.
      return less < more
          && less <= more
          && more > less
          && more >= less;
    };

    more = {"a1", "a1", "a1", 11.0};
    affirm.is_true( "Relational Price test                      ", check() );

    more = {"a2", "a1", "a1", 9.0};
    affirm.is_true( "Relational Product Name test               ", check() );

    more = {"a0", "a2", "a1", 9.0};
    affirm.is_true( "Relational Brand Name test                 ", check() );

    more = {"a0", "a0", "a2", 9.0};
    affirm.is_true( "Relational UPC test                        ", check() );
  }



  GroceryItemRegressionTest::GroceryItemRegressionTest()
  {
    std::clog << std::boolalpha << std::showpoint << std::fixed << std::setprecision( 2 );


    try
    {
      std::clog << "\nGrocery Item Regression Test:  Construction\n";
      construction();

      std::clog << "\nGrocery Item Regression Test:  Relational comparisons\n";
      auto previousPrecision = std::clog.precision( static_cast<std::streamsize>( std::ceil( -std::log10( EPSILON ) ) ) );
      comparison();
      std::clog.precision( previousPrecision );

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
