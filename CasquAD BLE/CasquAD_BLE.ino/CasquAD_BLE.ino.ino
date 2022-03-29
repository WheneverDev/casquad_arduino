#include <ArduinoBLE.h>

void setup() {
  Serial.begin(9600);
  
  Serial.println("Starting Casqu'AD firmware...");

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setDeviceName("CASQU'AD");

  BLE.advertise();

}

void loop() {
}
