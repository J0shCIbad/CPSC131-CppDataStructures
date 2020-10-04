#include <cmath>       // abs()
#include <cstdlib>     // exit()
#include <exception>
#include <iomanip>     // setprecision()
#include <iostream>    // boolalpha(), showpoint(), fixed()
#include <sstream>
#include <string>      // to_string()

#include "CheckResults.hpp"
#include "GroceryList.hpp"

namespace    // anonymous
{
  class GroceryListRegressionTest
  {
    public:
      GroceryListRegressionTest();

    private:
      void test();

      Regression::CheckResults affirm;
  } run_groceryItem_tests;




  void GroceryListRegressionTest::test()
  {
    const GroceryItem milk   ( "milk"          ),
                      hotDogs( "hot dogs"      ),
                      eggs   ( "eggs"          ),
                      bread  ( "bread"         ),
                      butter ( "peanut butter" ),
                      jelly  ( "jelly"         );

    {
      GroceryList list;
      affirm.is_equal( "Default construction:  Size", 0U, list.size() );
    }

    {
      GroceryList list;
      list.insert( eggs                                 );
      list.insert( bread, GroceryList::Position::BOTTOM );
      list.insert( milk,  1                             );
      list.insert( hotDogs                              );

      GroceryList expected = {hotDogs, eggs, milk, bread};

      affirm.is_equal( "Initializer list constructor:  Size",    4U,       list.size() );
      affirm.is_equal( "Initializer list constructor:  content", expected, list        );
    }

    {
      GroceryList list1 = {hotDogs, eggs, milk, bread};
      list1 += {eggs, milk, hotDogs, butter};

      GroceryList list2 = {hotDogs, jelly, milk, bread};
      list1 += list2;

      GroceryList expected = {hotDogs, eggs, milk, bread, butter, jelly};

      affirm.is_equal( "Initializer list concatenation:  Size",    6U,       list1.size() );
      affirm.is_equal( "Initializer list concatenation:  content", expected, list1        );

      affirm.is_equal( "Search - hot dogs",  0U, list1.find( hotDogs       ) );
      affirm.is_equal( "Search - eggs",      1U, list1.find( eggs          ) );
      affirm.is_equal( "Search - milk",      2U, list1.find( milk          ) );
      affirm.is_equal( "Search - bread",     3U, list1.find( bread         ) );
      affirm.is_equal( "Search - butter",    4U, list1.find( butter        ) );
      affirm.is_equal( "Search - jelly",     5U, list1.find( jelly         ) );
      affirm.is_equal( "Search - not there", 6U, list1.find( {"not there"} ) );
    }

    {
      GroceryList list = {hotDogs, milk, bread, butter, jelly};

      list.remove( milk );
      affirm.is_equal( "Remove by Item - middle", GroceryList {hotDogs, bread, butter, jelly}, list );

      list.remove( jelly );
      affirm.is_equal( "Remove by Item - bottom", GroceryList {hotDogs, bread, butter}, list );

      list.remove( hotDogs );
      affirm.is_equal( "Remove by Item - top", GroceryList {bread, butter}, list );

      list.remove( {"not there"} );
      affirm.is_equal( "Remove by Item - not there", GroceryList {bread, butter}, list );
    }

    {
      GroceryList list = {hotDogs, milk, bread, butter, jelly};

      list.remove( 1 );
      affirm.is_equal( "Remove by position - middle", GroceryList {hotDogs, bread, butter, jelly}, list );

      list.remove( 3 );
      affirm.is_equal( "Remove by position - bottom", GroceryList {hotDogs, bread, butter}, list );

      list.remove( 0 );
      affirm.is_equal( "Remove by position - top", GroceryList {bread, butter}, list );

      list.remove( 10 );
      affirm.is_equal( "Remove by position - bad index", GroceryList {bread, butter}, list );
    }

    {
      GroceryList list = {hotDogs, milk, bread, butter, jelly};

      list.moveToTop( butter        );
      list.moveToTop( jelly         );
      list.moveToTop( jelly         );
      list.moveToTop( butter        );
      list.moveToTop( bread         );
      list.moveToTop( {"not there"} );

      GroceryList expected = {bread, butter, jelly, hotDogs, milk};
      affirm.is_equal( "Move to top", expected, list );
    }

    {
      GroceryList list;

      try
      {
        for( unsigned i = 0; i < 100; ++i ) list.insert( "Item-" + std::to_string( i ) );
        affirm.is_true( "Fixed size array capacity check", false );
      }
      catch ( const GroceryList::CapacityExceeded_Ex & )  // expected
      {
        affirm.is_true( "Fixed size array capacity check", true );
      }
    }
  }




  GroceryListRegressionTest::GroceryListRegressionTest()
  {
    std::clog << std::boolalpha << std::showpoint << std::fixed << std::setprecision( 2 );


    try
    {
      std::clog << "\nGrocery List Regression Tests:\n";
      test();

      std::clog << affirm << '\n';
    }
    catch( const std::exception & ex )
    {
      std::clog << "FAILURE:  Regression test for \"class GroceryList\" failed with an unhandled exception. \n\n\n"
                << ex.what() << std::endl;

      // Reminder:  Objects with automatic storage are not destroyed by calling std::exit().  In this case, this is okay.
      // std::exit( -__LINE__ ); // uncomment to terminate program with test failures
    }
  }
}    // namespace
