#include "input-operators.hpp"
#include <iterator>
#include <iomanip>
#include <string>

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

std::istream& nefedev::operator>>(std::istream& in, nefedev::DoubleSciIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.key;
}

std::istream& nefedev::operator>>(std::istream& in, UnsLongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.key >> LabelIO{ "ull" };
}

std::istream& nefedev::operator>>(std::istream& in, nefedev::StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> nefedev::DelimeterIO{ '"' }, dest.key, '"');
}

std::istream& nefedev::operator>>(std::istream& in, nefedev::LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data = "";
  std::istream_iterator< char > iter(in);
  for (size_t i = 0; i < dest.exp.length(); ++i)
  {
    data += *iter;
    if (i != dest.exp.length() - 1)
    {
      ++iter;
    }
  }
  if (in && (data != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
