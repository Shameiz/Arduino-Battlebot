// Shameiz and Nader
#include <AFMotor.h>
//declaration of constants and variables
AF_DCMotor motor(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
const int sensors[] = {9, 3};


void setup() {

  // turn on motor
  motor.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  pinMode(sensors[0], OUTPUT);//pin for ultrasonic sensor
  digitalWrite(sensors[0], HIGH); // Trig pin is normally HIGH

  pinMode(sensors[1], INPUT);//pin for pushbutton
  digitalWrite(sensors[1], HIGH); //turns on the 20KΩ pull-up resistor
}

float distance(int pin)
{
  unsigned long time;
  unsigned long sizeofpulse;
  float range;

  pinMode(pin, OUTPUT); //return digital pin to OUTPUT mode after reading
  digitalWrite(pin, LOW);
  delayMicroseconds(25);
  digitalWrite(pin, HIGH); //Trig pin pulsed LOW for 25usec
  time = micros(); //record timer
  pinMode(pin, INPUT); //change pin to INPUT to read the echo pulse
  sizeofpulse = pulseIn(pin, LOW, 18000); //should be approx 150usec, timeout at 18msec
  time = micros() - time - sizeofpulse; // amount of time elapsed since we sent the trigger pulse and detect the echo pulse, then subtract the size of the echo pulse
  range = (time * 340.29 / 2 / 10000) - 3; // convert to distance in centimeters
  return range;
}

void buttonSensor()
{
  if (sensor[1] == LOW)
  {
    motor4.run(FORWARD);//move motor forward
    delay(5000);
  }

motor4.run(RELEASE);

}

void sensor()
{
  float range = distance(sensors[0]);//calculate range
  if (range < 10)
  {
    while (range < 20)
    {
      motor3.run(FORWARD);//move motor forward

      for (int i = 1; i <= 1000; i++)
      {
        buttonSensor();//call button
        delay(1);
      }

      motor3.run(BACKWARD);//move mototr backward
      for (int i = 1; i <= 2000; i++)
      {

        buttonSensor();//call button
        delay(1);
      }
      range = distance(sensors[0]);//calcualte range
    }
    motor3.run(RELEASE);
  }


}

void sensorLoop(int interval)
{
  for (int i = 1; i <= interval; i++)
  {
    sensor();  //call ultrasonic
    buttonSensor();//call button
    delay(1);
  }
}

void front(int interval)
{
  //front
  motor.run(FORWARD);//move motor forward
  motor2.run(FORWARD);//move motor forward
  sensor();
  sensorLoop(interval);
}

void back(int interval)
{
  //back
  motor.run(BACKWARD);//move mototr backward
  motor2.run(BACKWARD);//move mototr backward
  sensor();
  sensorLoop(interval);
}

void right(int interval)
{
  //turn right
  motor.run(FORWARD);//move motor forward
  motor2.run(BACKWARD);//move mototr backward
  sensor();
  sensorLoop(interval);
}

void left(int interval)
{
  //turn left
  motor.run(BACKWARD);//move mototr backward
  motor2.run(FORWARD);//move motor forward
  sensor();
  sensorLoop(interval);

}

void loop() {
  uint8_t i;

  front(10000);//go front

  back(5000);//go back

  right(1000);//go right

  front(10000);//go front

  left(1000);//go left

  front(10000);//go front


  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(1000);
}



