#include <SPI.h>
#include "RF24.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 6,5,4,3);

RF24 radio(7,8);
const uint64_t pipe1 = 0xE8E8F0F0E1LL;

int movement;
bool stopped;
bool forward;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  radio.begin();
  radio.setChannel(108);
  radio.openReadingPipe(1,pipe1);
  radio.startListening();
}

void loop() {
  if (radio.available()) {                           
      radio.read(&movement, sizeof(movement));
      Serial.println(movement);

      switch(movement){
        case 1:
          stopped = false;
          forward = true;
          break;
        case 4:
          stopped = true;
          forward = false;
          break;
      }
  }
  if(stopped){
  lcd.clear();
  lcd.print("Stopped");
  }
  if(forward){
    lcd.clear();
    lcd.print("Forward");
  }

}
