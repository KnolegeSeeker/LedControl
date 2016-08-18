#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;
int addButton = 7;
int subButton = 8;
int verifyButton = 9;
int resp = 0;

LedControl lc=LedControl(DIN,CLK,CS,1);

int correct = 0;
byte pos[]=
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

byte neg[] =
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

byte jogo1 [] = 
{
  B00000010,
  B00000000,
  B00000100,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte jogo2 [] =
{
  B00001110,
  B00000000,
  B00010101,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

void setup(){
 pinMode(addButton, INPUT);
 pinMode(subButton, INPUT);
 pinMode(verifyButton, INPUT);
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
 Serial.begin(9600);
 Serial.flush(); 
}

void verify() { // verifica se a resposta esta correta e inicia novo jogo randomicamente.
    
    if(resp == 6) {

      correct = 1;
    } else {
      correct = -1;
    }
    
    if(correct == 1) {
      printByte(pos);
      delay(1000);
    }
    if(correct == -1) {
      printByte(neg);
      delay(1000);
    }
    correct = 0;
    resp = 0;
  //jogo = jogos[random(0, 2)];
}

void printByte(byte character []) // imprime a imagem do byte no display.
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
void loop(){

    printByte(jogo1);

    while(digitalRead(verifyButton) == 0) {
      if(digitalRead(addButton) == 1) {
        resp++;
        Serial.println(resp);
        lc.setRow(0,4, resp);
        delay(150);
      }
      
      if(digitalRead(subButton) == 1) {
        resp--;
        Serial.println(resp);
        lc.setRow(0,4, resp);
        delay(150);
      }
    }

    verify();

}
