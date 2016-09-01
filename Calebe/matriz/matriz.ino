//100MHz shiftOut frequency delayMicrosseconds(1);
unsigned const int colunas[8]={4,5,6,7,8,9,10,11};
#define clockCD 3
#define clockECD 2
void setup(){
  //time_t tempo;
  pinMode(A0,INPUT);
  srand((unsigned)(analogRead(A0)));
  int randomic = rand()%50;
	pinMode(clockCD,OUTPUT);
	pinMode(clockECD,OUTPUT);
  for(int cont = 0; cont < 8; cont ++){
    pinMode(colunas[cont],OUTPUT);  
  }
	digitalWrite(clockECD,HIGH);
	digitalWrite(clockCD,LOW);
	delay(100);
	digitalWrite(clockECD,LOW);
}
void loop(){
  for(int cont = 0 ; cont < 8 ; cont ++){
    digitalWrite(clockCD,HIGH);
    digitalWrite(clockCD,LOW);
    digitalWrite(colunas[cont],HIGH);
		delay(200);
	}
  for(int cont = 0 ; cont < 8 ; cont ++){
    digitalWrite(clockCD,HIGH);
    digitalWrite(clockCD,LOW);
    digitalWrite(colunas[cont],LOW);
   delay(200);
  }
 
}

