#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "config.h"

/* should packet counters be 32 or 64 bit? --enable-64bit */
#ifdef ENABLE_64BITS
#define COUNTER unsigned long long
#define COUNTER_SPEC "%llu"
#else
#define COUNTER unsigned long
#define COUNTER_SPEC "%lu"
#endif


#ifdef HAVE_BPF
#include <net/bpf.h>
#define PCAP_DONT_INCLUDE_PCAP_BPF_H 1
#endif

#if defined INCLUDE_PCAP_BPF_H_FILE && !defined PCAP_DONT_INCLUDE_PCAP_BPF_H
#include "/usr/local/include/pcap/bpf.h"
#define PCAP_DONT_INCLUDE_PCAP_BPF_H 1 /* don't re-include it in pcap.h */
#endif

#include "/usr/local/include/pcap.h"

#define PCAP_TIMEOUT 100        /* 100ms pcap_open_live timeout */

/* struct timeval print structs */
#ifdef HAVE_DARWIN
/* Darwin defines usec as an __int32_t, not unsigned long. */
#define TIMEVAL_FORMAT "%lus %dusec"
#else
#define TIMEVAL_FORMAT "%lus %luusec"
#endif
#define TIMESPEC_FORMAT "%lus %lunsec"


#ifndef HAVE_UINT8_T
typedef u_int8_t uint8_t
typedef u_int16_t uint16_t
typedef u_int32_t uint32_t
#endif

/* Time converters */
#define SEC_TO_MILLISEC(x) (x * 1000)
#define SEC_TO_MICROSEC(x) (x * 1000000)
#define SEC_TO_NANOSEC(x)  ((u_int64_t)x * 1000000000)

#define MILLISEC_TO_SEC(x) (x / 1000)
#define MICROSEC_TO_SEC(x) (x / 1000000)
#define NANOSEC_TO_SEC(x)  ((u_int64_t)x / 1000000000)

#define TIMEVAL_TO_MILLISEC(x)  (((x)->tv_sec * 1000) + ((x)->tv_usec / 1000))
#define TIMEVAL_TO_MICROSEC(x)  (((x)->tv_sec * 1000000) + (x)->tv_usec)
#define TIMEVAL_TO_NANOSEC(x)   ((u_int64_t)((x)->tv_sec * 1000000000) + ((u_int64_t)(x)->tv_usec * 1000))

#define MILLISEC_TO_TIMEVAL(x, tv)          \
    do {                                    \
        (tv)->tv_sec = (x) / 1000;          \
        (tv)->tv_usec = (x * 1000) - ((tv)->tv_sec * 1000000);   \
    } while(0)
    
#define MICROSEC_TO_TIMEVAL(x, tv)          \
    do {                                    \
        (tv)->tv_sec = (x) / 1000000;       \
        (tv)->tv_usec = (x) - ((tv)->tv_sec * 1000000);   \
    } while(0)

#define NANOSEC_TO_TIMEVAL(x, tv)           \
    do {                                    \
        (tv)->tv_sec =  (x) / 1000000000;   \
        (tv)->tv_usec = ((x) % 1000000000) / 1000);   \
    } while(0)

#define NANOSEC_TO_TIMESPEC(x, ts)          \
    do {                                    \
        (ts)->tv_sec = (x) / 1000000000;    \
        (ts)->tv_nsec = (x) % 1000000000;   \
    } while(0)

#define TIMESPEC_TO_MILLISEC(x)  (((x)->tv_sec * 1000) + ((x)->tv_nsec / 1000000))
#define TIMESPEC_TO_MICROSEC(x)  (((x)->tv_sec * 1000000) + (x)->tv_nsec / 1000)
#define TIMESPEC_TO_NANOSEC(x) ((u_int64_t)((x)->tv_sec * 1000000000) + ((u_int64_t)(x)->tv_nsec))

#define MAXPACKET 65535         /* was 16436 linux loopback, but maybe something is bigger than linux loopback */

#endif /* DEFINES */
