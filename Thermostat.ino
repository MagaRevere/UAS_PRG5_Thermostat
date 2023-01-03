#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal.h>
//Initialize LCD display and set params
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
//Initialize DHT11 Temp Sensor and set params
#define tempSensorPin 10
#define DHTTYPE DHT11
DHT tempSensor(tempSensorPin, DHTTYPE);
#define acTriggerPin A0
#define tempUpPin 8
#define tempDownPin 9
int setTemp = 70;
int tempUpState = 0;
int tempDownState = 0;
int lastTempUpState = 0;
int lastTempDownState = 0;
void setup() {
  lcd.begin(16, 2);
  pinMode(tempUpPin, INPUT);
  pinMode(tempDownPin, INPUT);
  pinMode(acTriggerPin, OUTPUT);
  tempSensor.begin();
  lcd.setCursor(0, 0);
  lcd.print("Set Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Current Temp:");
}

void loop() {
  int currentTemp = tempSensor.readTemperature(true);
  tempUpState = digitalRead(tempUpPin);
  tempDownState = digitalRead(tempDownPin);
  lcd.setCursor(10, 0);
  lcd.print(setTemp);
  lcd.setCursor(14, 1);
  lcd.print(currentTemp);
  if (setTemp == 60) {
    if (tempUpState != lastTempUpState) {
      if (tempUpState == HIGH) {
        setTemp = setTemp + 1;
      } else {
      }
    }
  }
  else if (setTemp == 80) {
    if (tempDownState != lastTempDownState) {
      if (tempDownState == HIGH) {
        setTemp = setTemp - 1;
      } else {
      }
    }
  }
  else {
    if (tempDownState != lastTempDownState) {
      if (tempDownState == HIGH) {
        setTemp = setTemp - 1;
      } else {
      }
    }
    else if (tempUpState != lastTempUpState) {
      if (tempUpState == HIGH) {
        setTemp = setTemp + 1;
      } else {
      }
    }
  }
  lastTempDownState = tempDownState;
  lastTempUpState = tempUpState;

  if (setTemp < currentTemp) {
    digitalWrite(acTriggerPin, HIGH);
  }
  else {
    digitalWrite(acTriggerPin, LOW);
  }
}
