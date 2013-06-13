#include "common.h"
#include "defines.h"
#include "config.h"
#include "edit.h"
#include "protocol.h"

/**
 * this code re-calcs the IP and Layer 4 checksums
 * Returns 0 on sucess, -1 on error
 */
int
fix_ipv4_checksums(proto_ipv4_hdr *ip_hdr)
{
    int ret = 0;

    assert(ip_hdr);

    /* calc IP checksum */
    ret = do_checksum((u_char *) ip_hdr, IPPROTO_IP, ntohs(ip_hdr->ip_len));
    if (ret< 0)
        return EDIT_ERROR;

    /* what do we return? */
    if (ret == EDIT_WARN)
        return EDIT_WARN;

    return EDIT_OK;
}


int
fix_layer4_checksums(struct pcap_pkthdr *pkthdr,proto_ipv4_hdr *ip_hdr)
{
	int ret = 0;

	assert(pkthdr);
	assert(ip_hdr);
/* calc the L4 checksum if we have the whole packet && not a frag or first frag */
   if (pkthdr->caplen == pkthdr->len && (htons(ip_hdr->ip_off) & IP_OFFMASK) == 0) {
       ret = do_checksum((u_char *) ip_hdr,
               ip_hdr->ip_p, ntohs(ip_hdr->ip_len) - (ip_hdr->ip_hl << 2));
       if (ret < 0)
           return EDIT_ERROR;
   }
   else
   {
	   warn("Edit Check Sum of Layer4:the packet is not whole or it is a frag!");
	   return EDIT_WARN;
   }
}
