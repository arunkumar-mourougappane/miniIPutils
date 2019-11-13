#ifndef GTEST_IP_ADDRESS_H
#define GTEST_IP_ADDRESS_H
#include <string>
#include <iostream>
#include <cstring>
#include <gtest/gtest.h>


class TestCIPAddress : public :: testing :: Test
{
   public:
      std::string ipAddressString, invalidIPAddressString;
      virtual void SetUp()
      {
         ipAddressString = "127.0.0.1";
         invalidIPAddressString = "123456A";
      }
      
      virtual void TearDown()
      {
         //Not Utilized now.  
      }
};
#endif // ! GTEST_IP_ADDRESS_H
