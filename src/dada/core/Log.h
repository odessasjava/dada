//---------------------------------------------------------
//
//  Project:      dada
//  Module:       core
//  File:         Log.h
//  Author:       Viacheslav Pryshchepa
//
//  Description:
//
//---------------------------------------------------------

#ifndef DADA_CORE_LOG_H
#define DADA_CORE_LOG_H

#include "dada/core/common.h"

namespace dada
{

class endl_t {};
static endl_t endl;

class Log
{
};

Log& operator << (Log& log, const char* str);
Log& operator << (Log& log, char ch);
Log& operator << (Log& log, int8_t val);
Log& operator << (Log& log, uint8_t val);
Log& operator << (Log& log, int16_t val);
Log& operator << (Log& log, uint16_t val);
Log& operator << (Log& log, int32_t val);
Log& operator << (Log& log, uint32_t val);
Log& operator << (Log& log, int64_t val);
Log& operator << (Log& log, uint64_t val);
Log& operator << (Log& log, float val);
Log& operator << (Log& log, double val);
Log& operator << (Log& log, endl_t endl);

inline Log& getLog()
{
  static Log log;
  return log;
}

} // dada

#endif // DADA_CORE_LOG_H
