/*${.::sctp.h} .............................................................*/
#ifndef sctp_h
#define sctp_h
#include "sca.h"

typedef __packed struct {
    SCAHeader sca_header;  
    scd_protocol_t protocol;
} SCTPHeader;

typedef __packed struct {
    SCTPHeader sctp_header;
    scd_uint8_t type;
} SCTPSHeader;

typedef __packed struct {
    SCTPHeader sctp_header;
#if defined(SCD__LITTLE_ENDIAN_BITFIELD)
    scd_flags_t  
            res:2,                   
            fin:1,
            syn:1,
            rst:1,
            psh:1,
            ack:1,
            urg:1;
#elif defined (SCD__BIG_ENDIAN_BITFIELD)
    scd_flags_t    
            urg:1,
            ack:1,
            psh:1,
            rst:1,
            syn:1,
            fin:1,
            res:2;
#else
#error  "Please fix <scd.h>"
#endif    
    scd_uint16_t window;
    scd_port_t source_port;
    scd_port_t destination_port;
    scd_uint32_t sequence_number;
    scd_uint32_t acknowledgment_number;
    scd_uint16_t urgent_ptr;
} SCTPAHeader;




#endif  /* sctp_h */