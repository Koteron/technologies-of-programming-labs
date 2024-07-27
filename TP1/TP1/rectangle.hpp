#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace nefedev
{
  class Rectangle: public Shape
  {
  public:
    Rectangle() = delete;
    explicit Rectangle(const rectangle_t& rect);
    Rectangle(const point_t& leftBottom, const point_t& rightTop);
    double getArea() override;
    rectangle_t getFrameRect() override;
    void move(double xShift, double yShift) override;
    void move(const point_t& newCenter) override;
  private:
    void doScale(double multiplier) override;
    rectangle_t rectangle_;
  };
}

#endif

