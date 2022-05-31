#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

const int h = 8;
const int w = 8;

const int PIN=7;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(h, w, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS       + NEO_MATRIX_ZIGZAG,
  NEO_GRB               + NEO_KHZ800);


void drawArray(int draw[][h], uint16_t color){
  for(int y=0;y<h;y++){
    for(int x=0;x<w;x++){
      if(draw [y][x]==1){
        matrix.drawPixel(x, y, color);
      } else {
         matrix.drawPixel(x, y, 0);
      }
    }
  }
  matrix.show();
}

void animateBattery(int draw[][h], uint16_t color1, uint16_t color2, uint16_t color3) {
  Serial.println("led");
  for(int y=0;y<h;y++){
    for(int x=0;x<w;x++){
      switch(draw[y][x]){
        case 2:
          matrix.drawPixel(x, y, color1);
          break;
        case 3:
          matrix.drawPixel(x, y, color2);
          break;         
        case 4:
          matrix.drawPixel(x, y, color3);
          break;
      }
    }
  }
  matrix.show();
}

void startingAnimation(int draw[][h], uint16_t red, uint16_t orange, uint16_t green, uint16_t black){
    for (int i = 0; i <= 3; i++){ 
      animateBattery(draw, black, black, red); //Led green/green/green
      delay(200);
      animateBattery(draw, black, orange, red); //Led black/orange/orange
      delay(200);
      animateBattery(draw, green, green, green); //Led black/black/red
      delay(400);
      //animateBattery(draw, green, green, green); //Led green/green/green
      //delay(400);
    }
}

int rightarrowdraw[w][h] = {
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,1,1,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,0},
  {0,0,0,0,1,1,0,0},
  {0,0,0,0,1,0,0,0}        
};

int slowdowndraw[w][h] = {
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0}       
};


int leftarrowdraw[w][h] = {
  {0,0,0,1,0,0,0,0},
  {0,0,1,1,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1},
  {0,0,1,1,0,0,0,0},
  {0,0,0,1,0,0,0,0}       
};

int nothingdraw[w][h] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}        
};

  
int falldraw[w][h] = {
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,0,0,0,0}        
};

int batteryanim[w][h] = {
  {4,4,4,4,4,4,4,4},
  {4,4,4,4,4,4,4,4},
  {3,3,3,3,3,3,3,3},
  {3,3,3,3,3,3,3,3},
  {3,3,3,3,3,3,3,3},
  {2,2,2,2,2,2,2,2},
  {2,2,2,2,2,2,2,2},
  {2,2,2,2,2,2,2,2}        
};

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 0), matrix.Color(255, 255, 0), matrix.Color(255, 172, 0) 
};
