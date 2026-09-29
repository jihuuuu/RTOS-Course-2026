#define TASK_B_PRIORITY 3

TaskHandle_t taskBHandle = NULL;

void taskA(void *parameter) {
  const char *message = "Task A is printing slowly...\n";

  for (;;) {
    for (size_t i = 0; message[i] != '\0'; i++) {
      if (i == 12) {
        xTaskNotifyGive(taskBHandle);
      }

      Serial.print(message[i]);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void taskB(void *parameter) {
  for (;;) {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    Serial.print("[Task B is running!]");
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(taskB, "Task B", 2048, NULL, TASK_B_PRIORITY, &taskBHandle, 1);
  xTaskCreatePinnedToCore(taskA, "Task A", 2048, NULL, 1, NULL, 1);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}