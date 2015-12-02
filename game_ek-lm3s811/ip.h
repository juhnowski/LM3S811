/*${.::ip.h} .............................................................*/
#ifndef ip_h
#define ip_h
#include "ip.h"

typedef __packed struct {
    scd_uint32   faddr;
    scd_uint8_t optlen;
    scd_uint8_t srr;
    scd_uint8_t rr;
    scd_uint8_t ts;
    scd_uint8_t is_setbyuser:1,
                is_data:1,     
                is_strictroute:1,
                srr_is_hit:1,    
                is_changed:1,    
                rr_needaddr:1,   
                ts_needtime:1,   
                ts_needaddr:1;   
    scd_uint8_t router_alert;
    scd_uint8_t __pad1;
    scd_uint8_t __pad2;
    scd_uint8_t __data[0];
}IPOptions;


typedef __packed struct {
#if defined(SCD__LITTLE_ENDIAN_BITFIELD)
    scd_uint8_t    ihl:4,
                   version:4;
#elif defined (SCD__BIG_ENDIAN_BITFIELD)
    scd_uint8_t    version:4,
                   ihl:4;
#else
#error  "Please fix <scd.h>"
#endif
    scd_uint8_t    tos;
    scd_uint16_t   tot_len;
    scd_uint16_t   id;
    scd_uint16_t   frag_off;
    scd_uint8_t    ttl;
    scd_uint8_t    protocol;
    scd_uint16_t   check;
    scd_uint32_t   saddr;
    scd_uint32_t   daddr;
} IPHeader;


#endif  /* ip_h */