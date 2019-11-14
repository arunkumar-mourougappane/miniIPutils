#include <gtest_ip_address.h>
#include <ip_address.h>

TEST_F(TestCIPAddress, CheckifValidIPv4IsAccepted)
{
   mini_ip_utilities::CIPAddress ipAddressObj(ipv4AddressString);
   ASSERT_EQ(true, ipAddressObj.IsValidIP())  << "Failed to accept valid IP Address argument, IsValidIP() returned false.";
   EXPECT_EQ(std::string("127.0.0.1"), ipAddressObj.GetString())  << "Failed to accept valid IPv4 Address argument, ipAddr.GetString() returned empty string.";
   EXPECT_EQ(AF_INET, ipAddressObj.GetIPFamily())  << "Failed to accept valid IPv4 Address argument, ipAddr.GetIPFamily() returned AF_UNSPEC";
   EXPECT_TRUE(ipAddressObj)  << "Failed to overload bool operator valid IPv4 Address argument,it returned false.";
}

TEST_F(TestCIPAddress, CheckifInvalidIPv4IsAccepted)
{
    mini_ip_utilities::CIPAddress ipAddressObj(invalidIPv4AddressString);
   ASSERT_EQ(false, ipAddressObj.IsValidIP())  << "Failed to accept invalid IPv4 Address argument, IsValidIP() returned true.";
   EXPECT_EQ(std::string(""), ipAddressObj.GetString())  << "Failed to accept invalid IPv4 Addres argument, ipAddr.GetString() returned a string.";
   EXPECT_EQ(AF_UNSPEC, ipAddressObj.GetIPFamily())  << "Failed to accept valid IPv4 Address argument, ipAddr.GetIPFamily() returned AF_INET";
   EXPECT_FALSE(ipAddressObj)  << "Failed to overload bool operator invalid IPv4 Address argument, it returned false.";
}

TEST_F(TestCIPAddress, CheckifValidIPv6IsAccepted)
{
   mini_ip_utilities::CIPAddress ipAddressObj(ipv6AddressString);
   ASSERT_EQ(true, ipAddressObj.IsValidIP())  << "Failed to accept valid IPv6 Address argument, IsValidIP() returned false.";
   EXPECT_EQ(ipv6AddressString, ipAddressObj.GetString())  << "Failed to accept valid IPv6 Address argument, ipAddr.GetString() returned empty string.";
   EXPECT_EQ(AF_INET6, ipAddressObj.GetIPFamily())  << "Failed to accept valid IPv6 Address argument, ipAddr.GetIPFamily() returned AF_UNSPEC or AF_INET";
   EXPECT_TRUE(ipAddressObj)  << "Failed to overload bool operator valid IPv6 Address argument,it returned false.";
}

TEST_F(TestCIPAddress, CheckifInvalidIPv6IsAccepted)
{
   mini_ip_utilities::CIPAddress ipAddressObj(invalidIPv6AddressString);
   ASSERT_EQ(false, ipAddressObj.IsValidIP())  << "Failed to accept invalid IPv6 Address argument, IsValidIP() returned true.";
   EXPECT_EQ(std::string(""), ipAddressObj.GetString())  << "Failed to accept invalid IPv6 Address argument, ipAddr.GetString() returned a string.";
   EXPECT_EQ(AF_UNSPEC, ipAddressObj.GetIPFamily())  << "Failed to accept valid IPv6 Address argument, ipAddr.GetIPFamily() returned AF_INET6 or AF_INET";
   EXPECT_FALSE(ipAddressObj)  << "Failed to overload bool operator invalid IPv6 Address argument, it returned false.";
}
