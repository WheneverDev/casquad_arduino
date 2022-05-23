#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

const int h = 8;
const int w = 8;

const int PIN=4;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(h, w, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);


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

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0)
};
