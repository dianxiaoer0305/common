#include "common.h"
#include "defines.h"
#include "config.h"
#include "dlt.h"
/* 
 * initialize the DLT structure, and return a new context var.
 * 
 */
void dlt_init(dlt_t **ctx)
{
    dlt_t *dlt;

    *ctx = (dlt_t *)safe_malloc(sizeof(dlt_t));
    dlt = *ctx;

    dlt->l3buff = (u_char *)safe_malloc(MAXPACKET);
    dlt->skip_broadcast = 1;
}

/* cleans up after ourselves. */
void dlt_cleanup(dlt_t *ctx)
{
    assert(ctx);

    safe_free(ctx->l3buff);      
    safe_free(ctx);

}

