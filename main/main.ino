#include <Servo.h>

//declare analog pin connections
const int pinkieF = A0;
const int indexF = A3;
const int ringF = A1;
const int middleF = A2;
const int thumbF = A4;

int value; //for the finger values
int pos = 0;

const int motorDelay = 50;

Servo pinkieS;
Servo indexS;
Servo ringS;
Servo middleS;
Servo thumbS;

//max values for fingers. Fingers are curled. Preset Values are estimates; will be updated during calibration.
int pinkieMaxInput = 850;
int indexMaxInput = 850;
int ringMaxInput = 850;
int middleMaxInput = 850;
int thumbMaxInput = 850;

//min values for fingers. Fingers are stretched out. Preset Values are estimates; will be updated during calibration.
int pinkieMinInput = 550;
int indexMinInput = 550;
int ringMinInput = 550;
int middleMinInput = 550;
int thumbMinInput = 550;

//max values for servos
//these will be hardcoded once mounted and measured
int pinkieMaxOutput = 180;
int indexMaxOutput = 180;
int ringMaxOutput = 180;
int middleMaxOutput = 180;
int thumbMaxOutput = 180;

//min values for servos
//these will be hardcoded once mounted and measured
int pinkieMinOutput = 0;
int indexMinOutput = 0;
int ringMinOutput = 0;
int middleMinOutput = 0;
int thumbMinOutput = 0;

void setup()
{
  Serial.begin(9600);       //Begin serial communication
  pinkieS.attach(2);
  indexS.attach(4);
  ringS.attach(6);
  middleS.attach(8);
  thumbS.attach(10);

  // calibration

  // if (button is pushed)
  // calibrationMin()

}

//void servomovement(

void loop()
{
  value = analogRead(pinkieF);         //Read and save analog value from potentiometer
  Serial.println(value);               //Print value
  pos = map(value, pinkieMinInput, pinkieMaxInput, pinkieMinOutput, pinkieMaxOutput);//Map value 0-1023 to 0-255 (PWM)
  delay(motorDelay);                          //Small delay
  pinkieS.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);

  value = analogRead(indexF);         //Read and save analog value from potentiometer
  //Serial.println(value);               //Print value
  pos = map(value, 500, 900, 0, 180);//Map value 0-1023 to 0-255 (PWM)
  delay(motorDelay);                          //Small delay
  indexS.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);

  value = analogRead(ringF);         //Read and save analog value from potentiometer
  //Serial.println(value);               //Print value
  pos = map(value, 500, 900, 0, 180);//Map value 0-1023 to 0-255 (PWM)
  delay(motorDelay);                          //Small delay
  ringS.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);

  value = analogRead(middleF);         //Read and save analog value from potentiometer
  //Serial.println(value);               //Print value
  pos = map(value, 500, 900, 0, 180);//Map value 0-1023 to 0-255 (PWM)
  delay(motorDelay);                          //Small delay
  middleS.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);

  value = analogRead(thumbF);         //Read and save analog value from potentiometer
  //Serial.println(value);               //Print value
  pos = map(value, 500, 900, 0, 180);//Map value 0-1023 to 0-255 (PWM)
  delay(motorDelay);                          //Small delay
  thumbS.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);
}

void calibrationMin()
{
  pinkieMinInput = analogRead(pinkieF);
  indexMinInput = analogRead(indexF);
  ringMinInput = analogRead(ringF);
  middleMinInput = analogRead(middleF);
  thumbMinInput = analogRead(thumbF);
}

void calibrationMax()
{
  pinkieMaxInput = analogRead(pinkieF);
  indexMaxInput = analogRead(indexF);
  ringMaxInput = analogRead(ringF);
  middleMaxInput = analogRead(middleF);
  thumbMaxInput = analogRead(thumbF);
}
