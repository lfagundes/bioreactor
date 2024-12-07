#include "wiring.h"
#include "log.h"

const int daylightThreshold = 900;
const int maximumLightAmplitude = 100;

int readLight() {
  return analogRead(lightSensorPin);
}

void waitForDay() {
  while (true) {
    // Wait for a read of enough light
    // higher reads mean less light.
    int light = readLight();
    while (light > daylightThreshold) {
      delay(10000);
      logMessage(("It's night: " + String(light)).c_str());
    }
    int max = light;
    int min = light;
    // Now make a read every 5 seconds for 5 minutes
    // There should be no value above threshold and the
    // amplitude should be below threshold
    for (int i=0; i<60; i++) {
      light = readLight();
      if (light > max) {
        max = light;
      }
      if (light < min) {
        min = light;
      }
      delay(5000);
      logMessage(("Is it day? " + String(light)).c_str());
    }
    if (max < daylightThreshold && max - min < maximumLightAmplitude) {
      logMessage("It's day! Resetting clock");
      return;
    }
  }
}

bool isNight() {
  int light = readLight();
  // Read every 5s for a minute
  for (int i=0; i<12; i++) {
    if (light < daylightThreshold) {
      return false;
    }
  }
  return true;

}
