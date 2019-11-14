# miniIPutils <img src="images/ip_address.png" width="30">

[![Build Status](https://travis-ci.com/arunkumar-mourougappane/miniIPutils.svg?branch=master)](https://travis-ci.com/arunkumar-mourougappane/miniIPutils)

An advanced self managing IP Address Utility tool capable of managing both managing IPv4 and IPv6 Address.

[CIPAddress](https://github.com/arunkumar-mourougappane/miniIPutils/blob/master/src/lib/ip_address/ip_address.cpp "Source Code for CIPAddress API")

CIPAddress wrapper library can process any IP address format from one among the following:

- std::string
- const char*
- struct in_addr_t
- struct in_addr
- struct in6_addr
- struct sockaddr_storage

**APIs:**

- GetIPFamily() returns the IP Address family.
- IsValidIP() returns if IP is valid or not.
- GetString() returns a string for the IP Address.
- GetIPAddressBytes() returns a sockaddr_storage structure.
- GetIPAddress(struct in_addr & byteAddress ) returns 0 on success with valid IPv4 address populated to byte address.
- GetIPAddress(struct in6_addr & byteAddress ) returns 0 on success with valid IPv6 address populated to byte address.
- Compare(const CIPAddress& IpAddress)  compare a CIPAddress instance with current insance.
- to_string() provides a string representation of a class.

**Example of Use:**

Here are some examples of the use for CIPAddress class implementation.

```cpp
#include <CIPAddress.h>

CIPAddress obj("127.0.01");
// Checking for validty
if (obj) // Also obj.IsValidIP() can be use to check validity.
{
    std::cout << "Valid IP Address";
}
// to print ip Address string or send it to stream
stream_obj << obj;
// to get string value;
std::cout << obj.GetString();
```
