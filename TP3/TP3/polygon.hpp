#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>

namespace nefedev
{
  struct DelimeterIO
  {
    char exp;
  };
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, nefedev::DelimeterIO&& dest);
}


#endif
