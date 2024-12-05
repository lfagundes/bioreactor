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
 */

const int valvePins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int numValves = sizeof(valvePins) / sizeof(valvePins[0]);

const int waterInputPin = 10;
const int waterLevelSensorPin = A0;
const int circulationValvePin = A1;
const int airPumpPin = A2;
const int waterPumpPin = A3;

const int cleaningDuration = 10;

// Valve bitwise definitions
const int valveA = 1 << 0;  // 00000001
const int valveB = 1 << 1;  // 00000010
const int valveC = 1 << 2;  // 00000100
const int valveD = 1 << 3;  // 00001000
const int valveE = 1 << 4;  // 00010000
const int valveF = 1 << 5;  // 00100000
const int valveG = 1 << 6;  // 01000000
const int valveH = 1 << 7;  // 10000000

void setup() {
  Serial.begin(9600);
  delay(1000);
  // Initialize all valve pins as OUTPUTs
  for (int i = 0; i < numValves; i++) {
    pinMode(valvePins[i], OUTPUT);
    // Ensure all irrigation outputs start OFF
    digitalWrite(valvePins[i], LOW);
  }
  pinMode(waterInputPin, OUTPUT);
  digitalWrite(waterInputPin, LOW);

  pinMode(circulationValvePin, OUTPUT);
  digitalWrite(circulationValvePin, LOW);

  pinMode(waterPumpPin, OUTPUT);
  digitalWrite(waterPumpPin, LOW);

  pinMode(airPumpPin, OUTPUT);
  digitalWrite(airPumpPin, LOW);
}

void pumpOn() {
  digitalWrite(waterPumpPin, HIGH);
  Serial.println("Water pump ON");
}

void pumpOff() {
  digitalWrite(waterPumpPin, LOW);
  Serial.println("Water pump OFF");
}

void openCirculation() {
  digitalWrite(circulationValvePin, HIGH);
  delay(500);
}

void closeCirculation() {
  delay(500);
  digitalWrite(circulationValvePin, LOW);
}

void openValves(int valveCombination) {
  setValves(valveCombination, HIGH);
}

void closeValves(int valveCombination) {
  setValves(valveCombination, LOW);
}

void irrigate(int valveCombination, int duration) {
  // First dump bottom sediments to upper container to avoid clogging
  openCirculation();
  pumpOn();
  delay(cleaningDuration * 1000);
  // Now open valves and close circulation to pressurize irrigation channels
  openValves(valveCombination);
  closeCirculation();
  // Irrigate for desired duration
  delay(duration * 1000);
  // Stop pump and wait before closing valves, to avoid pressure on hoses
  pumpOff();
  delay(500);
  closeValves(valveCombination);
}

void setValves(int valveCombination, int state) {
  for (int i = 0; i < numValves; i++) {
    if (valveCombination & (1 << i)) {
      digitalWrite(valvePins[i], state);
      Serial.print("Valve ");
      Serial.print(i);
      Serial.println(state == HIGH ? " opened" : " closed");
    }
  }
}

void loop() {
}
