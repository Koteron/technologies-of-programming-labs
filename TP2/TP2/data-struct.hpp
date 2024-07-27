#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iosfwd>

namespace nefedev
{
  struct DataStruct
  {
    double key1;
    unsigned long long int key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  bool operator<(const DataStruct& left, const DataStruct& right);
}

#endif
