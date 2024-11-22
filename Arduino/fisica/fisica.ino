// Pines de los sensores infrarrojos
const int sensorPins[5] = {4, 5, 18, 19, 21};
unsigned long times[5];
bool experimentStarted = false;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }
  Serial.println("{\"status\":\"Sistema listo. Envíe 'inicio' para comenzar.\"}");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "inicio") {
      experimentStarted = true;
      Serial.println("{\"status\":\"Experimento iniciado.\"}");
      resetTimes();
    } else if (command == "datos") {
      if (!experimentStarted) {
        printResults();
      } else {
        Serial.println("{\"status\":\"El experimento aún está en curso.\"}");
      }
    }
  }

  if (experimentStarted) {
    for (int i = 0; i < 5; i++) {
      if (digitalRead(sensorPins[i]) == LOW && times[i] == 0) {
        delay(50);
        if (digitalRead(sensorPins[i]) == LOW) {
          times[i] = millis();
          if (i == 4) {
            experimentStarted = false;
            Serial.println("{\"status\":\"Experimento finalizado.\"}");
          }
        }
      }
    }
  }
}

void resetTimes() {
  for (int i = 0; i < 5; i++) {
    times[i] = 0;
  }
}

void printResults() {
  Serial.print("{\"results\":{\"times\":[");
  for (int i = 0; i < 5; i++) {
    Serial.print(times[i]);
    if (i < 4) Serial.print(",");
  }
  Serial.println("]}}");
}
