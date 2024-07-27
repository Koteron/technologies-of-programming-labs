#include "polygon.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>
#include "stream-guard.hpp"

struct PointPolygonIO
{
  nefedev::Point point_;
};

nefedev::Point transformIOToPoint(const PointPolygonIO& proxy)
{
  return proxy.point_;
}

std::istream& nefedev::operator>>(std::istream& in, nefedev::DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, PointPolygonIO& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using sep = nefedev::DelimeterIO;
  nefedev::Point input;
  in >> sep{ ' ' } >> input;
  if (in)
  {
    dest.point_ = input;
  }
  return in;
}

std::istream& nefedev::operator>>(std::istream& in, nefedev::Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using sep = nefedev::DelimeterIO;
  nefedev::Point input;
  in >> sep{ '(' } >> input.x >> sep{';'} >> input.y >> sep{')'};
  if (in)
  {
    dest = input;
  }
  return in;
}

std::istream& nefedev::operator>>(std::istream& in, nefedev::Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t numberOfPoints = 0;
  in >> numberOfPoints;
  if (!in || numberOfPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  nefedev::StreamGuard guard(in);
  in >> std::noskipws;
  std::vector< PointPolygonIO > input = std::vector< PointPolygonIO >(numberOfPoints);
  std::copy_n(std::istream_iterator< PointPolygonIO >(in), numberOfPoints, input.begin());
  in >> nefedev::DelimeterIO{ '\n' };
  if (in)
  {
    dest.points = std::vector< nefedev::Point >(numberOfPoints);
    std::transform(input.begin(), input.end(), dest.points.begin(), transformIOToPoint);
  }
  return in;
}
