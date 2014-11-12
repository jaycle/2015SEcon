#include <QTRSensors.h>


#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN 
#define LEFT_DIR     33
#define RIGHT_DIR    31
#define LEFT_EN      11
#define RIGHT_EN     12
#define FWD          0
#define REV          1

// sensors 0 through 7 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3, 4, 5, 6, 7}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR);
unsigned int sensorValues[NUM_SENSORS];

void leftMotor(int speed, short dir);
void rightMotor(int speed, short dir);


void setup()
{
  delay(500);
  pinMode(13, OUTPUT);
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_EN, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT);
  
  unsigned int position;
  
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 300; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
//  Serial.begin(9600);
//  for (int i = 0; i < NUM_SENSORS; i++)
//  {
//    Serial.print(qtra.calibratedMinimumOn[i]);
//    Serial.print(' ');
//  }
//  Serial.println();
//  
//  // print the calibration maximum values measured when emitters were on
//  for (int i = 0; i < NUM_SENSORS; i++)
//  {
//    Serial.print(qtra.calibratedMaximumOn[i]);
//    Serial.print(' ');
//  }
//  Serial.println();
//  Serial.println();
//  delay(1000);
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 7000
  unsigned int position = qtra.readLine(sensorValues, QTR_EMITTERS_ON ,1);
  rightMotor(150, FWD);
  leftMotor(150, FWD);  
  
  if (position < 3500){
    rightMotor(0,FWD);
    delay(200);
  }
  else if (position >= 3500){
    leftMotor(0, FWD);
    delay(200); 
  }
  
  
}

void leftMotor(int speed, short dir){
  digitalWrite(LEFT_DIR, dir);
  analogWrite(LEFT_EN, speed);
}

void rightMotor(int speed, short dir){
  digitalWrite(RIGHT_DIR, dir);
  analogWrite(RIGHT_EN, speed);
}
