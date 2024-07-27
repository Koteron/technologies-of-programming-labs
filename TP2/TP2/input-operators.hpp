#ifndef INPUT_OPERATORS_HPP
#define INPUT_OPERATORS_HPP

#include <iosfwd>
#include <string>

namespace nefedev
{
  struct DoubleSciIO
  {
    double& key;
  };
  struct UnsLongLongIO
  {
    unsigned long long& key;
  };
  struct StringIO
  {
    std::string& key;
  };
  struct DelimeterIO
  {
    char exp;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::istream& operator>>(std::istream& in, DoubleSciIO&& dest);
  std::istream& operator>>(std::istream& in, UnsLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}

#endif
