#include <ArduinoBLE.h>

#define SERVICE_UUID "ee04e839-6709-4f42-af61-3e66c48918b3"
#define ANALOG_CHARACT_UUID "7f32c0f0-67bf-47f4-bf28-15d413fa7b00"
#define CHANNEL_CHARACT_UUID "b15bde96-d6ac-408c-8f85-1ee20201067c"

BLEService AnalogService(SERVICE_UUID);
BLECharacteristic AnalogChar(ANALOG_CHARACT_UUID, BLERead | BLENotify, 2);
BLEByteCharacteristic ChannelChar(CHANNEL_CHARACT_UUID, BLEWrite | BLEWrite);

BLEDescriptor AnalogDescriptor("2901","analog");
BLEDescriptor ChannelDescriptor("2901","channel");

uint8_t channel;
boolean write_adr;

void setup() {
	Serial.begin(115200);
	analogReadResolution(12);
	channel = A0;
	
	Serial.println("Starting Casqu'AD firmware...");
	if (!BLE.begin()) {
		Serial.println("Starting BLE failed!");
		while (1);
	}

	AnalogChar.addDescriptor(AnalogDescriptor);
	ChannelChar.addDescriptor(ChannelDescriptor);

	BLE.setLocalName("CASQU'AD");
	BLE.setAdvertisedService(AnalogService);
	
	AnalogService.addCharacteristic(AnalogChar);
	AnalogService.addCharacteristic(ChannelChar);
	
	BLE.addService(AnalogService);
	BLE.advertise();

}

void loop() {
}
