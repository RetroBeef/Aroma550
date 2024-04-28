#include <CommandParser.h>
#include <BLEDevice.h>

#include <Aroma.h>

BLEClient* bleClient = 0;
Aroma* aroma = 0;

typedef CommandParser<> AromaCommandParser;
AromaCommandParser parser;

void cmd_fog(AromaCommandParser::Argument *args, char *response) {
  uint8_t state = args[0].asUInt64;
  aroma->enableFog(state);
  strlcpy(response, "sent fog command", AromaCommandParser::MAX_RESPONSE_SIZE);
}

void cmd_led(AromaCommandParser::Argument *args, char *response) {
  uint8_t state = args[0].asUInt64;
  aroma->enableLed(state);
  strlcpy(response, "sent led command", AromaCommandParser::MAX_RESPONSE_SIZE);
}

void cmd_rgb(AromaCommandParser::Argument *args, char *response) {
  uint8_t r = args[0].asUInt64;
  uint8_t g = args[1].asUInt64;
  uint8_t b = args[2].asUInt64;
  aroma->setLedRgbValue(r, g, b);
  strlcpy(response, "sent rgb command", AromaCommandParser::MAX_RESPONSE_SIZE);
}

void cmd_state(AromaCommandParser::Argument *args, char *response) {
  String arg = args[0].asString;
  if (arg == "fog") {
    aroma->queryFogStatus();
  } else if(arg == "led"){
    aroma->queryLedStatus();
  }
  strlcpy(response, "sent state command", AromaCommandParser::MAX_RESPONSE_SIZE);
}

void cmd_set_time(AromaCommandParser::Argument *args, char *response) {
  uint8_t hours = args[0].asUInt64;
  uint8_t minutes = args[1].asUInt64;
  aroma->setTime(hours, minutes);
  strlcpy(response, "sent time command", AromaCommandParser::MAX_RESPONSE_SIZE);
}

void setup() {
  Serial.begin(115200);

  BLEDevice::init("");
  bleClient = BLEDevice::createClient();

  aroma = new Aroma(bleClient, "33:FB:B4:5B:8B:12", [](BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify){
    aroma_response_t* response = (aroma_response_t*)pData;
    switch (response->type) {
      case stateFog: {
          if (response->state) {
            Serial.println("fog(on)");
          } else {
            Serial.println("fog(off)");
          }
        } break;
      case stateLed: {
          if (response->state) {
            Serial.print("led(on), ");
          } else {
            Serial.print("led(off), ");
          }
          aroma_rgb_t* rgb = (aroma_rgb_t*)response->data;
          Serial.printf("rgb(%u, %u, %u)", rgb->r, rgb->g, rgb->b);
          Serial.println();
        }
    }
  });
  aroma->connectToDevice();

  parser.registerCommand("state", "s", &cmd_state);
  parser.registerCommand("fog", "u", &cmd_fog);
  parser.registerCommand("led", "u", &cmd_led);
  parser.registerCommand("rgb", "uuu", &cmd_rgb);
  parser.registerCommand("time", "uu", &cmd_set_time);
}

void loop() {
  if (Serial.available()) {
    char line[128];
    size_t lineLength = Serial.readBytesUntil('\n', line, 127);
    line[lineLength] = '\0';
    if (aroma->isConnected()) {
      char response[AromaCommandParser::MAX_RESPONSE_SIZE];
      parser.processCommand(line, response);
      Serial.println(response);
    }
  }
  if (!aroma->isConnected()) {
    aroma->connectToDevice();
  }
}
