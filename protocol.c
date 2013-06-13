#include "common.h"
#include "defines.h"
#include "config.h"
#include "protocol.h"
#include "dlt.h"


proto_ipv4_hdr * _get_ipv4_header(const u_char* pktdata,const int pktlen,u_int16_t dlt)
{
    proto_ipv4_hdr *ipHdr = NULL;
	dlt_t *dataLink;

	 assert(pktdata);
     assert(pktlen);

	dlt_init(&dataLink);

	if(NULL == dataLink)
		return NULL;

	/* decode packet based on the data link type of enther 10M ,
	  * need to extend other type! parameter dlt will be used here.
	  */
	 dlt_en10mb_decode(dataLink, pktdata, pktlen);

	if(pktlen <= dataLink->l2len)
		return NULL;

#ifdef FORCE_ALIGN
    /* 
     * copy layer 3 and up to our temp packet buffer
     * for now on, we have to edit the packetbuff because
     * just before we send the packet, we copy the packetbuff 
     * back onto the pkt.data + l2len buffer
     * we do all this work to prevent byte alignment issues
     */
    if (dataLink->l2len % 4 == 0) {
        ipHdr= (proto_ipv4_hdr *)(&(pktdata)[dataLink->l2len]);
    } else {
        ipHdr= dataLink->l3buff;
        memcpy(ipHdr, (&(pktdata)[dataLink->l2len]), pktlen - dataLink->l2len);
    }
#else
    /*
     * on non-strict byte align systems, don't need to memcpy(), 
     * just point to 14 bytes into the existing buffer
     */
    ipHdr = (proto_ipv4_hdr *)(&(pktdata)[dataLink->l2len]);
#endif

	dlt_cleanup(dataLink);

    return ipHdr;
		
}

proto_ipv4_hdr * get_ipv4_header(const u_char* pktdata,const int pktlen)
{
        u_int16_t dlt = 0;
	return _get_ipv4_header(pktdata, pktlen,dlt);
}


/**
 * returns a pointer to the layer 4 header which is just beyond the IPv4 header
 */
void *
get_layer4_header(const proto_ipv4_hdr *ip_hdr)
{
    void *ptr;

    assert(ip_hdr);
    ptr = (u_int32_t *) ip_hdr + ip_hdr->ip_hl;
    return ((void *)ptr);
}

/**
* Extracts the layer 7 data from the packet for TCP, UDP, ICMP
* returns the number of bytes and a pointer to the layer 7 data.
* Returns 0 for no data
*/
int
get_application_layer_data(proto_ipv4_hdr* ip_hdr,int caplen,char *retdata)
{
	int datalen = 0; /* amount of data beyond ip header */
	proto_tcp_hdr *tcp_hdr ;
	proto_udp_hdr *udp_hdr ;
int i;
	assert(ip_hdr);
	assert(retdata);

	retdata = (char *) ip_hdr;

/*
* figure out the actual datalen which might be < the caplen
* due to ethernet padding
*/
	if (caplen > ntohs(ip_hdr->ip_len))
	{
		datalen = ntohs(ip_hdr->ip_len);
	}
	else
	{
		datalen = caplen - PROTO_802_3_H;
	}

/* update the datlen to not include the IP header len */
	datalen -= ip_hdr->ip_hl << 2;
	retdata += ip_hdr->ip_hl << 2;
	if (datalen <= 0)
		goto nodata;

/* TCP ? */
	if (ip_hdr->ip_p == IPPROTO_TCP)
	{

		tcp_hdr = (proto_tcp_hdr *) get_layer4_header(ip_hdr);
		datalen -= tcp_hdr->th_off << 2;
		if (datalen <= 0)
			goto nodata;

		retdata += tcp_hdr->th_off << 2;

	}

/* UDP ? */
	else if (ip_hdr->ip_p == IPPROTO_UDP)
	{
		udp_hdr = (proto_udp_hdr *) get_layer4_header(ip_hdr);
		datalen -= PROTO_UDP_H;
		if (datalen <= 0)
			goto nodata;

		retdata += PROTO_UDP_H;
	}

/* ICMP ? just ignore it for now */
	else if (ip_hdr->ip_p == IPPROTO_ICMP)
	{
		dbg(2, "Ignoring any possible data in ICMP packet");
		goto nodata;
	}

/* unknown proto, just dump everything past the IP header */
	else
	{
		dbg(2, "Unknown protocol, dumping everything past the IP header");
		retdata = (u_char *)ip_hdr;
	}

	dbgx(2, "packet had %d bytes of layer 7 data", datalen);
	return datalen;

nodata:
	dbg(2, "packet has no data, skipping...");
	return 0;
}
