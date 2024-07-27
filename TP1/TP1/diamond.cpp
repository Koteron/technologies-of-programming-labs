#include "diamond.hpp"
#include <stdexcept>

namespace
{
  nefedev::point_t getHorizontalPoint(nefedev::point_t& a, nefedev::point_t& b, nefedev::point_t& c)
  {
    if (a.x == c.x)
    {
      return b;
    }
    else if (a.x == b.x)
    {
      return c;
    }
    else if (b.x == c.x)
    {
      return a;
    }
    else
    {
      throw std::logic_error("Diamond can't exist: Can't find horizontal point\n");
    }
  }
  nefedev::point_t getVerticalPoint(nefedev::point_t& a, nefedev::point_t& b, nefedev::point_t& c)
  {
    if (a.y == c.y)
    {
      return b;
    }
    else if (a.y == b.y)
    {
      return c;
    }
    else if (b.y == c.y)
    {
      return a;
    }
    else
    {
      throw std::logic_error("Diamond can't exist: Can't find vertical point\n");
    }
  }
  nefedev::point_t getCenterPoint(nefedev::point_t& a, nefedev::point_t& b, nefedev::point_t& c)
  {
    if ((a.x == c.x && b.y == c.y) || (a.y == c.y && b.x == c.x))
    {
      return c;
    }
    else if ((a.x == c.x && b.y == c.y) || (a.y == c.y && b.x == c.x))
    {
      return a;
    }
    else if ((b.x == c.x && b.y == a.y) || (b.y == c.y && b.x == a.x))
    {
      return b;
    }
    else
    {
      throw std::logic_error("Diamond can't exist: Can't find center point\n");
    }
  }
}
nefedev::Diamond::Diamond(point_t& a, point_t& b, point_t& c):
  center(getCenterPoint(a, b, c)),
  horizontalPoint(getHorizontalPoint(a, b, c)),
  verticalPoint(getVerticalPoint(a, b, c))
{}

double nefedev::Diamond::getArea()
{
  return std::abs(verticalPoint.y - center.y) * std::abs(horizontalPoint.x - center.x) * 2;
}

nefedev::rectangle_t nefedev::Diamond::getFrameRect()
{
  double rectHeight = std::abs(verticalPoint.y - center.y) * 2;
  double rectWidth = std::abs(horizontalPoint.x - center.x) * 2;
  rectangle_t rect = { rectWidth, rectHeight, center };
  return rect;
}

void nefedev::Diamond::move(double xShift, double yShift)
{
  verticalPoint.x += xShift;
  verticalPoint.y += yShift;
  horizontalPoint.x += xShift;
  horizontalPoint.y += yShift;
  center.x += xShift;
  center.y += yShift;
}

void nefedev::Diamond::move(const point_t& newCenter)
{
  verticalPoint.x = center.x;
  verticalPoint.y = newCenter.y + verticalPoint.y - center.y;
  horizontalPoint.y = center.y;
  horizontalPoint.x = newCenter.x + horizontalPoint.x - center.x;
  center = newCenter;
}

void nefedev::Diamond::doScale(const double multiplier)
{
  verticalPoint.y = center.y + (verticalPoint.y - center.y) * multiplier;
  horizontalPoint.x = center.x + (horizontalPoint.x - center.x) * multiplier;
}
