#include "aroma_data.h"
#include <stddef.h>
uint8_t crc8(const uint8_t *data, size_t length) {
  uint8_t crc = 0;
  for (size_t i = 0; i < length; ++i) {
    crc ^= data[i];
    for (int j = 0; j < 8; ++j) {
      if (crc & 0x01) {
        crc = 0x8C ^ (crc >> 1);
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

aroma_packet_t fog(uint8_t status) {
  uint8_t tag = 0xf1;
  aroma_packet_t packet = {startByte, tag, {status, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}

aroma_packet_t led(uint8_t status) {
  uint8_t tag = 0xf6;
  aroma_packet_t packet = {startByte, tag, {status, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}

aroma_packet_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  uint8_t tag = 0xf7;
  aroma_packet_t packet = {startByte, tag, {r, g, b, 0x00, 0x00, 0x00, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}

aroma_packet_t fog_status() {
  uint8_t tag = 0xf5;
  aroma_packet_t packet = {startByte, tag, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}

aroma_packet_t led_status() {
  uint8_t tag = 0xf9;
  aroma_packet_t packet = {startByte, tag, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}

aroma_packet_t set_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds) {
  uint8_t tag = 0xe1;
  aroma_packet_t packet = {startByte, tag, {year, month, day, hours, minutes, seconds, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}

aroma_packet_t set_led_ring(uint8_t value) {
  uint8_t tag = 0xe2;
  aroma_packet_t packet = {startByte, tag, {value, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}

aroma_packet_t set_led_mode(uint8_t value) {
  uint8_t tag = 0xf8;
  aroma_packet_t packet = {startByte, tag, {value, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}

aroma_packet_t set_led_size(uint8_t value) {
  uint8_t tag = 0xf3;
  aroma_packet_t packet = {startByte, tag, {value, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, stopByte, 0x00};
  packet.crc = crc8((const uint8_t*)&packet, sizeof(aroma_packet_t) - 1);
  return packet;
}
