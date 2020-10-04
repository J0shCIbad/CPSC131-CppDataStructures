#pragma once
#include <cmath>          // abs()
#include <iostream>
#include <string>
#include <type_traits>    // is_floating_point

namespace Regression
{
  constexpr auto EPSILON = 1E-4;

  struct CheckResults
  {
                                     bool is_true                    ( const std::string & nameOfTest,                     bool      actual );
    template<typename T, typename U> bool is_equal                   ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_not_equal               ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_less_than               ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_less_than_or_equal_to   ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_greater_than            ( const std::string & nameOfTest, const T & expected, const U & actual );
    template<typename T, typename U> bool is_greater_than_or_equal_to( const std::string & nameOfTest, const T & expected, const U & actual );

    unsigned testCount   = 0;
    unsigned testsPassed = 0;
  };
  std::ostream & operator<<( std::ostream & stream, const CheckResults & results );










  inline std::ostream & operator<<( std::ostream & stream, const CheckResults & results )
  {
    stream << "\n\nSummary: " 
           << results.testsPassed << " of " << results.testCount 
           << " (" << results.testsPassed * 100.0 / results.testCount << "%) tests passed\n\n\n";

    return stream;
  }



  inline bool CheckResults::is_true( const std::string & nameOfTest, bool actual )
  {
    return is_equal( nameOfTest, true, actual );
  }



  template<typename T, typename U>
  bool CheckResults::is_equal( const std::string & nameOfTest, const T & expected, const U & actual )
  {
    ++testCount;

    bool pass;
    if constexpr( std::is_floating_point<T>::value && std::is_floating_point<U>::value ) pass =  std::abs( expected - actual ) < EPSILON;
    else                                                                                 pass =  expected == actual;

    if( pass )
    {
      ++testsPassed;
      std::clog << "  [PASSED] " << nameOfTest << ": expected and actual '" << actual << "' are equal\n";
    }
    else
    {
      std::clog << " *[FAILED] " << nameOfTest << ": expected '" << expected << "' is not equal to actual '" << actual << "'\n";
    }

    return pass;
  }
}    // namespace Regression
