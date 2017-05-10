#include <Servo.h> //servo library
Servo myservo; // create servo object to control servo
int ENA=5; 
int IN1=6;
int IN2=7;
int ENB=11; 
int IN3=8;
int IN4=9;
int Echo = A4;  
int Trig = A5;
long duration = 0;
long inchesAhead, inchesLeft, inchesRight = 0;
int data;
int moving = 2;
int turningRight = 4;
int turningLeft = 10;
int stopped = 12;

void setup() {
  myservo.attach(3);// attach servo on pin 3 to servo object
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);
  digitalWrite(ENA,HIGH);  
  digitalWrite(ENB,HIGH);  
  pinMode(moving, OUTPUT);
  pinMode(turningRight, OUTPUT);
  pinMode(turningLeft, OUTPUT);
  pinMode(stopped, OUTPUT);
}

void forward(){
  //digitalWrite(moving,LOW);
  digitalWrite(IN1,HIGH);      //moves car forward
  digitalWrite(IN2,LOW);         
  digitalWrite(IN3,LOW);      
  digitalWrite(IN4,HIGH); 
  digitalWrite(moving, HIGH);
  digitalWrite(turningLeft,LOW);
  digitalWrite(turningRight,LOW);
  digitalWrite(stopped,LOW);
  Serial.println("Forward");
}

void turnRight(){
  digitalWrite(IN1,LOW);      
  digitalWrite(IN2,LOW);         // left wheel goes forward
  digitalWrite(IN3,LOW);      
  digitalWrite(IN4,HIGH);         // right wheel goes forward
  digitalWrite(turningRight,HIGH);
  digitalWrite(turningLeft,LOW);
  digitalWrite(moving,LOW);
  digitalWrite(stopped,LOW);
  delay(300);
}

void turnLeft(){
  digitalWrite(IN1,HIGH);      
  digitalWrite(IN2,LOW);         
  digitalWrite(IN3,LOW);      
  digitalWrite(IN4,LOW);
  digitalWrite(turningLeft,HIGH); 
  digitalWrite(turningRight,LOW);   
  digitalWrite(moving,LOW);
  digitalWrite(stopped,LOW);     
  delay(300);
}

void stopCar(){
  digitalWrite(IN1,LOW);      //car stop
  digitalWrite(IN2,LOW);         
  digitalWrite(IN3,LOW);      
  digitalWrite(IN4,LOW);
  digitalWrite(moving, LOW);
  digitalWrite(turningLeft,LOW);
  digitalWrite(turningRight,LOW);
  digitalWrite(stopped,HIGH);
  Serial.println("Stopped");
 // delay(1000);
  
}

void scanAhead(){
  myservo.write(60);
  digitalWrite(Trig, LOW); //ultrasonic on
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  duration = pulseIn(Echo, HIGH); //measure and display distance
  inchesAhead = microsecondsToInches(duration);
  //Serial.println("straight");
  //Serial.println(inchesAhead);
}

void scanLeft(){
  myservo.write(130);
  delay(300);
  digitalWrite(Trig, LOW); //ultrasonic on
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  duration = pulseIn(Echo, HIGH); //measure and display distance
  inchesLeft = microsecondsToInches(duration);
  Serial.println("Left");
  Serial.println(inchesLeft);
}

void scanRight(){
  myservo.write(0);
  delay(300);
  digitalWrite(Trig, LOW); //ultrasonic on
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  duration = pulseIn(Echo, HIGH); //measure and display distance
  inchesRight = microsecondsToInches(duration);
  Serial.println("Right");
  Serial.println(inchesRight);
}


void loop() {
  //digitalWrite(moving,LOW);
  myservo.write(60);
  delay(200);
  scanAhead();
  if(inchesAhead < 15){
    stopCar();
    delay(1000);
    scanRight();
    delay(500);
    scanLeft();
    delay(500);
    if(inchesRight > inchesLeft){
      turnRight();
    }
    else if(inchesLeft > inchesRight){
      turnLeft();
    }
  }
  else{
    forward();
  }
  
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}
