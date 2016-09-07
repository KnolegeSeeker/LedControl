#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;
int addButton = 7;
int subButton = 8;
int verifyButton = 9;
int resp = 0;
int esp;

LedControl lc=LedControl(DIN,CLK,CS,1);

int correct = 0;
byte neg[]=
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

byte pos[] =
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

int j1 (int x) {
  int a, b, c, j;

  j = random(0, 5);

  if(j == 0) {
    a = x+5;
    b = 2*x+5;
    c = 3*x+5;
    lc.clearDisplay(0);
    lc.setRow(0, 7, x);
    lc.setRow(0, 6, a);
    lc.setRow(0, 5, b);
    lc.setRow(0, 4, c);
    
    esp = 4*x+5;
  } else {
    if(j == 1) {
      a = 2*x;
      b = 4 * x;
      c = 8*x;
      lc.clearDisplay(0);
      lc.setRow(0, 7, x);
      lc.setRow(0, 6, a);
      lc.setRow(0, 5, b);
      lc.setRow(0, 4, c);
      
      esp = 16*x;
    } else {
      if(j == 2) {
        a = x+2;
        b = x+4;
        c = x+6;
        lc.clearDisplay(0);
        lc.setRow(0, 7, x);
        lc.setRow(0, 6, a);
        lc.setRow(0, 5, b);
        lc.setRow(0, 4, c);
        
        esp = x+8;
      } else {
        if(j == 3) {
          a = x+3;
          b = x+6;
          c = x+9;
          lc.clearDisplay(0);
          lc.setRow(0, 7, x);
          lc.setRow(0, 6, a);
          lc.setRow(0, 5, b);
          lc.setRow(0, 4, c);
          
          esp = x+12;
        } else {
          if(j == 4) {
            a = 3*x;
            b = 6*x;
            c = 12*x;
            lc.clearDisplay(0);
            lc.setRow(0, 7, x);
            lc.setRow(0, 6, a);
            lc.setRow(0, 5, b);
            lc.setRow(0, 4, c);
            
            esp = 24*x;
          }
        }
      }
    }
  }

  return esp;
};


void setup(){
 pinMode(addButton, INPUT);
 pinMode(subButton, INPUT);
 pinMode(verifyButton, INPUT);
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,1);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
 Serial.begin(9600);
 Serial.flush();
 randomSeed(analogRead(A0)); 
}

void verify() { // verifica se a resposta esta correta e inicia novo jogo randomicamente.
    
    lc.setRow(0, 0, esp);
    delay(2500);
    
    if(resp == esp) {

      correct = 1;
    } else {
      correct = -1;
    }
    
    if(correct == 1) {
      printByte(pos);
      delay(1500);
    }
    if(correct == -1) {
      printByte(neg);
      delay(1500);
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
    int x;

    x = (int)random(0, 11);
    Serial.print("valor de x ");
    Serial.println(x);
    esp = j1(x);
    //printByte(jogo1);

    while(digitalRead(verifyButton) == 0) {
      if(digitalRead(addButton) == 1) {
        resp++;
        if(resp == 256) {
          resp = 0;
        }
        Serial.print("resposta resp");
        Serial.println(resp);
        lc.setRow(0,2, resp);
        delay(150);
      }
      
      if(digitalRead(subButton) == 1) {
        resp--;
        if(resp == -1) {
          resp = 255;
        }
        Serial.println(resp);
        lc.setRow(0,2, resp);
        delay(150);
      }
    }

    verify();

}
