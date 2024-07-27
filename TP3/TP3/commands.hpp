#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"
#include <iosfwd>
#include <string>
#include <numeric>
#include <functional>
#include <algorithm>

namespace nefedev
{
  class AreaFunctor
  {
  public:
    AreaFunctor(const nefedev::Polygon& polygon);
    double operator()(double sum, const nefedev::Point point);

  private:
    nefedev::Point previous_;
  };

  class RightShapesFunctor
  {
  public:
    RightShapesFunctor(const nefedev::Polygon& polygon);
    bool operator()(const nefedev::Point point);

  private:
    nefedev::Point point1_;
    nefedev::Point point2_;
  };

  void getArea(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out);
  void getMin(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out);
  void getMax(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out);
  void getCount(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out);
  void getInframe(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out);
  void getRightShapes(const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out);
  void getRects(const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out);

  double getAreaPolygon(const nefedev::Polygon& polygon);
  double getSumArea(double sum, const nefedev::Polygon& polygon);

  double getMinArea(const std::vector< nefedev::Polygon >& polygonVector);
  size_t getMinVertexes(const std::vector< nefedev::Polygon >& polygonVector);

  double getMaxArea(const std::vector< nefedev::Polygon >& polygonVector);
  size_t getMaxVertexes(const std::vector< nefedev::Polygon >& polygonVector);

  int polygonVertexSize(const nefedev::Polygon& polygon);
  bool hasCertainVertexAmount(const nefedev::Polygon& polygon, const size_t vertexNumber);

  bool isRightShape(const nefedev::Polygon& polygon);
  bool isRect(const nefedev::Polygon& polygon);

  void clearIStream(std::istream& in);
  void outInvalidCommand(std::ostream& out);
}

#endif
