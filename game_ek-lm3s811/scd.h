/*${.::scd.h} .............................................................*/
#ifndef scd_h
#define scd_h
#include "stdint.h"
#define SCD__LITTLE_ENDIAN_BITFIELD //SCD__BIG_ENDIAN_BITFIELD
#define scd_mac_t scd_uint8_t[6] 
#define scd_ip_t scd_uint8_t[4] 

    typedef uint8_t scd_uint8_t;
    typedef uint16_t scd_uint16_t;
    typedef uint32_t scd_uint32_t;

    typedef int8_t scd_int8_t;
    typedef int16_t scd_int16_t;
    typedef int32_t scd_int32_t;

    typedef float scd_float_t;
    typedef double scd_double_t;
    
    typedef struct {
        scd_int32_t seconds;
        scd_int32_t nanoseconds;
    } SCDTime;
    

    typedef scd_uint8_t scd_sca_t;
    typedef scd_uint8_t scd_port_t;
    typedef scd_uint16_t scd_crc_t;
    typedef scd_uint16_t scd_size_t;
    typedef scd_uint8_t scd_flags_t;
    typedef scd_uint8_t scd_protocol_t;
    typedef scd_int8_t scd_err_t;
#endif  /* scd_h */