#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define RGB_BUILTIN 38
#define RGB_BRIGHTNESS 50

volatile uint32_t blinkInterval = 500;

TaskHandle_t serialTaskHandle = NULL;
TaskHandle_t ledTaskHandle = NULL;

void setLed(bool on) {
  if (on) {
    neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0);
  } else {
    neopixelWrite(RGB_BUILTIN, 0, 0, 0);
  }
}

bool isDigits(const String &text) {
  if (text.length() == 0) {
    return false;
  }

  for (size_t i = 0; i < text.length(); i++) {
    char c = text.charAt(i);

    if (c < '0' || c > '9') {
      return false;
    }
  }

  return true;
}

void processCommand(String command) {
  command.trim();

  if (command.length() == 0) {
    return;
  }

  if (command.equalsIgnoreCase("suspend")) {
    if (ledTaskHandle != NULL) {
      vTaskSuspend(ledTaskHandle);
      setLed(false);
      Serial.println("LED task suspended.");
    }
    return;
  }

  if (command.equalsIgnoreCase("resume")) {
    if (ledTaskHandle != NULL) {
      vTaskResume(ledTaskHandle);
      Serial.println("LED task resumed.");
    }
    return;
  }

  if (isDigits(command)) {
    uint32_t newInterval = command.toInt();

    if (newInterval == 250 ||
        newInterval == 500 ||
        newInterval == 1000) {
      blinkInterval = newInterval;

      Serial.printf(
        "Blink interval set to %lu ms.\n",
        (unsigned long)blinkInterval
      );
    } else {
      Serial.println(
        "Invalid interval. Enter 250, 500, or 1000."
      );
    }

    return;
  }

  Serial.println(
    "Invalid command. Enter 250, 500, 1000, suspend, or resume."
  );
}

void serialTask(void *parameter) {
  String command;
  command.reserve(64);

  Serial.println("Commands: 250, 500, 1000, suspend, resume");

  for (;;) {
    while (Serial.available() > 0) {
      char c = Serial.read();

      if (c == '\r') {
        continue;
      }

      if (c == '\n') {
        processCommand(command);
        command = "";
      } else if (command.length() < 63) {
        command += c;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void ledTask(void *parameter) {
  for (;;) {
    setLed(true);

    uint32_t interval = blinkInterval;
    vTaskDelay(pdMS_TO_TICKS(interval));

    setLed(false);

    interval = blinkInterval;
    vTaskDelay(pdMS_TO_TICKS(interval));
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    ledTask,
    "LED Task",
    2048,
    NULL,
    1,
    &ledTaskHandle,
    1
  );

  xTaskCreatePinnedToCore(
    serialTask,
    "Serial Task",
    4096,
    NULL,
    1,
    &serialTaskHandle,
    1
  );
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}