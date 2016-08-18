# LedControl
LedControl Matriz 8x8
################################################
################################################

#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;

LedControl lc=LedControl(DIN,CLK,CS,1);

byte pos01[]=
{
  B00011100,
  B00010100,
  B11110110,
  B11000001,
  B11000001,
  B11000001,
  B11111110,
  B11111110
};

byte neg01[] =
{
  B11111110,
  B11111110,
  B11000001,
  B11000001,
  B11000001,
  B11110110,
  B00010100,
  B00011100
};

void setup(){
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
}

void pos () {

  for(int i=0; i < 8; i++) {
    lc.setRow(0,i,pos01[i]);
  }
}
void neg() {
  for(int i =0; i < 8; i++) {
    lc.setRow(0, i, neg01[i]);
  }
}
void loop(){ 

    pos();
    delay(1000);
    neg();
    delay(1000);
}
