/*
 * This file is part of the home composting bioreactor project on
 * https://github.com/lfagundes/bioreactor
 *
 * Copyright (c) 2024 Luis Fagundes
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "log.h"
#include "wiring.h"
#include "weather.h"

void setup() {
  Serial.begin(9600);
  resetClock();
  delay(1000);
  // Initialize all valve pins as OUTPUTs
  for (int i = 0; i < numValves; i++) {
    pinMode(valvePins[i], OUTPUT);
    // Ensure all irrigation outputs start OFF
    digitalWrite(valvePins[i], LOW);
  }
  pinMode(waterLevelSensorPin, INPUT_PULLUP);
  pinMode(lightSensorPin, INPUT);

  pinMode(waterInputValvePin, OUTPUT);
  digitalWrite(waterInputValvePin, LOW);

  pinMode(circulationValvePin, OUTPUT);
  digitalWrite(circulationValvePin, LOW);

  pinMode(waterPumpPin, OUTPUT);
  digitalWrite(waterPumpPin, LOW);

  pinMode(airPumpPin, OUTPUT);
  digitalWrite(airPumpPin, LOW);

  logMessage("Bioreactor initialized");
}

void pumpOn() {
  digitalWrite(waterPumpPin, HIGH);
  logMessage("Water pump ON");
}

void pumpOff() {
  digitalWrite(waterPumpPin, LOW);
  logMessage("Water pump OFF");
}

void openCirculation() {
  digitalWrite(circulationValvePin, HIGH);
  delay(500);
}

void closeCirculation() {
  delay(500);
  digitalWrite(circulationValvePin, LOW);
}

void open(int valves) {
  setValves(valves, HIGH);
  delay(500);
}

void close(int valves) {
  delay(500);
  setValves(valves, LOW);
}

void setValves(int valves, int state) {
  for (int i = 0; i < numValves; i++) {
    if (valves & (1 << i)) {
      digitalWrite(valvePins[i], state);
      String message = "Valve " + String(i) + (state == HIGH ?
                                               " opened" : " closed");
      logMessage(message.c_str());
    }
  }
}

bool waterAboveThreshold() {
  bool connected = digitalRead(waterLevelSensorPin) == LOW; // LOW means connected
  if (connected) {
    logMessage("Water level is low, needs water");
  } else {
    logMessage("Water level is OK");
  }
  return !connected;
}

void inputWater(int t) {
  for (int i=0; i < t; i++) {
    if (waterAboveThreshold()) {
      digitalWrite(waterInputValvePin, LOW);
      return;
    }
    digitalWrite(waterInputValvePin, HIGH);
    delay(1000);
  }
  digitalWrite(waterInputValvePin, LOW);
}

void cleanUp() {
  openCirculation();
  pumpOn();
  delay(5000);
  pumpOff();
  closeCirculation();
}

void loop() {
  while (true) {
    waitForDay();
    resetClock();
    inputWater(120);
    while (!isNight()) {
      // Cleanup
      openCirculation();
      pumpOn();
      delay(5000);
      // Collect nutrients for 10s
      open(valveH);
      delay(10000);
      // Irrigate cannabis for 1 minute
      open(valveG);
      close(valveH);
      delay(60000);
      pumpOff();
      close(valveG);
      // Now irrigate nutrients every 10 minutes for 4 hours
      for (int i=0; i<24; i++) {
        delay(600000);
        open(valveH);
        pumpOn();
        delay(10000);
        pumpOff();
        close(valveH);
        inputWater(30);
      }
    }
  }
}
