#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

const uint8_t startByte = 0xaa;
const uint8_t stopByte = 0xff;
const uint8_t stateLed = 0xf9;
const uint8_t stateFog = 0xf5;

#pragma pack(push, 1)
typedef struct {
  uint8_t start;
  uint8_t tag;
  uint8_t content[8];
  uint8_t stop;
  uint8_t crc;
} aroma_packet_t;

typedef struct{
    uint8_t start;
    uint8_t type;
    uint8_t state;
    uint8_t data[8];
    uint8_t crc;
} aroma_response_t;

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} aroma_rgb_t;
#pragma pack(pop)

aroma_packet_t fog(uint8_t status);
aroma_packet_t led(uint8_t status);
aroma_packet_t rgb(uint8_t r, uint8_t g, uint8_t b);
aroma_packet_t fog_status();
aroma_packet_t led_status();
aroma_packet_t set_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds);
aroma_packet_t set_led_ring(uint8_t value);
aroma_packet_t set_led_mode(uint8_t value);
aroma_packet_t set_led_size(uint8_t value);

#ifdef __cplusplus
}
#endif
