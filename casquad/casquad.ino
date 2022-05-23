#include "gyroscope.h"
#include "led.h"
#include "accelerometre.h"
#include "casquadBLE.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Starting Casqu'AD firmware...");

  //Setup Bluetooth
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  setupBluetooth();

  //Setup Acce + Gyro
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  //Setup LED
  matrix.begin();
  matrix.setBrightness(100);

  //Setup Airbag
  pinMode(5, OUTPUT);
}

void loop() {
  
  //Bluetooth
  BLEDevice central = BLE.central();

  if (central) {
      central.connected() ? BLEon = true : BLEon = false;
  }
  
  //Detecte fall 
  if (IMU.accelerationAvailable()) {
    if (newFall(xa, ya, za) && fall == false) {
      Serial.println("chute");
      //Launch airbag
      digitalWrite(5, HIGH);
      oldtime = millis();
      movget = true;
      fall = true;
      //Start vibrating
      sendBLEdata((byte)0x00);
    }
  }

  //Detecte movement
  if (IMU.gyroscopeAvailable()){
    int movement = newMovement(xg, yg, zg);

    if (movement == 1 && movget == false) {
      Serial.println("   right");
      oldtime = millis();
      drawArray(rightarrowdraw, colors[1]);
      movget = true;
      
    } else if (movement == 2 && movget == false) {
      oldtime = millis();
      Serial.println("   left");
      movget = true;
      drawArray(leftarrowdraw, colors[1]);
    }
    
    if ((movget || fall) && millis() >= oldtime+3000) {
      movget = false;
      fall = false;
      matrix.fillScreen(0);
      digitalWrite(5, LOW);
    }
    
  }
}
