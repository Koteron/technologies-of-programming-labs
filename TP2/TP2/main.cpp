#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include "data-struct.hpp"

int main()
{
  std::vector<nefedev::DataStruct> dataVector;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< nefedev::DataStruct >(std::cin),
      std::istream_iterator< nefedev::DataStruct >(),
      std::back_inserter(dataVector)
    );
    if (std::cin.rdstate() == std::ios::failbit)
    {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
  }
  std::sort(dataVector.begin(), dataVector.end());
  std::copy(
    std::begin(dataVector),
    std::end(dataVector),
    std::ostream_iterator< nefedev::DataStruct >(std::cout, "\n")
  );
  return 0;
}
