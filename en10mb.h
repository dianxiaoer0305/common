/*
 */

#ifndef _DLT_en10mb_H_
#define _DLT_en10mb_H_
#include "protocol.h"

#ifdef __cplusplus
extern "C"
{
#endif

int dlt_en10mb_decode(dlt_t *ctx, const u_char *packet, const int pktlen);

#ifdef __cplusplus
}
#endif

#endif

