#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

#include <iosfwd>

namespace nefedev
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
  std::ostream& operator<<(std::ostream& out, const point_t& point);
  std::ostream& operator<<(std::ostream& out, const rectangle_t& rect);
}
#endif
