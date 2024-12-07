#include <Arduino.h>

const int valvePins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int numValves = sizeof(valvePins) / sizeof(valvePins[0]);

const int waterInputValvePin = 10;
const int waterLevelSensorPin = A0;
const int circulationValvePin = A1;
const int airPumpPin = A2;
const int waterPumpPin = A3;
const int lightSensorPin = A4;

// Valve bitwise definitions
const int valveA = 1 << 0;  // 00000001
const int valveB = 1 << 1;  // 00000010
const int valveC = 1 << 2;  // 00000100
const int valveD = 1 << 3;  // 00001000
const int valveE = 1 << 4;  // 00010000
const int valveF = 1 << 5;  // 00100000
const int valveG = 1 << 6;  // 01000000
const int valveH = 1 << 7;  // 10000000
