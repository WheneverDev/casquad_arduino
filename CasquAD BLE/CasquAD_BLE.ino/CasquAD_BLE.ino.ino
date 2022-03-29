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
	if (write_adr) {
		Serial.print("Adresse : ");
		Serial.println(BLE.address());
	}
	BLEDevice central = BLE.central();
	if (central) {
		Serial.print("Connected to central : ");
		Serial.println(central.address());
		while (central.connected()) {
				if (ChannelChar.written()) {
						Serial.println("Channel char written");
						int c = ChannelChar.value();
						if ((c>=0)&&(c<=8)) {
							Serial.println(c);
							channel = A0+c;
						}
				}
				int x = analogRead(channel);
				uint8_t a[2];
				a[0] = (x >> 8) & 0xFF;
				a[1] = x & 0xFF;
				AnalogChar.writeValue(a,2);
				delay(1000);
		}
		Serial.print("Disconnected from central: ");
		Serial.println(central.address());
	}
}
