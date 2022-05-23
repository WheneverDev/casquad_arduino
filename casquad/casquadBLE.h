#include <ArduinoBLE.h>

#define SERVICE_UUID "ee04e830-6709-4f42-af61-3e66c48918b3"
#define ANALOG_CHARACT_UUID "ee04e831-6709-4f42-af61-3e66c48918b3"
#define CHANNEL_CHARACT_UUID "ee04e832-6709-4f42-af61-3e66c48918b3"

bool BLEon;

BLEService AnalogService(SERVICE_UUID);
BLECharacteristic AnalogChar(ANALOG_CHARACT_UUID, BLERead | BLENotify, 2);
BLEByteCharacteristic ChannelChar(CHANNEL_CHARACT_UUID, BLEWrite | BLEWrite);

BLEDescriptor AnalogDescriptor("2901","analog");
BLEDescriptor ChannelDescriptor("2901","channel");

void setupBluetooth() {
  analogReadResolution(12);
  AnalogChar.addDescriptor(AnalogDescriptor);
  ChannelChar.addDescriptor(ChannelDescriptor);

  BLE.setLocalName("CASQU'AD");
  BLE.setAdvertisedService(AnalogService);
  
  AnalogService.addCharacteristic(AnalogChar);
  AnalogService.addCharacteristic(ChannelChar);
  
  BLE.addService(AnalogService);
  BLE.advertise();
}

void sendBLEdata(uint8_t data) {
  AnalogChar.writeValue(data);
}
