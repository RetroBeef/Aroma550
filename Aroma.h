#pragma once
#include <Arduino.h>
#include "BLEDevice.h"
#include "aroma_data.h"
#include <functional>

class Aroma{
private:
protected:
  BLEClient* bleClient;
  
  BLERemoteCharacteristic* writeCharacteristic = 0;
  BLERemoteCharacteristic* readCharacteristic = 0;
  BLERemoteService* aromaService = 0;

  String deviceMac;

  std::function<void(BLERemoteCharacteristic*, uint8_t*, size_t, bool)> notificationCallback;
public:
  Aroma(BLEClient* bleClient, const String& deviceMac, const std::function<void(BLERemoteCharacteristic*, uint8_t*, size_t, bool)>& notificationCallback) : bleClient(bleClient), deviceMac(deviceMac), notificationCallback(notificationCallback) {}
  virtual ~Aroma(){}
  int8_t connectToDevice();
  bool isConnected(){
    return bleClient->isConnected();
  }

  void enableFog(uint8_t state);
  void enableLed(uint8_t state);
  void setLedRgbValue(uint8_t r, uint8_t g, uint8_t b);
  void queryFogStatus();
  void queryLedStatus();
  void setTime(uint8_t hours, uint8_t minutes);

};
