// Definimos el pin al que está conectado el sensor piezoeléctrico
const int piezoPin = 34; // GPIO34 (puedes cambiarlo a otro pin si lo necesitas)
int piezoValue = 0; // Variable para almacenar la lectura analógica del sensor

// Definimos un umbral (threshold) para detectar eventos
const int threshold = 400; // Ajusta este valor según lo que necesites

void setup() {
  // Iniciamos la comunicación serie para ver los valores en el monitor serie
  Serial.begin(115200);
  // Configuramos el pin del sensor como entrada
  pinMode(piezoPin, INPUT);
}

void loop() {
  // Leemos el valor analógico del sensor piezoeléctrico
  piezoValue = analogRead(piezoPin);
  
  // Imprimimos el valor leído en el monitor serie
  Serial.print("Valor piezoeléctrico: ");
  Serial.println(piezoValue);

  // Comprobamos si el valor leído excede el umbral
  if (piezoValue > threshold) {
    // Si el valor excede el umbral, imprimimos un mensaje de alerta
    Serial.println("¡Alerta! Se ha detectado una vibración fuerte.");
    // Aquí puedes realizar otras acciones, como encender un LED o activar una alarma
  }

  // Delay para evitar saturar el monitor serie
  delay(100);
}
