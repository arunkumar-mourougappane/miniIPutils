/**
 * @file ip_address.h
 * @author Arunkumar (amouroug@buffalo.edu)
 * @brief A C++ IP Address Wrapper to handle both IPv4 as 
 *        well as IPv6 Addresses without the need for
 *        separate APIs to handle them.
 * @version 0.1
 * @date 2019-11-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>

#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H
namespace mini_ip_utilities
{
   /**
    * @brief CIPAddress wrapper to handle IPv4 and IPv6.
    * 
    */
   class CIPAddress
   {
      private:
         std::string mIpAddress;
         sa_family_t mIPFamily;
         bool mValidIP;
         struct sockaddr_storage mIPAddressBytes;
      public:
         /**
          * @brief Construct a new CIPAddress object
          * 
          * @param ipAddress - a std::string of IPv4 or 
          *    IPv6 Address. All instance variables are
          *    populated for a valid IP.
          */
         CIPAddress(std::string ipAddress);

         /**
          * @brief Construct a new CIPAddress object
          * 
          * @param byteAddress take a reference to byte
          *    address value and if valid populates
          *    all instance variables.
          */
         CIPAddress(in_addr_t& byteAddress);

         /**
          * @brief Construct a new CIPAddress object
          * 
          * @param byteAddressData a reference to the
          *    IPv6 in6_addr and if valid populates 
          *    all the instance variables of the class
          *    with appropriate information.
          */
         CIPAddress(const struct in6_addr & byteAddressData);

         /**
          * @brief Construct a new CIPAddress object
          * 
          * @param byteAddressData a reference to the IPv4
          *    byte address is taken and if found valid is
          *    used to populate all instance variable
          *    information.
          */
         CIPAddress(const struct in_addr & byteAddressData);

         /**
          * @brief Construct a new CIPAddress object
          * 
          * @param byteAddressData a refernce to sockaddr_storage
          *    structure, the ip address is detected from the
          *    structure and is then used to populate all
          *    instance variable information.
          */
         CIPAddress(const struct sockaddr_storage& byteAddressData);

         /**
          * @brief Construct a new CIPAddress object
          * 
          */
         CIPAddress();

         /**
          * @brief GetIPFamily() gives the IP Address 
          *    family of the IP Address saved in the
          *    instance.
          * 
          * @return sa_family_t  of values AF_INET,
          *    AF_INET6 or AF_UNSPEC
          */
         sa_family_t GetIPFamily() const;

         /**
          * @brief IsValidIP() checks if IP from
          *    instance is valid or not.
          * 
          * @return true if IP is valid
          * @return false if IP is invalid
          */
         bool IsValidIP() const;

         /**
          * @brief Get the String the IP Address instance.
          * 
          * @return const std::string 
          */
         const std::string GetString() const;

         /**
          * @brief Get Byte Address information in the form of
          *    a sockaddr_storage structure.
          * 
          * @return const struct sockaddr_storage 
          */
         const struct sockaddr_storage GetIPAddressBytes() const;
         
         /**
          * @brief Gets the byte address of IPv4 address from the
          *    instance and saves to argument reference.
          * 
          * @param byteAddress a byte address for IPv4 is generated
          *    and populated to the reference provided as argument.
          * 
          * @return int_least32_t  0 on success with the correct byte
          *    address and -1 for failure with IN_ADDR_ANY populated
          *    for reference argument.
          */
         int_least32_t GetIPAddress(struct in_addr & byteAddress ) const;

         /**
          * @brief Gets the byte address of IPv6 address from the
          *    instance and saves to argument reference.
          * 
          * @param byteAddress  a byte address for IPv6 is generated
          *    and populated to the reference provided as argument.
          * 
          * @return int_least32_t  0 on success with the correct byte
          *    address and -1 for failure with in6_addr_any populated
          *    for reference argument.
          */
         int_least32_t GetIPAddress(struct in6_addr & byteAddress ) const;

         /**
          * @brief Compares current CIPAddess instance with another.
          * 
          * @param IpAddress CIPAddress instance that needs to be comapred
          *    with.
          * @return int_least32_t returns 0 on success -1 if they are not
          *    the same.
          */
         int_least32_t Compare(const CIPAddress& IpAddress) const;

         /**
          * @brief operator overloading for equality.
          * 
          * @param IpAddress to be compared with.
          * 
          * @return true if the CIPAddress instance compared
          *    is the same.
          * @return false if CIPAddress instances are
          *    different.
          */
         bool operator== (const CIPAddress &IpAddress);
         
         /**
          * @brief Operator overloading for inequality
          * 
          * @param IpAddress to be compared with.
          * 
          * @return true f the CIPAddress instance compared
          *    is not the same.
          * @return false if the CIPAddress instance compared
          *    is the same.
          */
         bool operator!= (const CIPAddress &IpAddress);

         /**
          * @brief gives a string representation
          * 
          * @return std::string a string representation of
          *    the IP Address.
          */
         std::string to_string() const;
         /**
          * @brief Provides a boolean state of the instance
          * 
          * @return true if IP Address is valid
          * @return false if IP Address is invalid.
          */
         explicit operator bool() const 
         {
            return IsValidIP();
         }
   };
}
#endif