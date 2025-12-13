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





void OPENPLC_LEDFAN_init__(OPENPLC_LEDFAN *data__, BOOL retain) {
  __INIT_VAR(data__->SW1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SW2,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CR1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CR2,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CR3,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void OPENPLC_LEDFAN_body__(OPENPLC_LEDFAN *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,CR1,,(!(__GET_VAR(data__->SW2,)) && (__GET_VAR(data__->CR1,) || __GET_VAR(data__->SW1,))));
  __SET_VAR(data__->,CR2,,(!(__GET_VAR(data__->SW2,)) && (__GET_VAR(data__->CR2,) || __GET_VAR(data__->SW1,))));
  __SET_VAR(data__->,CR3,,(!(__GET_VAR(data__->SW1,)) && (__GET_VAR(data__->CR3,) || __GET_VAR(data__->SW2,))));

  goto __end;

__end:
  return;
} // OPENPLC_LEDFAN_body__() 





