#include <exception>
#include <iostream>
#include <typeinfo>

#include "GroceryItem.hpp"
#include "GroceryList.hpp"



int main()
{
  try
  {
    // Let's start a grocery list
    GroceryList thingsToBuy = {{"milk"    },
                               {"hot dogs"},
                               {"eggs"    },
                               {"bread"   }};
      std::cout << "\t" << thingsToBuy << std::endl;//

    // Changed my mind, I want to make sure I get eggs so I'm going to move that to the top of my list
    thingsToBuy.moveToTop( {"eggs"} );

    // Let's see what's on the list so far
    std::cout << "My Grocery List" << thingsToBuy << "\n\n";

    // Yay, no.  Need to add a few more things
    thingsToBuy += {{"bananas"},
                    {"apples" }};

    // My roommate also has a grocery list
    GroceryList roommatesList = {{"potato chips", "Ruffles"   },
                                 {"potato chips", "Frito Lays"},
                                 {"beer", "Bud Lite"          },
                                 {"pretzels"                  }};

    std::cout << "My roommate's Grocery List" << roommatesList << "\n\n";

    // Let's combine the lists (if different) and go shopping
    if( thingsToBuy != roommatesList ) thingsToBuy += roommatesList;


    // Oops, forgot butter.  Let's add that right before bread.
    thingsToBuy.insert( {"butter", "Lakes 'Ole"}, thingsToBuy.find( {"bread"} ) );

    // And beer, really?  You should be studying!
    thingsToBuy.remove( {"beer", "Bud Lite"} );

    // Now let's see what's on the list
    std::cout << "Combined Grocery Lists" << thingsToBuy << "\n\n";



    // Did you get it right?
    GroceryList expectedResults = {{"eggs"                      },
                                   {"milk"                      },
                                   {"hot dogs"                  },
                                   {"butter", "Lakes 'Ole"      },
                                   {"bread"                     },
                                   {"bananas"                   },
                                   {"apples"                    },
                                   {"potato chips", "Ruffles"   },
                                   {"potato chips", "Frito Lays"},
                                   {"pretzels"                  }};

    std::cout << "\nExpected results:" << expectedResults                                        << "\n\n"
              << "\nActual results:"   << thingsToBuy                                            << "\n\n"
              << "\nTest results:  "     << ( thingsToBuy == expectedResults  ? "PASS"  :  "FAIL") << '\n';
  }

  catch( const std::exception & ex )
  {
    std::cerr << "Fatal Error:  unhanded exception \"" << typeid( ex ).name() << "\"\n"
              << ex.what() << '\n';
  }
}
