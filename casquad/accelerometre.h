#include <Arduino_LSM9DS1.h>

float xa, ya, za;
bool fall = false;
bool newFall(float x, float y, float z) {

    IMU.readAcceleration(x, y, z);
    
    if(x>3.24 || x<-3.24){// la vrai valeur de l'acceleration est de 8.24 ou -8.24
        return true;
    }

    if(y>3.24 || y<-3.24){ //la vrai valeur de l'acceleration est de 8.24 ou -8.24
        return true;
    }
    
    if(z>3.24 || z<-3.24){ //la vrai valeur de l'acceleration est de 8.24 ou -8.24
        return true;
    }
}
