#include <Arduino.h>
#include "config.h"
#include "ESP32Servo.h"
#include <Wire.h>
#include <VL6180X.h>

#include "comm.h"

// Variables globale
VL6180X sensorL;
VL6180X sensorR;
int i1;
int i2;
Servo motDroit;
Servo motGauche;

void avancer(int valdroite, int valgauche)
{
  motDroit.writeMicroseconds(NEUTRE_DROIT - 100 * valdroite);
  motGauche.writeMicroseconds(NEUTRE_GAUCHE + 100 * valgauche);
  if (valdroite)
  {
    if (valdroite < 0)
    {
      digitalWrite(LED_REAR_RIGHT, HIGH);
      digitalWrite(LED_FRONT_RIGHT, LOW);
    }
    else
    {
      digitalWrite(LED_REAR_RIGHT, LOW);
      digitalWrite(LED_FRONT_RIGHT, HIGH);
    }
  }
  else
  {
    digitalWrite(LED_REAR_RIGHT, LOW);
    digitalWrite(LED_FRONT_RIGHT, LOW);
  }

  if (valgauche)
  {
    if (valgauche < 0)
    {
      digitalWrite(LED_REAR_LEFT, HIGH);
      digitalWrite(LED_FRONT_LEFT, LOW);
    }
    else
    {
      digitalWrite(LED_REAR_LEFT, LOW);
      digitalWrite(LED_FRONT_LEFT, HIGH);
    }
  }
  else
  {
    digitalWrite(LED_REAR_LEFT, LOW);
    digitalWrite(LED_FRONT_LEFT, LOW);
  }
}


void mvt_handler(comm::Movement mvt) { 
  switch(mvt) {
    case comm::Movement::FORWARD:
        avancer(1, 1);
    case comm::Movement::LEFT:
      avancer(-1, 1);
    case comm::Movement::RIGHT:
      avancer(1, -1);
    case comm::Movement::BACKWARD:
      avancer(-1, -1);
    case comm::Movement::STOP:
        avancer(0, 0);
    case comm::Movement::UNKNOWN: 
        avancer(0, 0);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_FRONT_RIGHT, OUTPUT);
  pinMode(LED_FRONT_LEFT, OUTPUT);
  pinMode(LED_REAR_RIGHT, OUTPUT);
  pinMode(LED_REAR_LEFT, OUTPUT);
  pinMode(SWITCH_1, INPUT_PULLUP);
  pinMode(SWITCH_2, INPUT_PULLUP);
  motDroit.attach(SERVO_RIGHT);
  motGauche.attach(SERVO_LEFT);
  //comm::movement_handler = mvt_handler;
  // pinMode(TOF_EN_LEFT, OUTPUT);
  // pinMode(TOF_EN_RIGHT, OUTPUT);
  // digitalWrite(TOF_EN_LEFT, LOW);
  // digitalWrite(TOF_EN_RIGHT, LOW);
  // Wire.begin();
  // delay(1000);

  // digitalWrite(TOF_EN_LEFT, HIGH);
  // delay(300);
  // sensorL.init();
  // sensorL.configureDefault();
  // sensorL.setAddress(0x33);
  // sensorL.stopContinuous();

  // digitalWrite(TOF_EN_RIGHT, HIGH);
  // delay(300);
  // sensorR.init();
  // sensorR.configureDefault();
  // sensorR.setAddress(0x30);
  // sensorR.stopContinuous();
}
int c = 0;
void loop()
{
  // int distanceR = sensorR.readRangeSingleMillimeters();
  // int distanceL = sensorL.readRangeSingleMillimeters();
  // if ((distanceL > 40 && distanceL < 71) && (distanceR > 40 && distanceR < 70))
  // {
  //   avancer(1, 1);
  // }
  // else if (distanceL > 40 && distanceL < 70)
  // {
  //   avancer(0, 1);
  // }
  // else if (distanceR > 40 && distanceR < 70)
  // {
  //   avancer(1, 0);
  // }
  // else
  // {
  //   avancer(-1, 0);
  // }
  // delay(200);
  c++;
  Serial.printf("%d\t", c);
  if (c % 3)
  {
    avancer(1, 1);
    delay(1000);
    Serial.println("Forward !");
  }
  else if ((c + 1) % 3)
  {
    avancer(1, -1);
    delay(300);
    Serial.println("Tribord !");
  }
  else
  {
    avancer(0, 0);
    delay(500);
    Serial.println("Stop !");
  }
}