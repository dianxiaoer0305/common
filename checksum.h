/*

 */
 
#ifndef _CHECKSUM_H_
#define _CHECKSUM_H_

#define CHECKSUM_CARRY(x) \
    (x = (x >> 16) + (x & 0xffff), (~(x + (x >> 16)) & 0xffff))
    
int do_checksum(u_int8_t *, int, int);

#endif
