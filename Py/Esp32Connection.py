import serial
import time

# Configurar el puerto serie (ajusta 'COM3' o '/dev/ttyUSB0' según tu sistema)
esp32_port = 'COM10'  # Windows: 'COMx', Linux/Mac: '/dev/ttyUSBx'
baud_rate = 115200   # Debe coincidir con el baudrate del ESP32


class ESP32Connection:
    def __init__(self, port: str, baud_rate: int):
        self.port = port
        self.baud_rate = baud_rate
        self.serial_connection = None
    
    def startConnection(self):
        try:
            self.serial_connection = serial.Serial(self.port, self.baud_rate, timeout=1)
            print("Conectado al ESP32 en", self.port)
            time.sleep(2)
            
        except serial.SerialException as e:
            print("Error al conectar con el ESP32:", e)
    
    def endConnection(self) -> bool:
        if self.serial_connection is not None and self.serial_connection.is_open:
            self.serial_connection.close()
            print("Puerto serie cerrado")
            return True
        print("Error al cerrar el puerto")
        return False
    
    def sendCommand(self,command: str) -> bool:
        if self.serial_connection is not None and self.serial_connection.is_open:
            self.serial_connection.write(command.encode())
            return True
        print("Error al enviar el mensaje")
        return False
    
    def readResponse(self) -> str:
        if self.serial_connection is not None and self.serial_connection.is_open:
            response = self.serial_connection.readline().decode('utf-8').strip()
            return response
        print("Error al leer la respuesta")
        return ""
    
    def listeningResponses(self) -> list[str]:
        if self.serial_connection is not None and self.serial_connection.is_open:
            responses = []
            print("Escuchando respuestas...")
            while True:
                response = self.serial_connection.readline().decode('utf-8').strip()
                if response == '':
                    break
                responses.append(response)
            return responses
        print("Error al escuchar respuestas")
        return []
    
esp32 = ESP32Connection(esp32_port, baud_rate)

esp32.startConnection()
esp32.sendCommand("Prueba1")
respuestas = esp32.listeningResponses()
print(respuestas)
esp32.endConnection()