#include <gtest_ip_address.h>
#include <ip_address.h>

TEST_F(TestCIPAddress, CheckifValidIPIsAccepted)
{
   mini_ip_utilities::CIPAddress ipAddressObj(ipAddressString);
   EXPECT_EQ(true, ipAddressObj.IsValidIP())  << "Failed to accept valid IP Addres argument, IsValidIP() returned false.";
   EXPECT_EQ(std::string("127.0.0.1"), ipAddressObj.GetString())  << "Failed to accept valid IP Addres argument, ipAddr.GetString() returned empty string.";
   EXPECT_EQ(AF_INET, ipAddressObj.GetIPFamily())  << "Failed to accept valid IP Addres argument, ipAddr.GetIPFamily() returned AF_UNSPEC";
}