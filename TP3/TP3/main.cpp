#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <vector>
#include <string>
#include <iterator>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "Too few arguments!\n";
    return 1;
  }
  std::string input = argv[1];
  std::ifstream in;
  in.open(input);
  std::vector< nefedev::Polygon > polygonVector;
  while (!in.eof())
  {
    std::copy(std::istream_iterator< nefedev::Polygon >(in),
      std::istream_iterator< nefedev::Polygon >(),
      std::back_inserter(polygonVector));
    if (!in)
    {
      nefedev::clearIStream(in);
    }
  }
  std::map< std::string, std::function< void() > > commands(
    {
      {"AREA", std::bind(nefedev::getArea, std::ref(std::cin), std::cref(polygonVector), std::ref(std::cout))},
      {"MAX", std::bind(nefedev::getMax, std::ref(std::cin), std::cref(polygonVector), std::ref(std::cout))},
      {"MIN", std::bind(nefedev::getMin, std::ref(std::cin), std::cref(polygonVector), std::ref(std::cout))},
      {"COUNT", std::bind(nefedev::getCount, std::ref(std::cin), std::cref(polygonVector), std::ref(std::cout))},
      {"INFRAME", std::bind(nefedev::getInframe, std::ref(std::cin), std::cref(polygonVector), std::ref(std::cout))},
      {"RIGHTSHAPES", std::bind(nefedev::getRightShapes, std::cref(polygonVector), std::ref(std::cout))},
      {"RECTS", std::bind(nefedev::getRects, std::cref(polygonVector), std::ref(std::cout))},
    });
  while (!std::cin.eof())
  {
    input = "";
    std::cin >> input;
    if (!input.empty())
    {
      try
      {
        commands.at(input)();
      }
      catch (...)
      {
        nefedev::outInvalidCommand(std::cout);
        nefedev::clearIStream(std::cin);
      }
    }
  }
  return 0;
}
