#define clockPin 10
#define latchPin 11
#define dataPin 12
#define colClock 7
#define colLatch 8
#define colData 9
#define botMais 6
#define botMenos 5
#define botConfirma 4
void registerWrite(const int iData);
void sendData(unsigned const int data);
void drawLike(unsigned const int like);
unsigned const int coluna[]={2,3,4,5,6,7,8,9};
unsigned const int valor[10]={3,2,7,4,9,8,11,10,15,20};
unsigned const int like[8]={
	 28,//00011100
	 20,//00010100
	246,//11110110
	193,//11000001
	193,//11000001
	193,//11000001
	193,//11000001
	254 //11111110
};
void setup(){
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(colClock,OUTPUT);
  pinMode(colLatch,OUTPUT);
  pinMode(colData,OUTPUT);
  pinMode(botMais,INPUT);
  pinMode(botMenos,INPUT);
  pinMode(botConfirma,INPUT);
  //Serial.begin(9600);
}
unsigned int indexVetor=0;
unsigned int dataConfirm=0;
void jogo(){
    registerWrite(colLatch,colData,colClock,1);
    sendData(valor[indexVetor]);
    delay(5);

    registerWrite(colLatch,colData,colClock,3);
    sendData(valor[indexVetor+1]);
    delay(5);
    
    registerWrite(colLatch,colData,colClock,5);
    sendData(dataConfirm);
    delay(5);
    
  }
void loop(){
  jogo();
  if(digitalRead(botMais)==HIGH){
    while(digitalRead(botMais)==HIGH) {}dataConfirm++;
  }
  if(digitalRead(botMenos)==HIGH){
    while(digitalRead(botMenos)==HIGH){} dataConfirm-=1;
  }
  if(digitalRead(botConfirma)==HIGH)
    while(digitalRead(botConfirma)==HIGH){
      if(dataConfirm ==(valor[indexVetor]&valor[indexVetor+1])){
        indexVetor++;
        if(indexVetor == 10) indexVetor=0;
        for(int cont=0;cont<300;cont++){
          for(int iCount=0;iCount<8;iCount++){
            registerWrite(colLatch,colData,colClock,iCount);
            drawLike(1,iCount);
            delay(1);
          }
        }
      }else{
        dataConfirm=0;
        for(int cont=0;cont<300;cont++){
          for(int iCount=0;iCount<8;iCount++){
            registerWrite(colLatch,colData,colClock,iCount);
            drawLike(0,iCount);
            delay(1);
          }
        }
      }
    }
}
void drawLike(unsigned const int likes,unsigned const int cont){
	if(likes == 1){
      registerWrite(colLatch,colData,colClock,cont);
			digitalWrite(latchPin,LOW);
			shiftOut(dataPin,clockPin,MSBFIRST,like[cont]);
			digitalWrite(latchPin,HIGH);
	}else{
			digitalWrite(latchPin,LOW);
			shiftOut(dataPin,clockPin,MSBFIRST,like[7-cont]);
			digitalWrite(latchPin,HIGH);
		}
}
void sendData(unsigned const int data){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,data);
    //delay(5);
    digitalWrite(latchPin,HIGH);
  }
void registerWrite(const int latch,const int data,const int clockP,const int iData){
  byte bitsToSend = (1UL<<iData);
  digitalWrite(latch,LOW);
  shiftOut(data,clockP,MSBFIRST,bitsToSend);
  digitalWrite(latch,HIGH);
  //Para o contador começar de Tras para frente, basta mudar
  //MSBFIRST por LSBFIRST
}
