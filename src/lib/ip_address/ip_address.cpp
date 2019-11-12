#include <unistd.h>
#include <netinet/in.h>
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
      mIPFamily = AF_UNSPEC;
      mValidIP=false;
      mIPAddressBytes = {};
      mIpAddress.clear();
   }
   CIPAddress::CIPAddress(std::string ipAddress)
   {
      mIPFamily=AF_UNSPEC;
      mValidIP=false;
      mIPAddressBytes={0};
      struct sockaddr_in v4Address = {0};
      struct sockaddr_in6 v6Address = {0};
      if(ipAddress.length() > 0)
      {
         if (inet_pton(AF_INET, ipAddress.c_str(), &v4Address.sin_addr) == 1)
         {
            char ipv4Buffer[INET_ADDRSTRLEN];
            mIPFamily = AF_INET;
            mValidIP = true;
            v4Address.sin_family = AF_INET;
            std::memcpy(&mIPAddressBytes, &v4Address, sizeof(v4Address));
            mIpAddress = std::string(inet_ntop(AF_INET, &(((struct sockaddr_in *)&mIPAddressBytes)->sin_addr), ipv4Buffer, INET_ADDRSTRLEN));
         }
         else if (inet_pton(AF_INET6, ipAddress.c_str(), &v6Address.sin6_addr) == 1)
         {
            char ipv6Buffer[INET6_ADDRSTRLEN];
            mIPFamily = AF_INET6;
            v6Address.sin6_family = AF_INET6;
            mValidIP = true;
            std::memcpy(&mIPAddressBytes, &v6Address, sizeof(v6Address));
            mIpAddress = std::string(inet_ntop(AF_INET6, &((struct sockaddr_in6 *)&mIPAddressBytes)->sin6_addr, ipv6Buffer, INET6_ADDRSTRLEN));
         }
         else
         {
            mIpAddress.clear();
            mIPFamily = AF_UNSPEC;
            mIPAddressBytes = {};
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

      if (inet_ntop(AF_INET, &v4Address.sin_addr, ipv4Buffer, INET_ADDRSTRLEN))
      {
         mIPFamily = AF_INET;
         mValidIP = true;
         v4Address.sin_family = AF_INET;
         std::memcpy(&mIPAddressBytes, &v4Address, sizeof(v4Address));
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

      if (inet_ntop(AF_INET, &byteAddressData, ipv4Buffer, INET_ADDRSTRLEN))
      {
         mIPFamily = AF_INET;
         mValidIP = true;
         v4Address.sin_family = AF_INET;
         std::memcpy(&mIPAddressBytes, &v4Address, sizeof(v4Address));
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
      if((!IpAddress.IsValidIP()) || (!IsValidIP()))
      {
         return -1;
      }
      else
      {
         if (IpAddress.GetIPFamily() != mIPFamily)
         {
            return -2;
         }
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

}