#include <ArduinoBLE.h> 
#include "config.h"

int lastButtonStatus;

BLEService AnalogService(SERVICE_UUID);
BLECharacteristic AnalogChar(ANALOG_CHARACT_UUID, BLERead | BLENotify, 2);
BLEByteCharacteristic ChannelChar(CHANNEL_CHARACT_UUID, BLEWrite | BLEWrite);

BLEDescriptor AnalogDescriptor("2901","analog");
BLEDescriptor ChannelDescriptor("2901","channel");

void setup() {
	Serial.begin(115200);
	analogReadResolution(12);

	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_BUTTON, INPUT_PULLUP);

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

	BLEDevice central = BLE.central();
	if (central) {
		Serial.print("Connected to central : ");
		Serial.println(central.address());

		while (central.connected()) {

			if (ChannelChar.written()) {
				Serial.println("Channel char written");
				int c = ChannelChar.value();
				if(c == 4){
					digitalWrite(PIN_LED, !digitalRead(PIN_LED));
					Serial.println("LED");
				}
			}
			
			uint16_t button = digitalRead(PIN_BUTTON);
			if (lastButtonStatus == 0 && button == 1) {
				Serial.println("Button push!");
			}
			lastButtonStatus = button;
			AnalogChar.writeValue(button);

			delay(250);
		}	

		Serial.print("Disconnected from central: ");
		Serial.println(central.address());
		
	}
}
