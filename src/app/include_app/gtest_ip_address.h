#ifndef GTEST_IP_ADDRESS_H
#define GTEST_IP_ADDRESS_H
#include <string>
#include <iostream>
#include <cstring>
#include <gtest/gtest.h>

/**
 * @brief TestCIPAddress to test for instance variables.
 * 
 */
class TestCIPAddress : public :: testing :: Test
{
   public:
      std::string ipv4AddressString, invalidIPv4AddressString;
      std::string  ipv6AddressString, invalidIPv6AddressString;
      virtual void SetUp()
      {
         ipv4AddressString = "127.0.0.1";
         invalidIPv4AddressString = "123456A";
         ipv6AddressString="a060:9006:b0a2:5200:2a1c:d979:4276:836f";
         invalidIPv6AddressString="a060:9006:b0a2:ghdiss:2a1c:d#979:42276:836f";
      }
      
      virtual void TearDown()
      {
         //Not Utilized now.  
      }
};
#endif // ! GTEST_IP_ADDRESS_H
