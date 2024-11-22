// Pines de los sensores
const int pinesSensores[5] = {4, 5, 18, 19, 21};

// Variables para registrar los tiempos
unsigned long tiempos[5] = {0, 0, 0, 0, 0};

// Estado previo de los sensores
bool estadoPrevio[5] = {true, true, true, true, true};

// Indicador de que el experimento ha terminado
bool experimentoTerminado = false;

void setup() {
  Serial.begin(115200);

  // Configurar pines de sensores como entrada
  for (int i = 0; i < 5; i++) {
    pinMode(pinesSensores[i], INPUT);
  }

  Serial.println("Sistema listo. Esperando detección...");
}

void loop() {
  if (!experimentoTerminado) {
    for (int i = 0; i < 5; i++) {
      // Leer el estado actual del sensor
      bool estadoActual = digitalRead(pinesSensores[i]);

      // Detectar el paso de la esfera por el sensor (flanco descendente)
      if (!estadoActual && estadoPrevio[i]) { // Detectar transición de HIGH a LOW
        if (i == 0) {
          // Si es el primer sensor, registrar el tiempo inicial
          tiempos[i] = millis();
          Serial.println("Esfera detectada en el primer sensor");
          Serial.print("Tiempo inicial: ");
          Serial.print(tiempos[i]);
          Serial.println(" ms");
        } else {
          // Para los demás sensores, registrar el tiempo relativo
          tiempos[i] = millis() - tiempos[0];
          Serial.print("Esfera detectada en el sensor ");
          Serial.print(i + 1);
          Serial.print(" - Tiempo relativo: ");
          Serial.print(tiempos[i]);
          Serial.println(" ms");
        }
      }

      // Actualizar el estado previo del sensor
      estadoPrevio[i] = estadoActual;
    }

    // Verificar si todos los sensores han registrado tiempos
    if (tiempos[4] > 0) {
      experimentoTerminado = true;
      imprimirResultados();
    }
  }
}

void imprimirResultados() {
  Serial.println("\n--- Resultados del experimento ---");
  for (int i = 0; i < 5; i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(tiempos[i]);
    Serial.println(" ms");
  }
  Serial.println("----------------------------------");
}
