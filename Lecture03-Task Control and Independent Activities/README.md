# 1. Hardware and Software
- Board: ESP32-S3-DevKitC-1 v1.1
- RGB LED: GPIO 38
- Arduino IDE 2.x
- Serial Monitor: 115200 baud
- Both tasks are pinned to Core 1.


# 2. Task Design
The application has two FreeRTOS tasks. Both tasks run on Core 1 with priority 1.
The Serial Task reads commands from the Serial Monitor. It accepts the blink intervals 250, 500 and 1000 milliseconds. It also accepts the commands suspend and resume.
The RGB LED Task controls the onboard RGB LED on GPIO 38. It turns the LED on and off using the current value of blinkInterval.

The two tasks share this variable:
volatile uint32_t blinkInterval = 500;

The Serial Task updates the variable, and the RGB LED Task reads it. Therefore, the Serial Task can change the LED speed while the LED Task continues running independently.


# 3. Task Handles
created one task handle for each task:
TaskHandle_t serialTaskHandle = NULL;
TaskHandle_t ledTaskHandle = NULL;

The handles are stored when the tasks are created with xTaskCreatePinnedToCore().
The LED task handle is used to control the LED Task:
vTaskSuspend(ledTaskHandle);
vTaskResume(ledTaskHandle);

A task handle is a reference to a specific task. It allows the program to suspend or resume that task.


# 4. Suspend / Resume Test
Explain what happened when you used:
- suspend
- resume

# 5. Prediction
Include your prediction table.

# 6. State Analysis
Explain the relevant task states.

# 7. Reflection
Include your 150–200 word reflection.