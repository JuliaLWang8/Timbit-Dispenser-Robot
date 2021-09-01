//UTEK 2020 Senior Design 
//Puneet, Julia, Truman 
//Timbit Dispenser

#include <Servo.h>

//Servo
Servo myservo;
int pos = 0;
const int servoPin = 4;

//IR Sensors
const int left_IR_Sensor = A0;
const int right_IR_Sensor = A1;
int left_Sensor_Val, right_Sensor_Val;
const int sensorThresh = 50;

//Motors
const int enA = 10;
const int in1 = 9;
const int in2 = 8;
const int enB = 5;
const int in3 = 7;
const int in4 = 6;

//Ultrasonic Sensor
const int trig = 12;
const int echo = 11;
long duration;
int distance;

//LED 
const int led = 13;

//house drop (fix if time to sreal read)
const int h1 = 1;
const int h2 = 1;
const int h3 = 1;
const int h4 = 1;
const int h5 = 1;

//amount of houses visited
int houseCount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);

  //setting up motor pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //ultrasonic sensor pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //while(Serial.available() <= 0);

  //servo pins
  myservo.attach(4);
  myservo.write(100);

  //led pin 
  pinMode(led, OUTPUT);
}

void loop() {
  //Sensor Calibration  
//  left_Sensor_Val = analogRead(left_IR_Sensor);
//  right_Sensor_Val = analogRead(right_IR_Sensor);
//  Serial.print("Right Val: ");
//  Serial.print(right_Sensor_Val);
//  Serial.print("Left Val: ");
//  Serial.println(left_Sensor_Val);
//  delay(1000);
  //ultrasonic test
  followLine();
}

void birth(){

  for(pos = 100; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(2);
  }

  for(pos = 150; pos >= 100; pos -= 1) {                    
    myservo.write(pos);
    delay(2);
  }
  delay(1000);
}

void over(){
  digitalWrite(led, HIGH);
  while(1);
}

void followLine(){
  left_Sensor_Val = analogRead(left_IR_Sensor);
  right_Sensor_Val = analogRead(right_IR_Sensor);
  if (dist() < 30){
    drive(3);
    if(houseCount == 0){
      for(int i = 0; i < h1; i++){
        birth();
      }
    } else if(houseCount == 1){
      for(int i = 0; i < h2; i++){
        birth();
      }
    } else if(houseCount == 2){
      for(int i = 0; i < h3; i++){
        birth();
      }
    } else if(houseCount == 3){
      for(int i = 0; i < h4; i++){
        birth();
      }
    } else if(houseCount == 4){
      for(int i = 0; i < h5; i++){
        birth();
      }
      over();
    }
    houseCount += 1;
  }
  if (right_Sensor_Val < sensorThresh && left_Sensor_Val < sensorThresh){
    drive(0);
  }
  if (right_Sensor_Val > sensorThresh && left_Sensor_Val < sensorThresh){
    drive(1);
  }
  if (right_Sensor_Val > sensorThresh && left_Sensor_Val > sensorThresh){
    drive(2);
  }
}

int dist(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  return distance;
}

void drive(int dir) { //0 = straight; 1 = left; 2 = right; 3 = stop
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  if (dir == 0){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
  }
  if (dir == 1){
    while(analogRead(left_IR_Sensor) < sensorThresh && analogRead(right_IR_Sensor) < sensorThresh){
      analogWrite(enA, 255);
      analogWrite(enB, 0);
    }
    delay(200);
  }
  if (dir == 2){
    while(analogRead(left_IR_Sensor) < sensorThresh && analogRead(right_IR_Sensor) < sensorThresh){
      analogWrite(enA, 0);
      analogWrite(enB, 255);
    }
    delay(200);
  }
  if (dir == 3){
    for (int i = 150; i >= 0; --i){
      analogWrite(enA, i);
      analogWrite(enB, i);
      delay(20);
    }
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}
