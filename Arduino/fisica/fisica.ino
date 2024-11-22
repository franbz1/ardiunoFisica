// Pines de los sensores infrarrojos
const int pinesSensores[5] = {4, 5, 18, 19, 21};
unsigned long tiempos[5] = {0, 0, 0, 0, 0}; // Almacena los tiempos relativos al primer sensor activado
unsigned long tiempoInicio = 0; // Marca de tiempo del primer sensor activado
bool estadoPrevio[5] = {true, true, true, true, true}; // Estados previos de los sensores
bool experimentoIniciado = false; // Indica si el experimento está en curso

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    pinMode(pinesSensores[i], INPUT);
  }
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if (comando == "inicio" || comando == "datos") {
      procesarComando(comando);
    }
  }

  if (experimentoIniciado) {
    verificarSensores();
  }
}

void procesarComando(const String &comando) {
  if (comando == "inicio") {
    if (experimentoIniciado) {
      Serial.println("{\"error\":\"El experimento ya está en curso.\"}");
    } else {
      iniciarExperimento();
    }
  } else if (comando == "datos") {
    if (experimentoIniciado) {
      Serial.println("{\"estado\":\"El experimento aún está en curso.\"}");
    } else {
      imprimirResultados();
    }
  } else {
    Serial.println("{\"error\":\"Comando no reconocido.\"}");
  }
}

void iniciarExperimento() {
  // Reiniciar variables
  for (int i = 0; i < 5; i++) {
    tiempos[i] = 0;
    estadoPrevio[i] = true;
  }
  tiempoInicio = 0;
  experimentoIniciado = true;

  Serial.println("{\"estado\":\"Experimento iniciado.\"}");
}

void verificarSensores() {
  for (int i = 0; i < 5; i++) {
    // Leer el estado actual del sensor
    bool estadoActual = digitalRead(pinesSensores[i]);

    // Detectar flanco descendente (HIGH -> LOW)
    if (!estadoActual && estadoPrevio[i]) {
      if (i == 0) {
        // Primer sensor: registrar tiempo inicial
        unsigned long tiempoInicio = millis();
        Serial.println("Tiempo inicial: " + tiempoInicio);
        tiempos[i] = tiempoInicio;
      } else {
        // Sensores posteriores: registrar tiempo relativo
        tiempos[i] = millis() - tiempoInicio;
        Serial.println("Tiempo del sensor: " + String(i + 1) + " " + String(millis() - tiempoInicio));
      }

      // Si es el último sensor, finalizar el experimento
      if (i == 4) {
        finalizarExperimento();
      }
    }

    // Actualizar estado previo
    estadoPrevio[i] = estadoActual;
  }
}

void finalizarExperimento() {
  experimentoIniciado = false;
  for (i = 0; i < 5; i++)
  Serial.println("{\"estado\":\"Experimento finalizado.\"}");
}

void imprimirResultados() {
  String respuesta = "{\"resultados\":{\"tiempos\":[";
  for (int i = 0; i < 5; i++) {
    respuesta += String(tiempos[i]);
    if (i < 4) {
      respuesta += ",";
    }
  }
  respuesta += "]}}";
  Serial.println(respuesta);
}
