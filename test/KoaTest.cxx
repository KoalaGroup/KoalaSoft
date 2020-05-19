#define BOOST_TEST_MODULE ExampleTest

#include "KoaTest.h"
#include <iostream>
// #include "KoaMapEncoder.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ExampleTest)

BOOST_AUTO_TEST_CASE(FirstTestApp)
{
  // auto encoder = KoaMapEncoder::Instance();
  // auto i = encoder->GetRecRearID();
  std::cout << "I'm KoaTest!" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()