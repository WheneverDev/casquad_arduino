#include "function.h"
#include <ArduinoBLE.h>
#include <Arduino.h>

void sendData(BLECharacteristic chara, uint16_t value) {
    chara.writeValue(value);
    Serial.print("Value ");
    Serial.print(value);
    Serial.println(" sent.");
}