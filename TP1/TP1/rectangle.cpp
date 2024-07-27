#include "rectangle.hpp"
#include <stdexcept>

nefedev::Rectangle::Rectangle(const rectangle_t& rect):
  rectangle_(rect)
{
  if (rect.width == 0 || rect.height == 0)
  {
    throw std::logic_error("Rectangle can't exist: one of rectangle's sides equals 0\n");
  }
}
nefedev::Rectangle::Rectangle(const point_t& point1, const point_t& point2)
{
  if (point1.x == point2.x || point1.y == point2.y)
  {
    throw std::logic_error("Rectangle can't exist: one of rectangle's sides equals 0\n");
  }
  if (point1.x > point2.x || point1.y > point2.y)
  {
    throw std::logic_error("Rectangle points are given in wrong order\n");
  }
  rectangle_.width = std::abs(point2.x - point1.x);
  rectangle_.height = std::abs(point2.y - point1.y);
  rectangle_.pos.x = (point1.x + point2.x) / 2;
  rectangle_.pos.y = (point1.y + point2.y) / 2;
}
double nefedev::Rectangle::getArea()
{
  return rectangle_.width * rectangle_.height;
}
nefedev::rectangle_t nefedev::Rectangle::getFrameRect()
{
  return rectangle_;
}
void nefedev::Rectangle::move(const double xShift, const double yShift)
{
  rectangle_.pos.x += xShift;
  rectangle_.pos.y += yShift;
}
void nefedev::Rectangle::move(const point_t& newCenter)
{
  rectangle_.pos = newCenter;
}
void nefedev::Rectangle::doScale(const double multiplier)
{
  rectangle_.width *= multiplier;
  rectangle_.height *= multiplier;
}
