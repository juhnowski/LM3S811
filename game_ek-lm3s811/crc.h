#ifndef crc_h
#define crc_h
#include "scd.h"

#define CRC16 0x8005
    scd_uint16_t gen_crc16(const scd_uint8_t *data, scd_uint16_t size);

#endif  /* crc_h */