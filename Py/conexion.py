# conexion.py
import serial
import time
import threading

class ConexionSerial:
    def __init__(self, puerto, velocidad=115200):
        self.puerto = puerto
        self.velocidad = velocidad
        self.ser = None
        self.mensajes = []
        self._hilo_lectura = None
        self._detener = False

    def conectar(self):
        """Inicia la conexión serial"""
        try:
            self.ser = serial.Serial(self.puerto, self.velocidad)
            time.sleep(2)  # Espera para asegurar que el puerto se inicialice correctamente
            print(f"Conexión establecida en {self.puerto} a {self.velocidad} baudios.")
        except Exception as e:
            print(f"Error al conectar: {e}")
            return False
        return True

    def leer_mensajes(self):
        """Lee mensajes del puerto serial de manera continua en un hilo"""
        while not self._detener:
            if self.ser.in_waiting > 0:
                mensaje = self.ser.readline().decode('utf-8').strip()
                self.mensajes.append(mensaje)
                time.sleep(0.1)

    def iniciar_lectura(self):
        """Inicia el hilo para leer los mensajes"""
        self._detener = False
        self._hilo_lectura = threading.Thread(target=self.leer_mensajes, daemon=True)
        self._hilo_lectura.start()

    def detener_lectura(self):
        """Detiene la lectura y el hilo"""
        self._detener = True
        if self._hilo_lectura:
            self._hilo_lectura.join()

    def obtener_mensajes(self):
        """Devuelve los mensajes leídos"""
        return self.mensajes[-5:]  # Devolver solo los últimos 5 mensajes

    def cerrar_conexion(self):
        """Cierra la conexión serial"""
        if self.ser:
            self.ser.close()
            print("Conexión cerrada.")
