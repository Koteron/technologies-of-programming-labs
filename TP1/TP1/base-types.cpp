#include "base-types.hpp"
#include <ostream>

std::ostream& nefedev::operator<<(std::ostream& out, const point_t& point)
{
  out << point.x << ' ' << point.y;
  return out;
}

std::ostream& nefedev::operator<<(std::ostream& out, const rectangle_t& rect)
{
  double width = rect.width;
  double height = rect.height;
  double centerX = rect.pos.x;
  double centerY = rect.pos.y;
  out << (centerX - width / 2) << ' ' << (centerY - height / 2) << ' ' << (centerX + width / 2) << ' ' << (centerY + height / 2);
  return out;
}
