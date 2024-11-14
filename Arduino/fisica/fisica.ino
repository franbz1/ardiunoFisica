// Pines de los sensores infrarrojos y piezoeléctrico
const int IR1 = 15;
const int IR2 = 4;
const int IR3 = 5;
const int PIEZO = 18;

// Variables de tiempo
unsigned long startTime;
unsigned long timeIR1 = 0;
unsigned long timeIR2 = 0;
unsigned long timeIR3 = 0;
unsigned long timePiezo = 0;

// Variable de control
bool experimentStarted = false;

void setup() {
  // Configuración de pines de los sensores
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(PIEZO, INPUT);

  // Iniciar comunicación serial
  Serial.begin(115200);
  Serial.println("Listo para iniciar experimento de caída libre.");

  // Esperar señal para iniciar experimento
  while (true) {
    if (Serial.available() > 0) {
      char input = Serial.read();  // Leer un solo byte
      if (input == 'S') {  // Si el carácter recibido es 'S', inicia el experimento
        startDrop();
        break;
      }
    }
  }
}

// Función para iniciar el experimento
void startDrop() {
  experimentStarted = true;
  startTime = millis();
  Serial.println("Esfera liberada, inicio de conteo...");
}

// Bucle principal
void loop() {
  if (experimentStarted) {
    // Detección del primer sensor infrarrojo
    if (timeIR1 == 0 && digitalRead(IR1) == HIGH) {
      timeIR1 = millis() - startTime;
      Serial.println("Paso por IR1 detectado. Tiempo: " + String(timeIR1) + " ms");
    }

    // Detección del segundo sensor infrarrojo
    if (timeIR2 == 0 && digitalRead(IR2) == HIGH) {
      timeIR2 = millis() - startTime;
      Serial.println("Paso por IR2 detectado. Tiempo: " + String(timeIR2) + " ms");
    }

    // Detección del tercer sensor infrarrojo
    if (timeIR3 == 0 && digitalRead(IR3) == HIGH) {
      timeIR3 = millis() - startTime;
      Serial.println("Paso por IR3 detectado. Tiempo: " + String(timeIR3) + " ms");
    }

    // Detección del sensor piezoeléctrico (final de la caída)
    if (timePiezo == 0 && digitalRead(PIEZO) == HIGH) {
      timePiezo = millis() - startTime;
      Serial.println("Impacto detectado en el sensor piezoeléctrico. Tiempo final: " + String(timePiezo) + " ms");

      // Cálculo y resultado final
      Serial.println("Tiempo total de caída: " + String(timePiezo) + " ms");
      experimentStarted = false;  // Terminar experimento
    }
  }
}
