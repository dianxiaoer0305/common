#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_ 

#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>

#define ETHER_ADDR_LEN 0x6

/**
 * Libnet defines header sizes for every builder function exported.
 */
#define PROTO_802_1Q_H         0x12    /**< 802.1Q header:       18 bytes */
#define PROTO_802_1X_H         0x04    /**< 802.1X header:        4 bytes */
#define PROTO_802_2_H          0x03    /**< 802.2 LLC header:     3 bytes */
#define PROTO_802_2SNAP_H      0x08    /**< 802.2 LLC/SNAP header:8 bytes */
#define PROTO_802_3_H          0x0e    /**< 802.3 header:        14 bytes */
#define PROTO_ARP_H            0x08    /**< ARP header w/o addrs: 8 bytes */
#define PROTO_ARP_ETH_IP_H     0x1c    /**< ARP w/ ETH and IP:   28 bytes */
#define PROTO_BGP4_HEADER_H    0x13    /**< BGP header:          19 bytes */
#define PROTO_BGP4_OPEN_H      0x0a    /**< BGP open header:     10 bytes */
#define PROTO_BGP4_UPDATE_H    0x04    /**< BGP open header:      4 bytes */
#define PROTO_BGP4_NOTIFICATION_H 0x02 /**< BGP notif. header:    2 bytes */
#define PROTO_CDP_H            0x08    /**< CDP header base:      8 bytes */
#define PROTO_DHCPV4_H         0xf0    /**< DHCP v4 header:     240 bytes */
#define PROTO_UDP_DNSV4_H      0x0c    /**< UDP DNS v4 header:   12 bytes */
#define PROTO_TCP_DNSV4_H      0x0e    /**< TCP DNS v4 header:   14 bytes */
#define PROTO_ETH_H            0x0e    /**< Ethernet header:     14 bytes */
#define PROTO_ETH_MTU          1500    /**< Ethernet MTU size: 1500 bytes */
#define PROTO_FDDI_H           0x15    /**< FDDI header:         21 bytes */
#define PROTO_ICMPV4_H         0x04    /**< ICMP header base:     4 bytes */
#define PROTO_ICMPV4_ECHO_H    0x08    /**< ICMP_ECHO header:     8 bytes */
#define PROTO_ICMPV4_MASK_H    0x0c    /**< ICMP_MASK header:    12 bytes */
#define PROTO_ICMPV4_UNREACH_H  0x08   /**< ICMP_UNREACH header:  8 bytes */
#define PROTO_ICMPV4_TIMXCEED_H 0x08   /**< ICMP_TIMXCEED header: 8 bytes */
#define PROTO_ICMPV4_REDIRECT_H 0x08   /**< ICMP_REDIRECT header: 8 bytes */
#define PROTO_ICMPV4_TS_H      0x14    /**< ICMP_TIMESTAMP headr:20 bytes */
#define PROTO_ICMPV6_H         0x08    /**< ICMP6 header base:    8 bytes */
#define PROTO_IGMP_H           0x08    /**< IGMP header:          8 bytes */
#define PROTO_IPV4_H           0x14    /**< IPv4 header:         20 bytes */
#define PROTO_IPV6_H           0x28    /**< IPv6 header:         40 bytes */
#define PROTO_IPV6_FRAG_H      0x08    /**< IPv6 frag header:     8 bytes */
#define PROTO_IPV6_ROUTING_H   0x04    /**< IPv6 frag header base:4 bytes */
#define PROTO_IPV6_DESTOPTS_H  0x02    /**< IPv6 dest opts base:  2 bytes */
#define PROTO_IPV6_HBHOPTS_H   0x02    /**< IPv6 hop/hop opt base:2 bytes */
#define PROTO_IPSEC_ESP_HDR_H  0x0c    /**< IPSEC ESP header:    12 bytes */
#define PROTO_IPSEC_ESP_FTR_H  0x02    /**< IPSEC ESP footer:     2 bytes */
#define PROTO_IPSEC_AH_H       0x10    /**< IPSEC AH header:     16 bytes */
#define PROTO_ISL_H            0x1a    /**< ISL header:          26 bytes */
#define PROTO_GRE_H            0x04    /**< GRE header:           4 bytes */
#define PROTO_GRE_SRE_H        0x04    /**< GRE SRE header:       4 bytes */
#define PROTO_MPLS_H           0x04    /**< MPLS header:          4 bytes */
#define PROTO_OSPF_H           0x10    /**< OSPF header:         16 bytes */
#define PROTO_OSPF_HELLO_H     0x18    /**< OSPF hello header:   24 bytes */
#define PROTO_OSPF_DBD_H       0x08    /**< OSPF DBD header:      8 bytes */
#define PROTO_OSPF_LSR_H       0x0c    /**< OSPF LSR header:     12 bytes */
#define PROTO_OSPF_LSU_H       0x04    /**< OSPF LSU header:      4 bytes */
#define PROTO_OSPF_LSA_H       0x14    /**< OSPF LSA header:     20 bytes */
#define PROTO_OSPF_AUTH_H      0x08    /**< OSPF AUTH header:     8 bytes */
#define PROTO_OSPF_CKSUM       0x10    /**< OSPF CKSUM header:   16 bytes */
#define PROTO_OSPF_LS_RTR_H    0x10    /**< OSPF LS RTR header:  16 bytes */
#define PROTO_OSPF_LS_NET_H    0x08    /**< OSPF LS NET header:   8 bytes */
#define PROTO_OSPF_LS_SUM_H    0x0c    /**< OSPF LS SUM header:  12 bytes */
#define PROTO_OSPF_LS_AS_EXT_H 0x10    /**< OSPF LS AS header:   16 bytes */
#define PROTO_NTP_H            0x30    /**< NTP header:          48 bytes */
#define PROTO_RIP_H            0x18    /**< RIP header base:     24 bytes */
#define PROTO_RPC_CALL_H       0x28    /**< RPC header:          40 bytes
                                         * (assuming 8 byte auth header)
                                         */
#define PROTO_RPC_CALL_TCP_H   0x2c    /**< RPC header:          44 bytes
                                         * (with record marking)
                                         */
#define PROTO_SEBEK_H          0x30    /* sebek header:          48 bytes */   
#define PROTO_STP_CONF_H       0x23    /**< STP conf header:     35 bytes */
#define PROTO_STP_TCN_H        0x04    /**< STP tcn header:       4 bytes */
#define PROTO_TOKEN_RING_H     0x16    /**< Token Ring header:   22 bytes */
#define PROTO_TCP_H            0x14    /**< TCP header:          20 bytes */
#define PROTO_UDP_H            0x08    /**< UDP header:           8 bytes */
#define PROTO_VRRP_H           0x08    /**< VRRP header:          8 bytes */
#define PROTO_HSRP_H           0x14    /**< HSRP header:          8 bytes */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//layer 2

/*
 *  Ethernet II header
 *  Static header size: 14 bytes
 */
struct ethernet_hdr
{
    u_int8_t  ether_dhost[ETHER_ADDR_LEN];/* destination ethernet address */
    u_int8_t  ether_shost[ETHER_ADDR_LEN];/* source ethernet address */
    u_int16_t ether_type;                 /* protocol */
};


#define ETHERTYPE_PUP           0x0200  /* PUP protocol */
#define ETHERTYPE_IP            0x0800  /* IP protocol */
#define ETHERTYPE_ARP           0x0806  /* addr. resolution protocol */
#define ETHERTYPE_REVARP        0x8035  /* reverse addr. resolution protocol */
#define ETHERTYPE_VLAN          0x8100  /* IEEE 802.1Q VLAN tagging */
#define ETHERTYPE_EAP           0x888e  /* IEEE 802.1X EAP authentication */
#define ETHERTYPE_MPLS          0x8847  /* MPLS */
#define ETHERTYPE_LOOPBACK      0x9000  /* used to test interfaces */
#define ETHERTYPE_IP6           0x86DD /* IPv6 */

/*
 *  data link layer 
 */
struct proto_dlt_s {
    u_char *l3buff;                     /* pointer for L3 buffer on strictly aligned systems */

	/* skip rewriting IP/MAC's which are broadcast or multicast? */
    int skip_broadcast;
    int l2len;                              /* set by decoder and updated by encoder */
    u_int8_t  ether_dhost[ETHER_ADDR_LEN];/* destination ethernet address */
    u_int8_t  ether_shost[ETHER_ADDR_LEN];/* source ethernet address */
    u_int16_t proto;                      /* protocol */
    
};
typedef struct proto_dlt_s dlt_t;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//layer 3

/* 
 *  ARP header
 *  Address Resolution Protocol
 *  Base header size: 8 bytes
 */
struct proto_arp_hdr
{
    u_int16_t ar_hrd;         /* format of hardware address */
#define ARPHRD_NETROM   0   /* from KA9Q: NET/ROM pseudo */
#define ARPHRD_ETHER    1   /* Ethernet 10Mbps */
#define ARPHRD_EETHER   2   /* Experimental Ethernet */
#define ARPHRD_AX25     3   /* AX.25 Level 2 */
#define ARPHRD_PRONET   4   /* PROnet token ring */
#define ARPHRD_CHAOS    5   /* Chaosnet */
#define ARPHRD_IEEE802  6   /* IEEE 802.2 Ethernet/TR/TB */
#define ARPHRD_ARCNET   7   /* ARCnet */
#define ARPHRD_APPLETLK 8   /* APPLEtalk */
#define ARPHRD_LANSTAR  9   /* Lanstar */
#define ARPHRD_DLCI     15  /* Frame Relay DLCI */
#define ARPHRD_ATM      19  /* ATM */
#define ARPHRD_METRICOM 23  /* Metricom STRIP (new IANA id) */
#define ARPHRD_IPSEC    31  /* IPsec tunnel */
    u_int16_t ar_pro;         /* format of protocol address */
    u_int8_t  ar_hln;         /* length of hardware address */
    u_int8_t  ar_pln;         /* length of protocol addres */
    u_int16_t ar_op;          /* operation type */
#define ARPOP_REQUEST    1  /* req to resolve address */
#define ARPOP_REPLY      2  /* resp to previous request */
#define ARPOP_REVREQUEST 3  /* req protocol address given hardware */
#define ARPOP_REVREPLY   4  /* resp giving protocol address */
#define ARPOP_INVREQUEST 8  /* req to identify peer */
#define ARPOP_INVREPLY   9  /* resp identifying peer */
    /* address information allocated dynamically */
};



/*
 *  IPv4 header
 *  Internet Protocol, version 4
 *  Static header size: 20 bytes
 */
struct _proto_ipv4_hdr
{
    u_int8_t ip_hl:4,        /* version */
    ip_v:4;                /* header length */
    u_int8_t ip_tos;       /* type of service */
#define IPTOS_LOWDELAY      0x10
#define IPTOS_THROUGHPUT    0x08
#define IPTOS_RELIABILITY   0x04
#define IPTOS_LOWCOST       0x02

    u_int16_t ip_len;         /* total length */
    u_int16_t ip_id;          /* identification */
    u_int16_t ip_off;
#define IP_RF 0x8000        /* reserved fragment flag */
#define IP_DF 0x4000        /* dont fragment flag */
#define IP_MF 0x2000        /* more fragments flag */
#define IP_OFFMASK 0x1fff   /* mask for fragmenting bits */

    u_int8_t ip_ttl;          /* time to live */
    u_int8_t ip_p;            /* protocol */
    u_int16_t ip_sum;         /* checksum */
    struct in_addr ip_src, ip_dst; /* source and dest address */
};

typedef struct _proto_ipv4_hdr proto_ipv4_hdr;

/*
 *  IP options
 */
#define IPOPT_EOL       0   /* end of option list */
#define IPOPT_NOP       1   /* no operation */ 
#define IPOPT_RR        7   /* record packet route */
#define IPOPT_TS        68  /* timestamp */
#define IPOPT_SECURITY  130 /* provide s,c,h,tcc */ 
#define IPOPT_LSRR      131 /* loose source route */
#define IPOPT_SATID     136 /* satnet id */
#define IPOPT_SSRR      137 /* strict source route */

struct proto_in6_addr
{
    union
    {
        u_int8_t   __u6_addr8[16];
        u_int16_t  __u6_addr16[8];
        u_int32_t  __u6_addr32[4];
    } __u6_addr;            /* 128-bit IP6 address */
};
#define proto_s6_addr __u6_addr.__u6_addr8
#define proto_s6_addr8 __u6_addr.__u6_addr8
#define proto_s6_addr16 __u6_addr.__u6_addr16
#define proto_s6_addr32 __u6_addr.__u6_addr32

/*
 *  IPv6 header
 *  Internet Protocol, version 6
 *  Static header size: 40 bytes
 */
struct _proto_ipv6_hdr
{
    u_int8_t ip_flags[4];     /* version, traffic class, flow label */
    u_int16_t ip_len;         /* total length */
    u_int8_t ip_nh;           /* next header */
    u_int8_t ip_hl;           /* hop limit */
    struct proto_in6_addr ip_src, ip_dst; /* source and dest address */
};
typedef struct _proto_ipv6_hdr proto_ipv6_hdr;

struct proto_ipv6_ext_hdr_base
{
    u_int8_t ip_nh;          /* next header */
    u_int8_t ip_len;         /* length of header in 8 octet units (sans 1st) */
    /* some more bytes are always here, but we don't know what kind */
};

#define PROTO_IPV6_NH_NO_NEXT 59
#define PROTO_IPV6_NH_IPV6    41
#define PROTO_IPV6_NH_ESP     50
#define PROTO_IPV6_NH_AH      51

/*
 *  IPv6 frag header
 *  Internet Protocol, version 6
 *  Static header size: 8 bytes
 */
#define PROTO_IPV6_NH_FRAGMENT 44
struct proto_ipv6_frag_hdr
{
    u_int8_t ip_nh;          /* next header */
    u_int8_t ip_reserved;    /* reserved */
    u_int16_t ip_frag;       /* fragmentation stuff */
    u_int32_t ip_id;         /* id */
};

/*
 *  IPv6 routing header
 *  Internet Protocol, version 6
 *  Base header size: 4 bytes
 */
#define PROTO_IPV6_NH_ROUTING  43
struct proto_ipv6_routing_hdr
{
    u_int8_t ip_nh;          /* next header */
    u_int8_t ip_len;         /* length of header in 8 octet units (sans 1st) */
    u_int8_t ip_rtype;       /* routing type */
    u_int8_t ip_segments;    /* segments left */
    /* routing information allocated dynamically */
};  


/*
 *  IPv6 destination options header
 *  Internet Protocol, version 6
 *  Base header size: 2 bytes
 */
#define PROTO_IPV6_NH_DESTOPTS 60
struct proto_ipv6_destopts_hdr
{
    u_int8_t ip_nh;          /* next header */
    u_int8_t ip_len;         /* length of header in 8 octet units (sans 1st) */
    /* destination options information allocated dynamically */
};

/*
 *  IPv6 hop by hop options header
 *  Internet Protocol, version 6
 *  Base header size: 2 bytes
 */
#define PROTO_IPV6_NH_HBH      0
struct proto_ipv6_hbhopts_hdr
{
    u_int8_t ip_nh;          /* next header */
    u_int8_t ip_len;         /* length of header in 8 octet units (sans 1st) */
    /* destination options information allocated dynamically */
};

/*
 *  ICMP6 header
 *  Internet Control Message Protocol v6
 *  Base header size: 8 bytes
 */
#define IPPROTO_ICMP6   0x3a

struct _proto_icmpv6_hdr
{
    u_int8_t icmp_type;       /* ICMP type */

#define ICMP6_ECHO          128
#define ICMP6_ECHOREPLY     129
#define ICMP6_UNREACH       1
#define ICMP6_PKTTOOBIG     2
#define ICMP6_TIMXCEED      3
#define ICMP6_PARAMPROB     4
    u_int8_t icmp_code;       /* ICMP code */
    u_int16_t icmp_sum;       /* ICMP Checksum */
    u_int16_t id;             /* ICMP id */
    u_int16_t seq;            /* ICMP sequence number */
};
typedef struct _proto_icmpv6_hdr proto_icmpv6_hdr;


/*
 *  ICMP header
 *  Internet Control Message Protocol
 *  Base header size: 4 bytes
 */
struct _proto_icmpv4_hdr
{
    u_int8_t icmp_type;       /* ICMP type */
#define     ICMP_ECHOREPLY                  0
#define     ICMP_UNREACH                    3
#define     ICMP_SOURCEQUENCH               4
#define     ICMP_REDIRECT                   5
#define     ICMP_ECHO                       8
#define     ICMP_ROUTERADVERT               9
#define     ICMP_ROUTERSOLICIT              10
#define     ICMP_TIMXCEED                   11
#define     ICMP_PARAMPROB                  12
#define     ICMP_TSTAMP                     13
#define     ICMP_TSTAMPREPLY                14
#define     ICMP_IREQ                       15
#define     ICMP_IREQREPLY                  16
#define     ICMP_MASKREQ                    17
#define     ICMP_MASKREPLY                  18
    u_int8_t icmp_code;       /* ICMP code */
#define     ICMP_UNREACH_NET                0
#define     ICMP_UNREACH_HOST               1
#define     ICMP_UNREACH_PROTOCOL           2
#define     ICMP_UNREACH_PORT               3
#define     ICMP_UNREACH_NEEDFRAG           4
#define     ICMP_UNREACH_SRCFAIL            5
#define     ICMP_UNREACH_NET_UNKNOWN        6
#define     ICMP_UNREACH_HOST_UNKNOWN       7
#define     ICMP_UNREACH_ISOLATED           8
#define     ICMP_UNREACH_NET_PROHIB         9
#define     ICMP_UNREACH_HOST_PROHIB        10
#define     ICMP_UNREACH_TOSNET             11
#define     ICMP_UNREACH_TOSHOST            12
#define     ICMP_UNREACH_FILTER_PROHIB      13
#define     ICMP_UNREACH_HOST_PRECEDENCE    14
#define     ICMP_UNREACH_PRECEDENCE_CUTOFF  15
#define     ICMP_REDIRECT_NET               0
#define     ICMP_REDIRECT_HOST              1
#define     ICMP_REDIRECT_TOSNET            2
#define     ICMP_REDIRECT_TOSHOST           3
#define     ICMP_TIMXCEED_INTRANS           0
#define     ICMP_TIMXCEED_REASS             1
#define     ICMP_PARAMPROB_OPTABSENT        1

    u_int16_t icmp_sum;   /* ICMP Checksum */

    union
    {
        struct
        {
            u_int16_t id; /* ICMP id */
            u_int16_t seq;/* ICMP sequence number */
        } echo;

#undef icmp_id
#undef icmp_seq
#define icmp_id     hun.echo.id
#define icmp_seq    hun.echo.seq
 
        u_int32_t gateway; /* gateway host */
        struct
        {
            u_int16_t pad;/* padding */
            u_int16_t mtu;/* MTU size */
        } frag;
    } hun;
    union
    {
        struct
        {
            n_time its_otime;
            n_time its_rtime;
            n_time its_ttime;
        } ts;
        struct
        {
             proto_ipv4_hdr idi_ip;
            /* options and then 64 bits of data */
        } ip;
        u_int32_t mask;
        int8_t data[1];

#undef icmp_mask
#define icmp_mask    dun.mask
#undef icmp_data
#define icmp_data    dun.data

#undef icmp_otime
#define icmp_otime   dun.ts.its_otime
#undef icmp_rtime
#define icmp_rtime   dun.ts.its_rtime
#undef icmp_ttime
#define icmp_ttime   dun.ts.its_ttime
    }dun;
};
typedef struct _proto_icmpv4_hdr proto_icmpv4_hdr;

/*
 *  IGMP header
 *  Internet Group Message Protocol
 *  Static header size: 8 bytes
 */
struct proto_igmp_hdr
{
    u_int8_t igmp_type;       /* IGMP type */
#define IGMP_MEMBERSHIP_QUERY           0x11    /* membership query */
#define IGMP_V1_MEMBERSHIP_REPORT       0x12    /* Ver. 1 membership report */
#define IGMP_V2_MEMBERSHIP_REPORT       0x16    /* Ver. 2 membership report */
#define IGMP_LEAVE_GROUP                0x17    /* Leave-group message */
    u_int8_t igmp_code;       /* IGMP code */
    u_int16_t igmp_sum;       /* IGMP checksum */
    struct in_addr igmp_group;/* IGMP host IP */
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//layer 4

/*
 *  TCP header
 *  Transmission Control Protocol
 *  Static header size: 20 bytes
 */
struct _proto_tcp_hdr
{
    u_int16_t th_sport;       /* source port */
    u_int16_t th_dport;       /* destination port */
    u_int32_t th_seq;          /* sequence number */
    u_int32_t th_ack;          /* acknowledgement number */
    u_int8_t th_off:4,        /* data offset */
    th_x2:4;                  /* (unused) */

    u_int8_t  th_flags;       /* control flags */
#define TH_FIN    0x01      /* finished send data */
#define TH_SYN    0x02      /* synchronize sequence numbers */
#define TH_RST    0x04      /* reset the connection */
#define TH_PUSH   0x08      /* push data to the app layer */
#define TH_ACK    0x10      /* acknowledge */
#define TH_URG    0x20      /* urgent! */
#define TH_ECE    0x40 
#define TH_CWR    0x80
    u_int16_t th_win;         /* window */
    u_int16_t th_sum;         /* checksum */
    u_int16_t th_urp;         /* urgent pointer */
};
typedef struct _proto_tcp_hdr proto_tcp_hdr;

/*
 *  UDP header
 *  User Data Protocol
 *  Static header size: 8 bytes
 */
struct _proto_udp_hdr
{
    u_int16_t uh_sport;       /* soure port */
    u_int16_t uh_dport;       /* destination port */
    u_int16_t uh_ulen;        /* length */
    u_int16_t uh_sum;         /* checksum */
};
typedef struct _proto_udp_hdr proto_udp_hdr;

/////////////////////////////////////////////////////////////////////////
//application layer

/*
 *  Base DNSv4 header
 *  Domain Name System
 *  Base header size: 12/14 bytes
 */
struct proto_dnsv4_hdr
{
    u_int16_t h_len;          /* length of the packet - only used with TCP */
    u_int16_t id;             /* DNS packet ID */
    u_int16_t flags;          /* DNS flags */
    u_int16_t num_q;          /* Number of questions */
    u_int16_t num_answ_rr;    /* Number of answer resource records */
    u_int16_t num_auth_rr;    /* Number of authority resource records */
    u_int16_t num_addi_rr;    /* Number of additional resource records */
};

#define proto_DNS_H proto_UDP_DNSV4_H
struct proto_dnsv4udp_hdr
{
    u_int16_t id;             /* DNS packet ID */
    u_int16_t flags;          /* DNS flags */
    u_int16_t num_q;          /* Number of questions */
    u_int16_t num_answ_rr;    /* Number of answer resource records */
    u_int16_t num_auth_rr;    /* Number of authority resource records */
    u_int16_t num_addi_rr;    /* Number of additional resource records */
};

/////////////////////////////////////////////////////////////////////////
//Functions.
#ifdef __cplusplus
extern "C"
{
#endif

proto_ipv4_hdr * get_ipv4_header(const u_char* pktdata,const int pktlen);
void * get_layer4_header(const proto_ipv4_hdr *ip_hdr);
int get_application_layer_data(proto_ipv4_hdr* ip_hdr,int caplen,char *retdata);


#ifdef __cplusplus
}
#endif


#endif
