#include "data-struct.hpp"
#include <iostream>
#include "input-operators.hpp"
#include "stream-guard.hpp"

std::istream& nefedev::operator>>(std::istream& in, nefedev::DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  nefedev::DataStruct input;
  {
    using sep = nefedev::DelimeterIO;
    using dbl = nefedev::DoubleSciIO;
    using str = nefedev::StringIO;
    using ull = nefedev::UnsLongLongIO;
    std::string keyString = "";
    in >> sep{ '(' } >> sep{ ':'};
    for (int i = 0; i < 3; ++i)
    {
      in >> keyString;
      if (keyString == "key1")
      {
        in >> dbl{ input.key1 };
      }
      else if (keyString == "key2")
      {
        in >> ull{ input.key2 };
      }
      else if (keyString == "key3")
      {
        in >> str{ input.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
      in >> sep{ ':' };
    }
    in >> sep{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& nefedev::operator<<(std::ostream& out, const nefedev::DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  nefedev::StreamGuard fmtguard(out);
  out << "(:";
  out << "key1 ";
  double mantissa = src.key1;
  int exponent = 0;
  while ((mantissa != 0 && std::abs(mantissa) < 1) || std::abs(mantissa) >= 10)
  {
    if (std::abs(mantissa) < 1)
    {
      --exponent;
      mantissa *= 10;
    }
    else if (std::abs(mantissa) >= 10)
    {
      ++exponent;
      mantissa /= 10;
    }
  }
  out << std::fixed << std::setprecision(1) << mantissa << 'e';
  out << std::showpos << exponent;
  out << ":key2 " << src.key2 << "ull";
  out << ":key3 \"" << src.key3 << '\"';
  out << ":)";
  return out;
}

bool nefedev::operator<(const DataStruct& left, const DataStruct& right)
{
  if (left.key1 != right.key1)
  {
    return left.key1 < right.key1;
  }
  else if (left.key2 != right.key2)
  {
    return left.key2 < right.key2;
  }
  else
  {
    return left.key3.length() < right.key3.length();
  }
}
