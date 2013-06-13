/*
 * This code is heavily based on (some might even say stolen from) Mike Shiffman's 
 * checksumming code from Libnet 1.1.3
 */
 
#include "config.h"
#include "defines.h"
#include "common.h"
#include "protocol.h"
#include "edit.h"
#include "checksum.h"

static int do_checksum_math(u_int16_t *, int);

/**
 * Returns -1 on error and 0 on success, 1 on warn
 * Note: support for TCP,UDP,IP,ICMP,ICMP6
 */
int
do_checksum( u_int8_t *data, int proto, int len) {
    proto_ipv4_hdr *ipv4;
    proto_ipv6_hdr *ipv6;
    proto_tcp_hdr *tcp;
    proto_udp_hdr *udp;
    proto_icmpv4_hdr *icmp;
    proto_icmpv6_hdr *icmp6;
    int ip_hl;
    int sum;
    
    sum = 0;
    ipv4 = NULL;
    ipv6 = NULL;
    assert(data);
    
    if (len <= 0) {
        warn("CheckSum:length of data must be > 0");
        return EDIT_ERROR;
    }
    
    ipv4 = (proto_ipv4_hdr *)data;
    if (ipv4->ip_v == 6) {
    	//need to extend supporting ipv6
    	warn("CheckSum:not support ipv6 now! ");
    	return EDIT_WARN;
    	/*ipv6 = (ipv6_hdr_t *)data;
    	ipv4 = NULL;

    	proto = get_ipv6_l4proto(ipv6);
    	dbgx(3, "layer4 proto is 0x%hhu", proto);

        ip_hl = (u_char*)get_layer4_v6(ipv6) - (u_char*)data;
    	dbgx(3, "ip_hl proto is 0x%d", ip_hl);

    	len -= (ip_hl - TCPR_IPV6_H);*/
    } else {
        ip_hl = ipv4->ip_hl << 2;
    }
    
    switch (proto) {
        
        case IPPROTO_TCP:
            tcp = (proto_tcp_hdr *)(data + ip_hl);
#ifdef STUPID_SOLARIS_CHECKSUM_BUG
            tcp->th_sum = tcp->th_off << 2;
            return (EDIT_OK);
#endif
            tcp->th_sum = 0;
            
            /* Note, we do both src & dst IP's at the same time, that's why the
             * length is 2x a single IP
             */
            if (ipv6 != NULL) {
                //can not get here now!
            	 sum = do_checksum_math((u_int16_t *)&ipv6->ip_src, 32);
            } else {
                sum = do_checksum_math((u_int16_t *)&ipv4->ip_src, 8);
            }
            sum += ntohs(IPPROTO_TCP + len);
            sum += do_checksum_math((u_int16_t *)tcp, len);
            tcp->th_sum = CHECKSUM_CARRY(sum);
            break;
        
        case IPPROTO_UDP:
            udp = (proto_udp_hdr *)(data + ip_hl);
            udp->uh_sum = 0;
            if (ipv6 != NULL) {
                sum = do_checksum_math((u_int16_t *)&ipv6->ip_src, 32);
            } else {
                sum = do_checksum_math((u_int16_t *)&ipv4->ip_src, 8);
            }
            sum += ntohs(IPPROTO_UDP + len);
            sum += do_checksum_math((u_int16_t *)udp, len);
            udp->uh_sum = CHECKSUM_CARRY(sum);
            break;
        
        case IPPROTO_ICMP:
            icmp = (proto_icmpv4_hdr *)(data + ip_hl);
            icmp->icmp_sum = 0;
            if (ipv6 != NULL) {
                sum = do_checksum_math((u_int16_t *)&ipv6->ip_src, 32);
                icmp->icmp_sum = CHECKSUM_CARRY(sum);                
            }
            sum += do_checksum_math((u_int16_t *)icmp, len);
            icmp->icmp_sum = CHECKSUM_CARRY(sum);
            break;
        
        case IPPROTO_ICMP6:
            icmp6 = (proto_icmpv6_hdr *)(data + ip_hl);
            icmp6->icmp_sum = 0;
            if (ipv6 != NULL) {
                sum = do_checksum_math((u_int16_t *)&ipv6->ip_src, 32);
            }
            sum += ntohs(IPPROTO_ICMP6 + len);
            sum += do_checksum_math((u_int16_t *)icmp6, len);
            icmp6->icmp_sum = CHECKSUM_CARRY(sum);
            break;

     
        case IPPROTO_IP:
            ipv4->ip_sum = 0;
            sum = do_checksum_math((u_int16_t *)data, ip_hl);
            ipv4->ip_sum = CHECKSUM_CARRY(sum);
            break;
       
       
        case IPPROTO_IGMP:
        case IPPROTO_GRE:
        default:
            warnx("CheckSum:Unsupported protocol for checksum: 0x%x", proto);
            return EDIT_WARN;
    }
    
    return EDIT_OK;
}

/**
 * code to do a ones-compliment checksum
 */
static int
do_checksum_math(u_int16_t *data, int len)
{
    int sum = 0;
    union {
        u_int16_t s;
        u_int8_t b[2];
    } pad;
    
    while (len > 1) {
        sum += *data++;
        len -= 2;
    }
    
    if (len == 1) {
        pad.b[0] = *(u_int8_t *)data;
        pad.b[1] = 0;
        sum += pad.s;
    }
    
    return (sum);
}

