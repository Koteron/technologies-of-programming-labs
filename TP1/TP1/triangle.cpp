#include "triangle.hpp"
#include <stdexcept>
#include <algorithm>
#include <cmath>

nefedev::Triangle::Triangle(const point_t& a, const point_t& b, const point_t& c):
  A_(a),
  B_(b),
  C_(c)
{
  double AB = std::sqrt((A_.x - B_.x) * (A_.x - B_.x) + (A_.y - B_.y) * (A_.y - B_.y));
  double AC = std::sqrt((A_.x - C_.x) * (A_.x - C_.x) + (A_.y - C_.y) * (A_.y - C_.y));
  double BC = std::sqrt((C_.x - B_.x) * (C_.x - B_.x) + (C_.y - B_.y) * (C_.y - B_.y));
  if (AB + AC <= BC || AC + BC <= AB || AB + BC <= AC || AB <= 0 || BC <= 0 || AC <= 0)
  {
    throw std::logic_error("Triangle can't exist: does not satisfy the condition of triangle existence\n");
  }
}

double nefedev::Triangle::getArea()
{
  double AB = std::sqrt((A_.x - B_.x) * (A_.x - B_.x) + (A_.y - B_.y) * (A_.y - B_.y));
  double AC = std::sqrt((A_.x - C_.x) * (A_.x - C_.x) + (A_.y - C_.y) * (A_.y - C_.y));
  double BC = std::sqrt((C_.x - B_.x) * (C_.x - B_.x) + (C_.y - B_.y) * (C_.y - B_.y));
  double halfPerimeter = (AB + AC + BC) / 2;
  return std::sqrt(halfPerimeter * (halfPerimeter - AB) * (halfPerimeter - AC) * (halfPerimeter - BC));
}

nefedev::rectangle_t nefedev::Triangle::getFrameRect()
{
  double rectPosX = (std::max({ A_.x, B_.x, C_.x }) + std::min({ A_.x, B_.x, C_.x })) / 2;
  double rectPosY = (std::max({ A_.y, B_.y, C_.y }) + std::min({ A_.y, B_.y, C_.y })) / 2;
  double rectWidth = std::abs(std::max({ A_.x, B_.x, C_.x }) - std::min({ A_.x, B_.x, C_.x }));
  double rectHeight = std::abs(std::max({ A_.y, B_.y, C_.y }) - std::min({ A_.y, B_.y, C_.y }));
  rectangle_t rect = { rectWidth, rectHeight, { rectPosX, rectPosY } };
  return rect;
}

void nefedev::Triangle::move(double xShift, double yShift)
{
  A_.x += xShift;
  B_.x += xShift;
  C_.x += xShift;
  A_.y += yShift;
  B_.y += yShift;
  C_.y += yShift;
}

void nefedev::Triangle::move(const point_t& newCenter)
{
  double xShift = newCenter.x - (A_.x + B_.x + C_.x) / 3;
  double yShift = newCenter.y - (A_.y + B_.y + C_.y) / 3;
  move(xShift, yShift);
}

void nefedev::Triangle::doScale(const double multiplier)
{
  double centerX = (A_.x + B_.x + C_.x) / 3;
  double centerY = (A_.y + B_.y + C_.y) / 3;
  point_t center = { centerX, centerY };
  A_.x = center.x + (A_.x - center.x) * multiplier;
  A_.y = center.y + (A_.y - center.y) * multiplier;
  B_.x = center.x + (B_.x - center.x) * multiplier;
  B_.y = center.y + (B_.y - center.y) * multiplier;
  C_.x = center.x + (C_.x - center.x) * multiplier;
  C_.y = center.y + (C_.y - center.y) * multiplier;
}
