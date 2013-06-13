
/*
 */

#include <stdlib.h>
#include <string.h>

#include "en10mb.h"
#include "common.h"
#include "edit.h"
#include "dlt.h"


/*
 * Function: 
 * Return: EDIT_ERROR | EDIT_OK | EDIT_WARN
 * Parameter:  
 */
int 
dlt_en10mb_decode(dlt_t *ctx, const u_char *packet, const int pktlen)
{
    
    struct ethernet_hdr *eth = NULL;
    u_char *ptr;
    
    assert(ctx);
    assert(packet);
    assert(pktlen >= 14);

    /* get our src & dst address */
    eth = (struct ethernet_hdr *)packet;
    memcpy(&(ctx->ether_dhost), eth, ETHER_ADDR_LEN);
    memcpy(&(ctx->ether_shost), &(eth->ether_shost), ETHER_ADDR_LEN); 
    /* get the L3 protocol type  & L2 len*/
    ctx->proto = ntohs(eth->ether_type);
    ctx->l2len = PROTO_802_3_H;

	if (pktlen > ctx->l2len)
	{
            ptr = ctx->l3buff;
            memcpy(ptr, (&(packet)[ctx->l2len]), pktlen - ctx->l2len);
	}

    return EDIT_OK; /* success */
}


