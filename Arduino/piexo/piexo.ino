const int piezoPin = 23;  // Pin donde está conectado el sensor piezoeléctrico (puede cambiar según tu conexión)
const int threshold = 10;  // Umbral para detectar una señal significativa (ajustable según tu sensor)

void setup() {
  Serial.begin(115200);  // Iniciar el puerto serial
  pinMode(piezoPin, INPUT);  // Configurar el pin del sensor como entrada
}

void loop() {
  int sensorValue = analogRead(piezoPin);  // Leer el valor analógico del sensor piezoeléctrico

  // Si la señal supera el umbral, enviamos un mensaje por la serial
  if (sensorValue > threshold) {
    Serial.println("¡Vibración o golpe detectado!");
  }
  
  delay(100);  // Pequeño retardo para evitar saturar la serial
}
