#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


RF24 radio(12, 13); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo pinkieS,indexS,ringS,middleS,thumbS;

int countdelay = 1000;
int actiondelay = 100;
long randNumber;
int value[4];

const int palmbutton = 22;
const int fistbutton = 23;
const int wakkabutton = 24;
const int ilubutton = 25;
const int countbutton = 26;
const int rpsbutton = 27;
const int wavebutton = 28;
// the reset button is plugged into pin 7
const int resetbutton = 29;
const int switcheroo = 7;

void setup()
{
  Serial.begin(9600);
  pinkieS.attach(2);
  indexS.attach(8);
  ringS.attach(4);
  middleS.attach(6);
  thumbS.attach(10);
  randomSeed(analogRead(0));
  //Buttons
  pinMode (palmbutton, INPUT_PULLUP);
  pinMode (fistbutton, INPUT_PULLUP);
  pinMode (wakkabutton, INPUT_PULLUP);
  pinMode (ilubutton, INPUT_PULLUP);
  pinMode (countbutton, INPUT_PULLUP);
  pinMode (rpsbutton, INPUT_PULLUP);
  pinMode (wavebutton, INPUT_PULLUP);
  pinMode (7, INPUT_PULLUP);
  pinMode (resetbutton, INPUT_PULLUP);
  pinMode (switcheroo, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  zero();
}

void loop() {
// fist();
  btnLoop();
  
}

void btnLoop() {
  if (digitalRead(switcheroo) == LOW) {
    Serial.println("Button Loop");
    if (digitalRead(palmbutton) == LOW) {
      peace();
      delay(2000);
    } else if (digitalRead(fistbutton) == LOW) {
      fist();
      delay(2000);
    } else if (digitalRead(wakkabutton) == LOW) {
      wakka();
      delay(2000);
    } else if (digitalRead(ilubutton) == LOW) {
      iLu();
      delay(2000);
    } else if (digitalRead(countbutton) == LOW) {
      count();
    } else if (digitalRead(rpsbutton) == LOW) {
      rPs();
    } else if (digitalRead(wavebutton) == LOW) {
      wave();
  //  } else if (digitalRead(resetbutton) == LOW) {
  //    presentation();
    } else {
      zero();
    }
  } else {
      if (radio.available()){
        while (radio.available()) {
          radio.read(value, sizeof(value));
          int thumbValue = value[1];
          int indexValue = value[1];
          int middleValue = value[3];
          int ringValue = value[2];
          int pinkieValue = value[0];

          // obscene gesture prevention Algorithm (patent pending) (TM) (SM) (R) (C) 2019
          if (middleValue < 50 && (thumbValue > 80) && (indexValue > 80) 
            && (ringValue > 80) && (pinkieValue > 80))
          {
            middleValue = 150;
          }
          
          pinkieS.write(pinkieValue);
          indexS.write(indexValue);
          ringS.write(ringValue);
          middleS.write(middleValue);
          thumbS.write(thumbValue);
      }
    }
  }
}

void presentation() {
  while (true) {
    Serial.println("Presentation Mode activated");
    zero();
    delay(2000);
    fist();
    delay(2000);
    wakka();
    delay(2000);
    iLu();
    delay(2000);
    Serial.println("Presentation mode loop iteration complete");
    // switch breakout code needed
  }
}

void wave()
{
  zero();
  
  thumbS.write(170);
  
  delay(100);
  
  while(true)
  {
    for (int t = 0; t<170; t++)
    {
      if (t >= 30)
        pinkieS.write(t);

      if (t >= 60)
        ringS.write(t);

      if (t >= 90)
         middleS.write(t);

      if (t >= 120)
         indexS.write(t);
     
      delay(5);
    }
    
    for (int t = 170; t > 20; t--)
    {
      if (t <= 170)
        pinkieS.write(t);

      if (t <= 110)
        ringS.write(t);

      if (t <= 80)
        middleS.write(t);

      if (t <= 50)
        indexS.write(t);
      
      delay(5);
    }
      if (digitalRead(resetbutton) == LOW) 
      {
        break;
        delay(100);
        presentation();
      }
      
      if (digitalRead(wavebutton) == HIGH) {
        break;
      }
   }
}

void rPs()
{
  countdown();
  delay(100);
  randNumber = random(0,3);
  Serial.println(randNumber);
  if (randNumber == 0)
  {
    zero();
    delay(1000);
  }
  else if (randNumber == 1)
  {
    fist();
    delay(1000);
  }
  else if (randNumber == 2)
  {
    scissors();
    delay(1000);
  }
}

void peace(){
  pinkieS.write(160);
  indexS.write(20);
  ringS.write(160);
  middleS.write(20);
  thumbS.write(160);
}

void zero()
{
  pinkieS.write(20);
  indexS.write(20);
  ringS.write(20);
  middleS.write(20);
  thumbS.write(20);
}

void wakka()
{
  pinkieS.write(20);
  indexS.write(170);
  ringS.write(170);
  middleS.write(170);
  thumbS.write(20);
}

void iLu()
{
  pinkieS.write(20);
  indexS.write(20);
  ringS.write(170);
  middleS.write(170);
  thumbS.write(20);
}

void fist(){
  pinkieS.write(140);
  indexS.write(150);
  ringS.write(150);
  middleS.write(160);
  thumbS.write(145);
}

void testFingers()
{
  pinkieS.write(140);
  indexS.write(150);
  thumbS.write(145);
  ringS.write(150);
  middleS.write(150);
  delay(2000);
  pinkieS.write(20);
  indexS.write(20);
  thumbS.write(20);
  ringS.write(20);
  middleS.write(20);
  delay(1000);
}

void count()
{
  fist();
  delay(1000);
  indexS.write(20);
  delay(countdelay);
  middleS.write(20);
  delay(countdelay);
  ringS.write(20);
  delay(countdelay);
  pinkieS.write(20);
  delay(countdelay);
  thumbS.write(20);
  delay(countdelay);
}

void countdown()
{
  pinkieS.write(140);
  indexS.write(20);
  thumbS.write(145);
  ringS.write(20);
  middleS.write(20);
  delay(700);
  pinkieS.write(140);
  indexS.write(20);
  thumbS.write(145);
  ringS.write(150);
  middleS.write(20);
  delay(700);
  pinkieS.write(140);
  indexS.write(20);
  thumbS.write(145);
  ringS.write(150);
  middleS.write(160);
  delay(700);
}

void scissors()
{
  indexS.write(20);
  middleS.write(20);
  pinkieS.write(140);
  ringS.write(150);
  thumbS.write(145);
}
