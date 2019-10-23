#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//pins to read analog input
const int pinkieF = A0; 
const int ringF = A1;
const int middleF = A2;
const int indexF = A3;

int value[4];

int pinkiepos;
int indexpos;
int ringpos;
int middlepos;
int pinkieValue;
int indexValue;
int ringValue;
int middleValue;

RF24 radio(7, 8); // CE, CSN 
const byte addresses[][6] = {"00001", "00002"};

void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop(void){
  pinkieValue = analogRead(pinkieF); 
  pinkiepos = map(pinkieValue, 850, 940, 0, 180);
  indexValue = analogRead(indexF);
  indexpos = map(indexValue, 690, 900, 0, 180);
  ringValue = analogRead(ringF);
  ringpos = map(ringValue, 690, 900, 0, 180);
  middleValue = analogRead(middleF);
  middlepos = map(middleValue, 700, 900, 0, 180);
  Serial.print((String) pinkieValue + "\t" + (String) indexValue + "\t"
    + (String) ringValue + "\t" + (String) middleValue + "\n");
  
  value[0] = pinkiepos;
  value[1] = indexpos;
  value[2] = ringpos;
  value[3] = middlepos;
  radio.write(value, sizeof(value));
}
