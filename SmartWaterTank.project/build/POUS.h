#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// PROGRAM PROGRAM0
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,TANKLEVEL)
  __DECLARE_VAR(INT,FLOWRATE)
  __DECLARE_VAR(INT,CURRENTHOUR)
  __DECLARE_VAR(BOOL,MAINTENANCEMODE)
  __DECLARE_VAR(BOOL,PUMPCMD)
  __DECLARE_VAR(BOOL,LOWFLOWALARM)
  __DECLARE_VAR(BOOL,OVERFLOWALARM)
  __DECLARE_VAR(BOOL,OFFPEAKACTIVE)
  __DECLARE_VAR(BOOL,PUMPENABLE)
  __DECLARE_VAR(BOOL,TIMERINPUT)
  TON FLOWTIMER;

} PROGRAM0;

void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain);
// Code part
void PROGRAM0_body__(PROGRAM0 *data__);
#endif //__POUS_H
