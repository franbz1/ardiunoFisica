import serial
import time

# Configurar el puerto serie (ajusta 'COM3' o '/dev/ttyUSB0' según tu sistema)
esp32_port = 'COM10'  # Windows: 'COMx', Linux/Mac: '/dev/ttyUSBx'
baud_rate = 115200   # Debe coincidir con el baudrate del ESP32

try:
    # Abrir el puerto serie
    ser = serial.Serial(esp32_port, baud_rate, timeout=1)
    print("Conectado al ESP32 en", esp32_port)
    time.sleep(2)  # Esperar a que el ESP32 esté listo

    # Enviar un mensaje al ESP32
    ser.write(b'S')
    print("Mensaje enviado")

    # Leer respuesta del ESP32
    response = ser.readline().decode('utf-8').strip()
    print("Respuesta del ESP32:", response)

except serial.SerialException as e:
    print("Error al conectar con el ESP32:", e)

finally:
    # Cerrar el puerto serie
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Puerto serie cerrado")
