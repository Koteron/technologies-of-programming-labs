#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace nefedev
{
  class Triangle: public Shape
  {
  public:
    Triangle() = delete;
    Triangle(const point_t& a, const point_t& b, const point_t& c);
    double getArea() override;
    rectangle_t getFrameRect() override;
    void move(double xShift, double yShift) override;
    void move(const point_t& newCenter) override;
  private:
    point_t A_;
    point_t B_;
    point_t C_;
    void doScale(double multiplier) override;
  };
}

#endif
