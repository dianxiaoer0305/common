#ifndef _DELAY_H_
#define _DELAY_H_

#include <sys/time.h>
#include "defines.h"
#include "sleep.h"
#include "time.h"

#ifdef __cplusplus
extern "C"
{
#endif

//delay time based on a specific time.
void delay_specifictime( struct timeval *specifictime,delta_t *fortimeajust);

//delay time based on the real packet interval time.
void delay_realinterval(struct timeval *currenttimestamp, struct timeval *lasttimestamp,delta_t *fortimeajust);

//delay time based on the specific Baud rate 
void delay_specificrate(float speed,int packetlen, delta_t *fortimeajust);

#ifdef __cplusplus
}
#endif

#endif
