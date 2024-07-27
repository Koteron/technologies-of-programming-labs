#include "commands.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <numeric>
#include <functional>
#include <algorithm>
#include <cmath>
#include "polygon.hpp"
#include "stream-guard.hpp"

namespace
{
  void outFalse(std::ostream& out)
  {
    out << "<FALSE>\n";
  }
  void outTrue(std::ostream& out)
  {
    out << "<TRUE>\n";
  }
  bool compPointsLessX(const nefedev::Point& point1, const nefedev::Point& point2)
  {
    return point1.x < point2.x;
  }
  bool compPointsLessY(const nefedev::Point& point1, const nefedev::Point& point2)
  {
    return point1.y < point2.y;
  }
  bool compPolygonLessXMax(const nefedev::Polygon& polygon1, const nefedev::Polygon& polygon2)
  {
    int maxX1 = std::max_element(polygon1.points.cbegin(), polygon1.points.cend(), compPointsLessX)->x;
    int maxX2 = std::max_element(polygon2.points.cbegin(), polygon2.points.cend(), compPointsLessX)->x;
    return maxX1 < maxX2;
  }
  bool compPolygonLessYMax(const nefedev::Polygon& polygon1, const nefedev::Polygon& polygon2)
  {
    int maxY1 = std::max_element(polygon1.points.cbegin(), polygon1.points.cend(), compPointsLessX)->y;
    int maxY2 = std::max_element(polygon2.points.cbegin(), polygon2.points.cend(), compPointsLessX)->y;
    return maxY1 < maxY2;
  }
  bool compPolygonLessXMin(const nefedev::Polygon& polygon1, const nefedev::Polygon& polygon2)
  {
    int minX1 = std::min_element(polygon1.points.cbegin(), polygon1.points.cend(), compPointsLessX)->x;
    int minX2 = std::min_element(polygon2.points.cbegin(), polygon2.points.cend(), compPointsLessX)->x;
    return minX1 < minX2;
  }
  bool compPolygonLessYMin(const nefedev::Polygon& polygon1, const nefedev::Polygon& polygon2)
  {
    int minY1 = std::min_element(polygon1.points.cbegin(), polygon1.points.cend(), compPointsLessX)->y;
    int minY2 = std::min_element(polygon2.points.cbegin(), polygon2.points.cend(), compPointsLessX)->y;
    return minY1 < minY2;
  }
  bool compPolygonLessArea(const nefedev::Polygon& polygon1, const nefedev::Polygon& polygon2)
  {
    double area1 = nefedev::getAreaPolygon(polygon1);
    double area2 = nefedev::getAreaPolygon(polygon2);
    return area1 < area2;
  }
  bool compPolygonLessVertexes(const nefedev::Polygon& polygon1, const nefedev::Polygon& polygon2)
  {
    return polygon1.points.size() < polygon2.points.size();
  }
}

int nefedev::polygonVertexSize(const nefedev::Polygon& polygon)
{
  return polygon.points.size();
}

bool nefedev::hasCertainVertexAmount(const nefedev::Polygon& polygon, size_t vertexNumber)
{
  return polygon.points.size() == vertexNumber;
}

void nefedev::clearIStream(std::istream& in)
{
  in.clear();
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void nefedev::outInvalidCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

nefedev::AreaFunctor::AreaFunctor(const Polygon& polygon):
  previous_(polygon.points[polygon.points.size() - 1])
{}

double nefedev::AreaFunctor::operator()(double sum, Point point)
{
  sum += (previous_.x + point.x) * (previous_.y - point.y);
  previous_ = point;
  return sum;
}

nefedev::RightShapesFunctor::RightShapesFunctor(const Polygon& polygon):
  point1_(polygon.points[polygon.points.size() - 2]),
  point2_(polygon.points[polygon.points.size() - 1])
{}

bool nefedev::RightShapesFunctor::operator()(Point point)
{
  double leg1 = std::sqrt((point2_.x - point1_.x) * (point2_.x - point1_.x) + (point2_.y - point1_.y) * (point2_.y - point1_.y));
  double leg2 = std::sqrt((point2_.x - point.x) * (point2_.x - point.x) + (point2_.y - point.y) * (point2_.y - point.y));
  double hypotenuse = std::sqrt((point.x - point1_.x) * (point.x - point1_.x) + (point.y - point1_.y) * (point.y - point1_.y));;
  bool isRight = std::sqrt(leg1 * leg1 + leg2 * leg2) == hypotenuse;
  point1_ = point2_;
  point2_ = point;
  return isRight;
}

double nefedev::getAreaPolygon(const nefedev::Polygon& polygon)
{
  AreaFunctor functor(polygon);
  double sum = std::accumulate(polygon.points.begin(), polygon.points.end(), 0, functor);
  return std::abs(sum) / 2.0;
}

double nefedev::getSumArea(double sum, const nefedev::Polygon& polygon)
{
  return sum + getAreaPolygon(polygon);
}

void nefedev::getArea(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out)
{
  std::string input = "";
  in >> input;
  double sumAll = 0.0;
  std::vector< nefedev::Polygon > filteredFigures;
  bool isMean = false;
  if (input == "EVEN")
  {
    auto hasOddVertexes = std::bind(std::bit_and< int >(), std::bind(nefedev::polygonVertexSize, std::placeholders::_1), 1);
    auto hasEvenVertexes = std::bind(std::logical_not< bool >(), std::bind(hasOddVertexes, std::placeholders::_1));
    std::copy_if(polygonVector.begin(), polygonVector.end(), std::back_inserter(filteredFigures), hasEvenVertexes);
  }
  else if (input == "ODD")
  {
    auto hasOddVertexes = std::bind(std::bit_and< int >(), std::bind(nefedev::polygonVertexSize, std::placeholders::_1), 1);
    std::copy_if(polygonVector.begin(), polygonVector.end(), std::back_inserter(filteredFigures), hasOddVertexes);
  }
  else if (input == "MEAN")
  {
    if (!polygonVector.empty())
    {
      filteredFigures = polygonVector;
      isMean = true;
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
  else
  {
    int inputNumber = std::stoi(input);
    if (inputNumber > 2)
    {
      auto hasSetVertexAmount = std::bind(hasCertainVertexAmount, std::placeholders::_1, inputNumber);
      std::copy_if(polygonVector.begin(), polygonVector.end(), std::back_inserter(filteredFigures), hasSetVertexAmount);
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
  sumAll = std::accumulate(filteredFigures.begin(), filteredFigures.end(), 0, getSumArea);
  nefedev::StreamGuard guard(out);
  out << std::fixed << std::setprecision(1);
  if (isMean)
  {
    out << sumAll / polygonVector.size() << '\n';
  }
  else
  {
    out << sumAll << '\n';
  }
}

double nefedev::getMinArea(const std::vector< nefedev::Polygon >& polygonVector)
{
  auto minPolygon = std::min_element(polygonVector.cbegin(), polygonVector.cend(), compPolygonLessArea);
  double minArea = getAreaPolygon(*minPolygon);
  return minArea;
}

size_t nefedev::getMinVertexes(const std::vector< nefedev::Polygon >& polygonVector)
{
  auto minPolygon = std::min_element(polygonVector.cbegin(), polygonVector.cend(), compPolygonLessVertexes);
  size_t minVertexes = minPolygon->points.size();
  return minVertexes;
}

void nefedev::getMin(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out)
{
  std::string input = "";
  in >> input;
  if (!polygonVector.empty() && input == "AREA")
  {
    nefedev::StreamGuard guard(out);
    out << std::fixed << std::setprecision(1);
    out << getMinArea(polygonVector) << '\n';
  }
  else if (!polygonVector.empty() && input == "VERTEXES")
  {
    out << getMinVertexes(polygonVector) << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
}

double nefedev::getMaxArea(const std::vector< nefedev::Polygon >& polygonVector)
{
  auto maxPolygon = std::max_element(polygonVector.cbegin(), polygonVector.cend(), compPolygonLessArea);
  double maxArea = getAreaPolygon(*maxPolygon);
  return maxArea;
}

size_t nefedev::getMaxVertexes(const std::vector< nefedev::Polygon >& polygonVector)
{
  auto maxPolygon = std::max_element(polygonVector.cbegin(), polygonVector.cend(), compPolygonLessVertexes);
  size_t maxVertexes = maxPolygon->points.size();
  return maxVertexes;
}

void nefedev::getMax(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out)
{
  std::string input = "";
  in >> input;
  if (!polygonVector.empty() && input == "AREA")
  {
    nefedev::StreamGuard guard(out);
    out << std::fixed << std::setprecision(1);
    out << getMaxArea(polygonVector) << '\n';
  }
  else if (!polygonVector.empty() && input == "VERTEXES")
  {
    out << getMaxVertexes(polygonVector) << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
}

void nefedev::getCount(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out)
{
  std::string input = "";
  in >> input;
  if (input == "EVEN")
  {
    auto hasOddVertexes = std::bind(std::bit_and< int >(), std::bind(nefedev::polygonVertexSize, std::placeholders::_1), 1);
    auto hasEvenVertexes = std::bind(std::logical_not< bool >(), std::bind(hasOddVertexes, std::placeholders::_1));
    out << std::count_if(polygonVector.begin(), polygonVector.end(), hasEvenVertexes) << '\n';
  }
  else if (input == "ODD")
  {
    auto hasOddVertexes = std::bind(std::bit_and< int >(), std::bind(nefedev::polygonVertexSize, std::placeholders::_1), 1);
    out << std::count_if(polygonVector.begin(), polygonVector.end(), hasOddVertexes) << '\n';
  }
  else
  {
    int inputNumber = std::stoi(input);
    if (inputNumber > 2)
    {
      auto hasCertainAmountPointsSet = std::bind(hasCertainVertexAmount, std::placeholders::_1, inputNumber);
      out << std::count_if(polygonVector.begin(), polygonVector.end(), hasCertainAmountPointsSet) << '\n';
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
}

void nefedev::getInframe(std::istream& in, const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out)
{
  nefedev::Polygon polygon;
  in >> polygon;
  if (!polygonVector.empty() && in)
  {
    auto maxXPolygon = std::max_element(polygonVector.cbegin(), polygonVector.cend(), compPolygonLessXMax);
    auto maxYPolygon = std::max_element(polygonVector.cbegin(), polygonVector.cend(), compPolygonLessYMax);
    auto minXPolygon = std::min_element(polygonVector.cbegin(), polygonVector.cend(), compPolygonLessXMin);
    auto minYPolygon = std::min_element(polygonVector.cbegin(), polygonVector.cend(), compPolygonLessYMin);
    int maxX = std::max_element(maxXPolygon->points.cbegin(), maxXPolygon->points.cend(), compPointsLessX)->x;
    int maxY = std::max_element(maxYPolygon->points.cbegin(), maxYPolygon->points.cend(), compPointsLessY)->y;
    int minX = std::min_element(minXPolygon->points.cbegin(), minXPolygon->points.cend(), compPointsLessX)->x;
    int minY = std::min_element(minYPolygon->points.cbegin(), minYPolygon->points.cend(), compPointsLessY)->y;
    auto inputXPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), compPointsLessX);
    auto inputYPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), compPointsLessY);
    if ((inputXPair.first->x < minX) || (inputXPair.second->x > maxX) || (inputYPair.first->y < minY) || (inputYPair.second->y > maxY))
    {
      outFalse(out);
    }
    else
    {
      outTrue(out);
    }
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
}

bool nefedev::isRightShape(const nefedev::Polygon& polygon)
{
  RightShapesFunctor functor(polygon);
  return std::count_if(polygon.points.begin(), polygon.points.end(), functor) > 0;
}

void nefedev::getRightShapes(const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out)
{
  out << std::count_if(polygonVector.begin(), polygonVector.end(), isRightShape) << '\n';
}

bool nefedev::isRect(const nefedev::Polygon& polygon)
{
  RightShapesFunctor functor(polygon);
  return polygon.points.size() == 4 && std::count_if(polygon.points.begin(), polygon.points.end(), functor) == 4;
}

void nefedev::getRects(const std::vector< nefedev::Polygon >& polygonVector, std::ostream& out)
{
  out << std::count_if(polygonVector.begin(), polygonVector.end(), isRect) << '\n';
}
