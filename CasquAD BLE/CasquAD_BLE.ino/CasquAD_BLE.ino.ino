#include <ArduinoBLE.h> 

#define PIN_LED 2

#define SERVICE_UUID "ee04e830-6709-4f42-af61-3e66c48918b3"
#define ANALOG_CHARACT_UUID "ee04e831-6709-4f42-af61-3e66c48918b3"
#define CHANNEL_CHARACT_UUID "ee04e832-6709-4f42-af61-3e66c48918b3"

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
	pinMode(PIN_LED, OUTPUT);

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

							if(c == 4){
								digitalWrite(PIN_LED, HIGH);
								Serial.println("LED");
							}

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
