#include "Aroma.h"

namespace {
  static BLEUUID serviceUUID("0000ae00-0000-1000-8000-00805f9b34fb");
  static BLEUUID writeUUID("0000ae01-0000-1000-8000-00805f9b34fb");
  static BLEUUID readUUID("0000ae02-0000-1000-8000-00805f9b34fb");
}

int8_t Aroma::connectToDevice() {
  if (!bleClient->connect(BLEAddress(deviceMac.c_str()))) {
    return -1;
  }

  aromaService = bleClient->getService(serviceUUID);
  if (aromaService == nullptr) {
    return -2;
  }

  writeCharacteristic = aromaService->getCharacteristic(writeUUID);
  if (writeCharacteristic == nullptr) {
    return -3;
  }

  readCharacteristic = aromaService->getCharacteristic(readUUID);
  if (readCharacteristic == nullptr) {
    return -4;
  }

  if (readCharacteristic->canNotify()) {
    readCharacteristic->registerForNotify(notificationCallback);
    return 0;
  }else {
    return -5;
  }
}

void Aroma::enableFog(uint8_t state) {
  aroma_packet_t packet = fog(state);
  writeCharacteristic->writeValue((uint8_t*)&packet, sizeof(aroma_packet_t));
}

void Aroma::enableLed(uint8_t state) {
  aroma_packet_t packet = led(state);
  writeCharacteristic->writeValue((uint8_t*)&packet, sizeof(aroma_packet_t));
}

void Aroma::setLedRgbValue(uint8_t r, uint8_t g, uint8_t b) {
  aroma_packet_t packet = rgb(r, g, b);
  writeCharacteristic->writeValue((uint8_t*)&packet, sizeof(aroma_packet_t));
}

void Aroma::queryFogStatus() {
  aroma_packet_t packet = fog_status();
  writeCharacteristic->writeValue((uint8_t*)&packet, sizeof(aroma_packet_t));
}

void Aroma::queryLedStatus() {
  aroma_packet_t packet = led_status();
  writeCharacteristic->writeValue((uint8_t*)&packet, sizeof(aroma_packet_t));
}

void Aroma::setTime(uint8_t hours, uint8_t minutes) {
  aroma_packet_t packet = set_time(0, 0, 0, 0, hours, minutes);
  writeCharacteristic->writeValue((uint8_t*)&packet, sizeof(aroma_packet_t));
}
