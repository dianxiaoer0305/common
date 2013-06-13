#ifndef _DLT_H_
#define _DLT_H_
#include "protocol.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* 
 * initialize the DLT structure, and return a new context var.
 * 
 */
void dlt_init(dlt_t **ctx);

/* cleans up after ourselves. */
void dlt_cleanup(dlt_t *ctx);

#ifdef __cplusplus
}
#endif

#endif
