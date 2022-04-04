#include <ArduinoBLE.h>

void sendData(BLECharacteristic chara, uint16_t value);

int tryReceivingData(BLEByteCharacteristic chara);

void changeBackLED();

void changeTurnLED();

