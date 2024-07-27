#include <iostream>
#include <string>
#include <iomanip>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "diamond.hpp"
#include "stream-guard.hpp"

using PointArray = std::unique_ptr< nefedev::point_t[] >;
using ShapePtr = std::unique_ptr< nefedev::Shape >;
using ShapeArray = std::unique_ptr< ShapePtr[] >;

namespace
{
  void addShape(ShapeArray& shapeArr, ShapePtr shape, size_t& capacity, size_t& size)
  {
    if (capacity == size)
    {
      capacity *= 2;
      ShapeArray temp = std::make_unique< ShapePtr[] >(capacity);
      for (size_t i = 0; i < size; ++i)
      {
        temp[i] = std::move(shapeArr[i]);
      }
      shapeArr = std::move(temp);
    }
    shapeArr[size] = std::move(shape);
  }

  void getPointArray(PointArray& pointArray, std::string& input)
  {
    std::string str = "\0";
    double numberArray[6];
    size_t j = 0;
    for (size_t i = 1; input[i] != '\0'; ++i)
    {
      if (input[i] != ' ')
      {
        str += input[i];
      }
      else
      {
        numberArray[j] = stod(str);
        j += 1;
        str = "\0";
      }
    }
    numberArray[j] = stod(str);
    size_t size = j / 2 + 1;
    pointArray = std::make_unique< nefedev::point_t[] >(size);
    for (size_t i = 0, m = 0; i < size; ++i, m += 2)
    {
      pointArray[i].x = numberArray[m];
      pointArray[i].y = numberArray[m + 1];
    }
  }
}

int main()
{
  std::string input;
  std::string errors = "";
  PointArray pointArray = nullptr;
  ShapeArray shapeArr = std::make_unique< ShapePtr[] >(2);
  size_t shapeArrayCapacity = 2;
  size_t shapeNumber = 0;
  double sumArea = 0;
  bool scaleCommandUsed = false;
  while (!std::cin.eof())
  {
    std::cin >> input;
    if (input == "RECTANGLE")
    {
      std::getline(std::cin, input);
      PointArray pointArr = nullptr;
      getPointArray(pointArr, input);
      try
      {
        addShape(shapeArr, std::make_unique< nefedev::Rectangle >(pointArr[0], pointArr[1]), shapeArrayCapacity, shapeNumber);
      }
      catch (const std::logic_error& err)
      {
        errors += err.what();
        continue;
      }
      sumArea += shapeArr[shapeNumber]->getArea();
      ++shapeNumber;
    }
    else if (input == "TRIANGLE")
    {
      std::getline(std::cin, input);
      PointArray pointArr = nullptr;
      getPointArray(pointArr, input);
      try
      {
        addShape(shapeArr, std::make_unique< nefedev::Triangle >(pointArr[0], pointArr[1], pointArr[2]), shapeArrayCapacity, shapeNumber);
      }
      catch (const std::logic_error& err)
      {
        errors += err.what();
        continue;
      }
      sumArea += shapeArr[shapeNumber]->getArea();
      ++shapeNumber;
    }
    else if (input == "DIAMOND")
    {
      std::getline(std::cin, input);
      PointArray pointArr = nullptr;
      getPointArray(pointArr, input);
      try
      {
        addShape(shapeArr, std::make_unique< nefedev::Diamond >(pointArr[0], pointArr[1], pointArr[2]), shapeArrayCapacity, shapeNumber);
      }
      catch (const std::logic_error& err)
      {
        errors += err.what();
        continue;
      }
      sumArea += shapeArr[shapeNumber]->getArea();
      ++shapeNumber;
    }
    else if (input == "SCALE")
    {
      if (shapeNumber == 0)
      {
        std::cerr << "There are no shapes to scale\n" << errors;
        return 1;
      }
      std::getline(std::cin, input);
      input.erase(0, 1);
      double multiplier = std::stod(input.substr(input.rfind(' '), input.length()));
      nefedev::point_t scaleCenter;
      scaleCenter.x = std::stod(input.substr(0, input.find(' ')));
      scaleCenter.y = std::stod(input.substr(input.find(' '), input.rfind(' ')));
      nefedev::StreamGuard guard(std::cout);
      std::cout.precision(1);
      std::cout << std::fixed << sumArea;
      try
      {
        for (size_t i = 0; i < shapeNumber; ++i)
        {
          std::cout << ' ' << shapeArr[i]->getFrameRect();
          nefedev::point_t frameCenter1 = shapeArr[i]->getFrameRect().pos;
          shapeArr[i]->move(scaleCenter);
          nefedev::point_t frameCenter2 = shapeArr[i]->getFrameRect().pos;
          shapeArr[i]->scale(multiplier);
          shapeArr[i]->move((frameCenter1.x - frameCenter2.x) * multiplier, (frameCenter1.y - frameCenter2.y) * multiplier);
        }
      }
      catch (const std::logic_error& err)
      {
        std::cerr << err.what();
        return 1;
      }
      sumArea *= multiplier * multiplier;
      std::cout << '\n' << sumArea;
      for (size_t i = 0; i < shapeNumber; ++i)
      {
        std::cout << ' ' << shapeArr[i]->getFrameRect();
      }
      scaleCommandUsed = true;
    }
  }
  std::cout << '\n';
  std::cerr << errors;
  if (!scaleCommandUsed)
  {
    std::cerr << "There was no scale command\n";
    return 1;
  }
  return 0;
}
