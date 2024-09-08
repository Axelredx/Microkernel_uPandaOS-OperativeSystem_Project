/* Support level exception*/
#ifndef SYSSUPPORT_H
#define SYSSUPPORT_H

#include "sst.h"

/*function to handle program trap exception*/
void programTrapExceptionHandler(state_t *exception_state);
/*pussed up exception handling*/
void supportExceptionHandler(void);
/*wrapper syscall handler for user process*/
void UsysCallHandler(state_t* exception_state, int asid);

#endif