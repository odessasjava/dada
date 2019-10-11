//---------------------------------------------------------
//
//  Project:      dada
//  Module:       core
//  File:         Log.cpp
//  Author:       Viacheslav Pryshchepa
//
//---------------------------------------------------------

#include "dada/core/Log.h"
#include <iostream>

namespace dada
{

Log& operator << (Log& log, const char* str)
{
  std::cout << str;
  return log;
}

Log& operator << (Log& log, char ch)
{
  std::cout << ch;
  return log;
}

Log& operator << (Log& log, int8_t val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, uint8_t val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, int16_t val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, uint16_t val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, int32_t val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, uint32_t val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, int64_t val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, uint64_t val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, float val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, double val)
{
  std::cout << val;
  return log;
}

Log& operator << (Log& log, endl_t endl)
{
  std::cout << "\n";
  return log;
}

} // dada
