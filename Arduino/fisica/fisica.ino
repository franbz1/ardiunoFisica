void setup() {
  pinMode(2, OUTPUT); // Configurar el pin GPIO2 como salida
  Serial.begin(115200); // Inicializar el puerto serie a 115200 baudios
  digitalWrite(2, LOW); // Asegurarte de que el LED esté apagado al inicio
}

void loop() {
  // Verificar si hay datos disponibles en el puerto serie
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // Leer datos hasta el salto de línea
    Serial.println("Recibido: " + data); // Responder con el mensaje recibido
    
    // Encender el LED si se recibe un mensaje
    if (data == "S") {
      digitalWrite(2, HIGH); // Encender el LED
      delay(1000);           // Mantenerlo encendido por 1 segundo
      digitalWrite(2, LOW);  // Apagar el LED después
    }
  }

  delay(100); // Retardo para evitar saturar el loop
}
