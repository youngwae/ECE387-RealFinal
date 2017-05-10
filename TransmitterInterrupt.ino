#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);
const uint64_t pipe1 = 0xE8E8F0F0E1LL;

int forward = 2;
//int right = 4;
//int left = 3;
int stopped = 3;

 int movement = 0;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(108); 
  radio.openWritingPipe(pipe1);
  //pinMode(forward,INPUT);
  //pinMode(right,INPUT);
  //pinMode(left,INPUT);
  //attachInterrupt(digitalPinToInterrupt(5), ISR_left, RISING);
  //attachInterrupt(digitalPinToInterrupt(4), ISR_right, RISING);
  attachInterrupt(digitalPinToInterrupt(forward), ISR_forward, RISING);
 // attachInterrupt(digitalPinToInterrupt(stopped), ISR_stop, RISING);
  attachInterrupt(digitalPinToInterrupt(stopped), ISR_stop, RISING);
  

}

void ISR_forward(){
  movement = 1;
}

//void ISR_right(){
  //movement = 2;
//}

//void ISR_left(){
  //movement = 3;
//}

void ISR_stop(){
  movement = 4;
}

void transmit(){
radio.write(&movement, sizeof(movement));
Serial.println(movement);
}

void loop() {
  Serial.println(movement);
  transmit();
  
  
}
