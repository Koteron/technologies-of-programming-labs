#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace nefedev
{
  class Shape
  {
  public:
    virtual double getArea() = 0;
    virtual rectangle_t getFrameRect() = 0;
    virtual void move(const point_t& newCenter) = 0;
    virtual void move(double xShift = 0, double yShift = 0) = 0;
    void scale(double multiplier);
  private:
    virtual void doScale(double multiplier) = 0;
  };
}
#endif

