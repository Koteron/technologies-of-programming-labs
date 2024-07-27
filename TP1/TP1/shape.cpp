#include "shape.hpp"
#include <stdexcept>

void nefedev::Shape::scale(const double multiplier)
{
  if (multiplier <= 0)
  {
    throw std::logic_error("Scale multiplier can't be negative\n");
  }
  doScale(multiplier);
}
