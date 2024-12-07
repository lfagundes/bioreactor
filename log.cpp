#include <Arduino.h>
#include "log.h"

unsigned long startTime;

void resetClock() {
  startTime = millis();
}

void logMessage(const char* message) {
    extern unsigned long startTime; // Reference to the global startTime variable
    unsigned long elapsedMillis = millis() - startTime;
    unsigned long seconds = elapsedMillis / 1000;
    unsigned long hours = seconds / 3600;
    unsigned long minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;

    // Format and print the elapsed time
    char timeBuffer[9];
    sprintf(timeBuffer, "%02lu:%02lu:%02lu", hours, minutes, seconds);

    Serial.print("[");
    Serial.print(timeBuffer);
    Serial.print("] ");
    Serial.println(message);
}
