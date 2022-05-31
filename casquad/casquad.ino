#include "gyroscope.h"
#include "led.h"
#include "accelerometre.h"
#include "casquadBLE.h"

#define PIN_AIRBAG 5
#define PIN_BLINK 6 
#define PIN_RIGHT 4
#define PIN_LEFT 3 

int timemax = 5000;

int oldMovement = 0;

void setup() {
  Serial.begin(9600);
  //while (!Serial); //debbuging
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

  //Setup pin
  pinMode(PIN_AIRBAG, OUTPUT);
  pinMode(PIN_BLINK, OUTPUT);
  pinMode(PIN_RIGHT, OUTPUT);
  pinMode(PIN_LEFT, OUTPUT);

  //Setup LED
  matrix.begin();
  matrix.setBrightness(255);

  //Battery animation
  digitalWrite(PIN_BLINK, HIGH);
  startingAnimation(batteryanim, colors[0], colors[4], colors[1], colors[2]);
  
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
      Serial.println("fall");
      
      //Launch airbag
      digitalWrite(PIN_AIRBAG, HIGH);
      digitalWrite(PIN_BLINK, HIGH);
      
      oldtime = millis();
      movget = true;
      fall = true;
      
      //Send SMS
      sendBLEdata((byte)0x00);

      //Lock
      while(1){
        drawArray(falldraw, colors[3]);
        delay(500);
        drawArray(nothingdraw, colors[2]);
        delay(500);
      }
    }
  }
  
  //Detecte movement
  if (IMU.gyroscopeAvailable()){
    int movement = newMovement(xg, yg, zg);

    if (movement == 1 && movget == false && newMovementPossible == true) {
      Serial.println("   right");
      movget = true;
  
      //Start blinking
      digitalWrite(PIN_BLINK, HIGH);
      digitalWrite(PIN_LEFT, HIGH);
      
      drawArray(rightarrowdraw, colors[1]);
      oldtime = millis();
      newMovementPossible = false;
      oldMovement = movement;
    }

    if (movement == 2 && movget == false && newMovementPossible == true) {
      Serial.println("   left");
      movget = true;
  
      //Start blinking
      digitalWrite(PIN_BLINK, HIGH); 
      digitalWrite(PIN_RIGHT, HIGH);
      
      drawArray(leftarrowdraw, colors[1]);
      oldtime = millis();
      newMovementPossible = false;
      oldMovement = movement;
    }
    
    if (movement == oldMovement && movget == true && newMovementPossible == true) {
      Serial.println("   stop");
      movget = false;
  
      //Stop blinking
      digitalWrite(PIN_BLINK, LOW);
      digitalWrite(PIN_LEFT, LOW);
      digitalWrite(PIN_RIGHT, LOW);
      
      drawArray(nothingdraw, colors[2]);
      oldtime = millis();
      newMovementPossible = false;
    }
    
    if (newMovementPossible == false && millis() >= oldtime+1000) {
      newMovementPossible = true;
    }
  }
}
