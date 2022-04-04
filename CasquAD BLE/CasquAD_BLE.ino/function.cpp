#include "function.h"
#include <ArduinoBLE.h>
#include <Arduino.h>

void sendData(BLECharacteristic chara, uint16_t value) {
    chara.writeValue(value);
    Serial.print("Value ");
    Serial.print(value);
    Serial.println(" sent.");
}

int tryReceivingData(BLEByteCharacteristic chara) {
    
    if(chara.written()) {
        Serial.println("Data receice");
        int value = chara.value();
        return value;
    }

}