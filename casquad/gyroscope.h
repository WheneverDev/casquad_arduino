#include <Arduino_LSM9DS1.h>

bool movget = false;
bool newMovementPossible = true;
long int oldtime;

float xg, yg, zg;

int newMovement(float x, float y, float z) {
    IMU.readGyroscope(x, y, z);
    
    if (x >= 100.0){
      return 1;

    } else if (x <= -100.0){
      return 2;  
    
    } else if (x < 100.0 && x > -100.0) {
      return 0;
    }
}
