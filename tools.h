#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "timer.h"
#include "delay.h"
#include "en10mb.h"
#include "utils.h"
#include "protocol.h"
#include "/usr/local/include/pcap.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//one packet entity of pcap 
struct packet_s
{
    u_char * pktdata;
    struct pcap_pkthdr *pkthdr;
};
typedef struct packet_s packet_t;

#ifdef __cplusplus
extern "C"
{
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// time delay

//delay time based on a specific time.
void delay_specifictime( struct timeval *specifictime,delta_t *fortimeajust);

//delay time based on the real packet interval time.
void delay_realinterval(struct timeval *currenttimestamp, struct timeval *lasttimestamp,delta_t *fortimeajust);

//delay time based on the specific Baud rate 
void delay_specificrate(float speed,int packetlen, delta_t *fortimeajust);


/*
 * starts a timer so we can figure out how much time has passed
 * when we call get_delta_timer()
 */
static inline void
start_delta_time(delta_t *ctx);

/*
 * returns the amount of time that has passed since the 
 * last time you called start_delta_time()
 */
static inline void
get_delta_time(delta_t *ctx, struct timespec *ret);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//packet edit

//decode the enther 10mb packet
int dlt_en10mb_decode(dlt_t *ctx, const u_char *packet, const int pktlen);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//"safe" implimentations of functions which allocate memory


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//Functions for editing packet.

proto_ipv4_hdr * get_ipv4_header(const u_char* pktdata,const int pktlen);

void * get_layer4_header(const proto_ipv4_hdr *ip_hdr);

int get_application_layer_data(proto_ipv4_hdr* ip_hdr,int caplen,char *retdata);

int fix_ipv4_checksums(proto_ipv4_hdr *ip_hdr);

int fix_layer4_checksums(struct pcap_pkthdr *pkthdr,proto_ipv4_hdr *ip_hdr);

/////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#endif
