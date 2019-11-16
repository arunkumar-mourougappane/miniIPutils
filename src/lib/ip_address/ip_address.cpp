#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ip_address.h>

namespace mini_ip_utilities
{
   CIPAddress::CIPAddress()
   {
      // Asssign default values to all.
      mIPFamily = AF_UNSPEC;
      mValidIP=false;
      mIPAddressBytes = {0};
      mIpAddress.clear();
   }

   CIPAddress::CIPAddress(std::string ipAddress)
   {
      mIPFamily=AF_UNSPEC;
      mValidIP=false;
      mIPAddressBytes={0};

      // Needed for parsed byte address.
      struct sockaddr_in v4Address = {0};
      struct sockaddr_in6 v6Address = {0};

      // If the IP Address is an empty string 
      // we reject it. However, we allow 0.0.0.0.
      if(ipAddress.length() > 0)
      {
         // verify if conversion to IPv4 worked, if yes then save the address information
         if (inet_pton(AF_INET, ipAddress.c_str(), &v4Address.sin_addr) == 1)
         {
            char ipv4Buffer[INET_ADDRSTRLEN];
            mIPFamily = AF_INET;
            mValidIP = true;
            v4Address.sin_family = AF_INET;
            std::memcpy(&mIPAddressBytes, &v4Address, sizeof(v4Address));
            mIpAddress = std::string(inet_ntop(AF_INET, &(((struct sockaddr_in *)&mIPAddressBytes)->sin_addr), ipv4Buffer, INET_ADDRSTRLEN));
         }
         // verify if address is IPv6, if yes then save all to instance.
         else if (inet_pton(AF_INET6, ipAddress.c_str(), &v6Address.sin6_addr) == 1)
         {
            char ipv6Buffer[INET6_ADDRSTRLEN];
            mIPFamily = AF_INET6;
            v6Address.sin6_family = AF_INET6;
            mValidIP = true;
            std::memcpy(&mIPAddressBytes, &v6Address, sizeof(v6Address));
            mIpAddress = std::string(inet_ntop(AF_INET6, &((struct sockaddr_in6 *)&mIPAddressBytes)->sin6_addr, ipv6Buffer, INET6_ADDRSTRLEN));
         }
         // if IP was invalid, then reset all variables.
         else
         {
            mIpAddress.clear();
            mIPFamily = AF_UNSPEC;
            mIPAddressBytes = {0};
         }
      }
   }

   CIPAddress::CIPAddress(in_addr_t& byteAddress)
   {
      mIPFamily = AF_UNSPEC;
      mValidIP = false;
      struct sockaddr_in v4Address;
      v4Address.sin_addr.s_addr = byteAddress;
      char ipv4Buffer[INET_ADDRSTRLEN];
      mIpAddress.clear();
      mIPAddressBytes = {0};
      // if given IPv4 byte address is valid, save to the instance!
      if (inet_ntop(AF_INET, &v4Address.sin_addr, ipv4Buffer, INET_ADDRSTRLEN))
      {
         mIPFamily = AF_INET;
         mValidIP = true;
         v4Address.sin_family = AF_INET;
         std::memcpy(&mIPAddressBytes, &v4Address, sizeof(v4Address));
         // The IP Address string is canonicalized, save for use to represent.
         mIpAddress = std::string(ipv4Buffer);
      }
   }
   
   CIPAddress::CIPAddress(const struct in_addr & byteAddressData)
   {
      mIPFamily = AF_UNSPEC;
      mValidIP = false;
      struct sockaddr_in v4Address;
      v4Address.sin_addr.s_addr = byteAddressData.s_addr;
      mIpAddress.clear();
      char ipv4Buffer[INET_ADDRSTRLEN];
      mIPAddressBytes = {0};
      // if given IPv4 byte address is valid, save to the instance!
      if (inet_ntop(AF_INET, &byteAddressData, ipv4Buffer, INET_ADDRSTRLEN))
      {
         mIPFamily = AF_INET;
         mValidIP = true;
         v4Address.sin_family = AF_INET;
         std::memcpy(&mIPAddressBytes, &v4Address, sizeof(v4Address));

         // The IP Address string is canonicalized, save for use to represent.
         mIpAddress = std::string(ipv4Buffer);
      }
   }
   
   CIPAddress::CIPAddress(const struct in6_addr & byteAddressData)
   {
      mIPFamily = AF_UNSPEC;
      mValidIP = false;
      struct sockaddr_in6 v6Address;
      v6Address.sin6_addr = byteAddressData;
      char ipv6Buffer[INET6_ADDRSTRLEN];
      mIpAddress.clear();
      mIPAddressBytes = {0};

      // if given IPv6 byte address is valid, save to the instance!
      if (inet_ntop(AF_INET6, &v6Address.sin6_addr, ipv6Buffer, INET6_ADDRSTRLEN))
      {
         mIPFamily = AF_INET6;
         mValidIP = true;
         v6Address.sin6_family = AF_INET6;
         std::memcpy(&mIPAddressBytes, &v6Address, sizeof(v6Address));
         //Caonicalize IP Address
         mIpAddress = std::string(ipv6Buffer);
      }
   }

   CIPAddress::CIPAddress(const struct sockaddr_storage & byteAddressData)
   {
      mIPFamily = byteAddressData.ss_family;
      mValidIP = false;
      mIPAddressBytes = byteAddressData;
      mIpAddress.clear();
      // Verify  for IPv4 Compatibility, and if valid save instance.
      if (byteAddressData.ss_family == AF_INET)
      {
         char ipv4Buffer[INET_ADDRSTRLEN];
         if (inet_ntop(AF_INET, &(((struct sockaddr_in *)&mIPAddressBytes)->sin_addr), ipv4Buffer, INET_ADDRSTRLEN))
         {
            mIPFamily = AF_INET;
            mValidIP = true;
            mIpAddress = std::string(ipv4Buffer);
         }
      }
      // Verify  for IPv6 Compatibility, and if valid save instance.
      else if (byteAddressData.ss_family == AF_INET6)
      {
         char ipv6Buffer[INET6_ADDRSTRLEN];
         if (inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)&mIPAddressBytes)->sin6_addr), ipv6Buffer, INET6_ADDRSTRLEN))
         {
            mIPFamily = AF_INET6;
            mValidIP = true;
            mIpAddress = std::string(ipv6Buffer);
         }
      }
      // No compatibility for IPv4v6 was found, so reset to defaults.
      else
      {
         mIPFamily = AF_UNSPEC;
         mIPAddressBytes = {0};
         mIpAddress.clear();
      }
   }


   sa_family_t CIPAddress::GetIPFamily() const
   {
      return mIPFamily;
   }

   bool CIPAddress::IsValidIP() const
   {
      return mValidIP;
   }
   
   const std::string CIPAddress::GetString() const
   {
      return mIpAddress;
   }

   const struct sockaddr_storage CIPAddress::GetIPAddressBytes() const
   {
      return mIPAddressBytes;
   }
   int_least32_t CIPAddress::GetIPAddress(struct in_addr& byteAddress ) const
   {
      // if the saved instance is IPv4, we save byte address to argument.
      if(GetIPFamily() == AF_INET)
      {
         byteAddress = ((struct sockaddr_in*)&mIPAddressBytes)->sin_addr;
      }
      else
      {
         byteAddress = {0};
         return -1;
      }
      return 0;
   }
   int_least32_t CIPAddress::GetIPAddress(struct in6_addr& byteAddress ) const
   {
      // if the saved instance is IPv6, we save byte address to argument.
      if(GetIPFamily() == AF_INET6)
      {
         byteAddress = ((struct sockaddr_in6*)&mIPAddressBytes)->sin6_addr;
      }
      else
      {
         byteAddress = {0};
         return -1;
      }
      return 0;
   }
   
   int_least32_t CIPAddress::Compare(const CIPAddress& IpAddress) const
   {
      // if one of the IPs are invalid, we don't need to comapare.
      if((!IpAddress.IsValidIP()) || (!IsValidIP()))
      {
         return -1;
      }
      else
      {
         // If the IP family doesn't match, no need to compare.
         if (IpAddress.GetIPFamily() != mIPFamily)
         {
            return -2;
         }
         // The IPAddress strings are canonicalized, so they can be compared
         // to be identical.
         else if(IpAddress.GetString().compare(GetString()) == 0)
         {
            return 0;
         }
         else
         {
            return -1;
         }
      }
   }

   bool CIPAddress::operator== (const CIPAddress &IpAddress)
   {
      if(GetIPFamily() == IpAddress.GetIPFamily() )
      {
         if(GetString().compare(IpAddress.GetString()) == 0)
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }
   }

   bool CIPAddress::operator!= (const CIPAddress &IpAddress)
   {
      return !(*this == IpAddress);
   }

   std::string CIPAddress::to_string() const
   {
      return mIpAddress;
   }

}
