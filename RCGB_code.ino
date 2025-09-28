#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int red = 10, green = 9, blue = 8;
const int button = 7;

int ledMode = 0;
int lastButtonState = HIGH;
int lastReading = HIGH;
unsigned long lastDebounceTime = 0;
const int debounceDelay = 50;

unsigned long prevTime = 0;
int animState = 0;
int animDelay = 1000;

void setup() {

  lcd.begin(16,2);

  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);

  pinMode(button,INPUT_PULLUP);

  updateLCD();

}

void loop() {

  clickButton();
  updateLED();

}

void clickButton(){
  int reading = digitalRead(button);

  if(reading!=lastReading){
    lastDebounceTime = millis();
  }

  if(millis()-lastDebounceTime>debounceDelay){

    if(reading!=lastButtonState){

      lastButtonState = reading;

      if(lastButtonState==LOW){
        ledMode=(ledMode+1)%4;
        animState=0;
        updateLCD();
      }
    }
  }

  lastReading=reading;
}

void updateLCD(){
  lcd.clear();

  switch(ledMode){
    case 0:
    lcd.print("RGB mode");
    break;
    case 1:
    lcd.print("YCM mode");
    break;
    case 2:
    lcd.print("White mode");
    break;
    case 3:
    lcd.print("OFF RCGB LED");
    break;
  }

}

void updateLED(){

  switch(ledMode){
    case 0:
    RGB();
    break;
    case 1:
    YCM();
    break;
    case 2:
    WHITE();
    break;
    case 3:
    OFF();
    break;
  }

}

void RGB(){

  if(millis()-prevTime>=animDelay){

    prevTime=millis();

    switch(animState){
      case 0:
      digitalWrite(red,HIGH);
      digitalWrite(green,LOW);
      digitalWrite(blue,LOW);
      break;
      case 1:
      digitalWrite(red,LOW);
      digitalWrite(green,HIGH);
      digitalWrite(blue,LOW);
      break;
      case 2:
      digitalWrite(red,LOW);
      digitalWrite(green,LOW);
      digitalWrite(blue,HIGH);
      break;

    }

    animState=(animState+1)%3;
  }
}

void YCM(){

  if(millis()-prevTime>=animDelay){

    prevTime=millis();

    switch(animState){
      case 0:
      digitalWrite(red,HIGH);
      digitalWrite(green,HIGH);
      digitalWrite(blue,LOW);
      break;
      case 1:
      digitalWrite(red,LOW);
      digitalWrite(green,HIGH);
      digitalWrite(blue,HIGH);
      break;
      case 2:
      digitalWrite(red,HIGH);
      digitalWrite(green,LOW);
      digitalWrite(blue,HIGH);
      break;

    }

    animState=(animState+1)%3;
  }
}

void WHITE(){

  digitalWrite(red,HIGH);
  digitalWrite(green,HIGH);
  digitalWrite(blue,HIGH);

}

void OFF(){

    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
    digitalWrite(blue,LOW);

}