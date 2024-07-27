#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace nefedev
{
  class Diamond: public Shape
  {
  public:
    Diamond() = delete;
    Diamond(point_t& a, point_t& b, point_t& c);
    double getArea() override;
    rectangle_t getFrameRect() override;
    void move(double xShift, double yShift) override;
    void move(const point_t& newCenter) override;
  private:
    point_t center;
    point_t horizontalPoint;
    point_t verticalPoint;
    void doScale(double multiplier) override;
  };
}

#endif
