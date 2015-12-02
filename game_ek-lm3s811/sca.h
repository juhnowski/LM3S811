/*${.::sca.h} .............................................................*/
#ifndef sca_h
#define sca_h
#include "scd.h"

typedef __packed struct {
    scd_sca_t source_address;
    scd_sca_t dest_address;
    scd_size_t total_length;
    scd_size_t identification;
#if defined(SCD__LITTLE_ENDIAN_BITFIELD)
    scd_flags_t  
                   res:6,                   
                   mf:1,
                   df:1;
#elif defined (SCD__BIG_ENDIAN_BITFIELD)
    scd_flags_t    
                   df:1,
                   mf:1,
                   res:6;
#else
#error  "Please fix <scd.h>"
#endif    
    scd_uint8_t fragment_offset;
    scd_uint8_t ttl;
    scd_protocol_t protocol;
    scd_crc_t checksum;
} SCAHeader;

#endif  /* sca_h */