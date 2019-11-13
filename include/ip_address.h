#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>

#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H
namespace mini_ip_utilities
{
   class CIPAddress
   {
      private:
         std::string mIpAddress;
         sa_family_t mIPFamily;
         bool mValidIP;
         struct sockaddr_storage mIPAddressBytes;
      public:
         CIPAddress(std::string ipAddress);
         CIPAddress(in_addr_t& byteAddress);
         CIPAddress(const struct in6_addr & byteAddressData);
         CIPAddress(const struct in_addr & byteAddressData);
         CIPAddress(const struct sockaddr_storage& byteAddressData);
         CIPAddress();
         
         sa_family_t GetIPFamily() const;
         bool IsValidIP() const;
         const std::string GetString() const;
         const struct sockaddr_storage GetIPAddressBytes() const;
         int_least32_t GetIPAddress(struct in_addr & byteAddress ) const;
         int_least32_t GetIPAddress(struct in6_addr & byteAddress ) const;
         int_least32_t Compare(const CIPAddress& IpAddress) const;
         bool operator== (const CIPAddress &IpAddress);
         bool operator!= (const CIPAddress &IpAddress);
   };
}
#endif