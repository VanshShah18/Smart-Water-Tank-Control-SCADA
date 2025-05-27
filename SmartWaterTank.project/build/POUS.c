void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  __INIT_VAR(data__->TANKLEVEL,50,retain)
  __INIT_VAR(data__->FLOWRATE,15,retain)
  __INIT_VAR(data__->CURRENTHOUR,12,retain)
  __INIT_VAR(data__->MAINTENANCEMODE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PUMPCMD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LOWFLOWALARM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OVERFLOWALARM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OFFPEAKACTIVE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PUMPENABLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TIMERINPUT,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->FLOWTIMER,retain);
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,OFFPEAKACTIVE,,((__GET_VAR(data__->CURRENTHOUR,) >= 22) || (__GET_VAR(data__->CURRENTHOUR,) < 6)));
  if ((((__GET_VAR(data__->TANKLEVEL,) < 30) && __GET_VAR(data__->OFFPEAKACTIVE,)) && !(__GET_VAR(data__->MAINTENANCEMODE,)))) {
    __SET_VAR(data__->,PUMPENABLE,,__BOOL_LITERAL(TRUE));
  };
  if ((((__GET_VAR(data__->TANKLEVEL,) > 80) || __GET_VAR(data__->MAINTENANCEMODE,)) || !(__GET_VAR(data__->OFFPEAKACTIVE,)))) {
    __SET_VAR(data__->,PUMPENABLE,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->TANKLEVEL,) > 95)) {
    __SET_VAR(data__->,PUMPENABLE,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,OVERFLOWALARM,,__BOOL_LITERAL(TRUE));
  } else {
    __SET_VAR(data__->,OVERFLOWALARM,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->,TIMERINPUT,,(__GET_VAR(data__->PUMPENABLE,) && (__GET_VAR(data__->FLOWRATE,) < 10)));
  __SET_VAR(data__->FLOWTIMER.,IN,,__GET_VAR(data__->TIMERINPUT,));
  __SET_VAR(data__->FLOWTIMER.,PT,,__time_to_timespec(1, 0, 0, 5, 0, 0));
  TON_body__(&data__->FLOWTIMER);
  __SET_VAR(data__->,LOWFLOWALARM,,__GET_VAR(data__->FLOWTIMER.Q,));
  __SET_VAR(data__->,PUMPCMD,,((__GET_VAR(data__->PUMPENABLE,) && !(__GET_VAR(data__->OVERFLOWALARM,))) && !(__GET_VAR(data__->MAINTENANCEMODE,))));

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





