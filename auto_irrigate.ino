#include <Servo.h>

//ultrasonic
long duration;
float distance; 
const int trigPin = 9;
const int echoPin = 10;

//moisture
int sensor_pin = A0;
int output_value;

//servo
Servo servo;
int angle = 0;
int servoPin = 11;
int r;

//levels
int upper = 5;
int lower = 10;
int correct_moisture = 20;
int check = 1;

void setup() {
  //setup for servo 
  servo.attach(servoPin);
  
  //setup for ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //setup for moisture sensor

  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = checkwaterlevel();
  Serial.println(distance);
  delay(1000);
  if(distance > lower) {
    handlewaterlevel_led();
  }
  else{
    r=1;  
  }
  output_value = analogRead(sensor_pin);
  output_value = map(output_value,550,0,0,100);
  Serial.print("Mositure : ");
  Serial.print(output_value);
  Serial.println("%");
  Serial.print("Output: ");
  Serial.println(output_value);
  Serial.print("Correct: ");
  Serial.println(correct_moisture);
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Lower: ");
  Serial.println(lower);
  Serial.print("Upper: ");
  Serial.println(upper);
 
  if(output_value < correct_moisture && distance<lower) {
    //0 for clockwise
    //1 for anticlockwise 
    //servo.write(20);
    r=1;
    //delay(100);
    Serial.println("Valve open!");
    servo.write(-85);
  }
  else {
  //servo.write(85);
  r=0;
  delay(100);
    Serial.println("Valve closed!");
    servo.write(85);
  }
  /*if(r=1)
  {
    servo.write(30);
  }
  else
  {
    servo.write(-30);
  }*/
}

int checkwaterlevel() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration/29/2;
  return distance;
}

void handlewaterlevel_led() {
    //fill water manually until the LED switches off
    if(distance > upper) {
      Serial.println("Fill water!");
      r=0;
      delay(50);
      //distance = checkwaterlevel();
    }
    //led should switch off
}
