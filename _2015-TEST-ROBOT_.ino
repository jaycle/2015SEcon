
int dirL = 33;
int dirR = 31;
int Motor_Speed_left ();
int Motor_Speed_Right ();
void Straight ();

void setup()
{


}
void loop(){


  int pwm_def = 255;
  pinMode(11, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(33, OUTPUT);

  digitalWrite(31, LOW);
  digitalWrite(33, LOW);


  //analogWrite(11, Motor_Speed_Left ());
  //analogWrite(12, Motor_Speed_Right ());
  int Straight();


  delay(600);

}

//0 - 50 - 100 sensor values
void Straight ()
{
  int Sensor = 50; //left sensor drift value
  int Sensor_Input = analogRead(3); //line follower sensors
  int leftSpeed = 0;
  int rightSpeed = 0;

  if (Sensor_Input < 50) //if drifting left
  {
    
    while (Sensor_Input < 50 && leftSpeed < 50)
    {
      leftSpeed++; // increments the speed counter by 1
      int left = leftSpeed + 200; // increases the speed left by x
      int right = leftSpeed - 200; // decreases the speed right by x
      analogWrite(11, left);
      analogWrite(12, right);
    }
  }
  
  else if (Sensor_Input > 50) //if drifting right
  {
    
    while (Sensor_Input > 50 && rightSpeed < 50)
    {
      rightSpeed++; // increments the speed counter by 1
      int left = rightSpeed - 200; // decreases the speed left by x
      int right = rightSpeed + 200; // increases the speed right by x
      analogWrite(11, left);
      analogWrite(12, right);
    }
  }
  else //(Sensor_Input = 50) // if straight
  {
    analogWrite(11, Motor_Speed_Left ());
    analogWrite(12, Motor_Speed_Right ());
    Sensor = 50; //resets the sensor drift value if needed 
    rightSpeed = 0; //resets the right sensor drift value if needed
    leftSpeed = 0; //resets the left sensor drift value if needed
  }
  
}


int Motor_Speed_Left ()
{
  int left = 200;
  return left;
}

int Motor_Speed_Right ()
{
  int right = 200;
  return right;
}





