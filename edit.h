#ifndef _EDIT_H_
#define _EDIT_H_

#include "protocol.h"

#define EDIT_SOFT_ERROR -2
#define EDIT_ERROR  -1
#define EDIT_OK      0
#define EDIT_WARN    1

#ifdef __cplusplus
extern "C"
{
#endif

int fix_ipv4_checksums(proto_ipv4_hdr *ip_hdr);
int fix_layer4_checksums(struct pcap_pkthdr *pkthdr,proto_ipv4_hdr *ip_hdr);

#ifdef __cplusplus
}
#endif

#endif
