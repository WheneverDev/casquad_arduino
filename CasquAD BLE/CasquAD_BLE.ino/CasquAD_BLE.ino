#include <ArduinoBLE.h> 
#include "config.h"
#include "function.h"

uint16_t lastButtonStatus;

BLEService ArduinoService(SERVICE_UUID);
BLECharacteristic DateSender(ANALOG_CHARACT_UUID, BLERead | BLENotify, 2);
BLEByteCharacteristic DataReceiver(CHANNEL_CHARACT_UUID, BLEWrite | BLEWrite);

BLEDescriptor SenderDescriptor("2901","analog");
BLEDescriptor ReceiverDescriptor("2901","channel");

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

	DateSender.addDescriptor(SenderDescriptor);
	DataReceiver.addDescriptor(ReceiverDescriptor);

	BLE.setLocalName("CASQU'AD");
	BLE.setAdvertisedService(ArduinoService);
	
	ArduinoService.addCharacteristic(DateSender);
	ArduinoService.addCharacteristic(DataReceiver);
	
	BLE.addService(ArduinoService);
	BLE.advertise();

}

void loop() {

	BLEDevice central = BLE.central();
	if (central) {
		Serial.print("Connected to device : ");
		Serial.println(central.address());

		while (central.connected()) {

			if (DataReceiver.written()) {
				Serial.println("Channel char written");
				int c = DataReceiver.value();
				if(c == 4){
					digitalWrite(PIN_LED, !digitalRead(PIN_LED));
					Serial.println("LED");
				}
			}
			
			uint16_t button = digitalRead(PIN_BUTTON);
			if (lastButtonStatus == 1 && button == 0) {
				Serial.println("Button push!");
				DateSender.writeValue(button);
			}
			lastButtonStatus = button;

			delay(250);
		}	

		Serial.print("Disconnected from device: ");
		Serial.println(central.address());
		
	}
}
