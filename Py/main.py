import tkinter as tk
import serial
import threading

# Configuración de comunicación serial
SERIAL_PORT = "COM10"  # Cambia este puerto al adecuado
BAUD_RATE = 115200

# Función para leer datos desde el puerto serial
def leer_datos_serial():
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        while True:
            linea = ser.readline().decode("utf-8").strip()
            if "IR1" in linea:
                time_IR1.set(linea.split(":")[1].strip())
            elif "IR2" in linea:
                time_IR2.set(linea.split(":")[1].strip())
            elif "IR3" in linea:
                time_IR3.set(linea.split(":")[1].strip())
            elif "Impacto" in linea:
                time_PIEZO.set(linea.split(":")[1].strip())
            elif "Tiempo total" in linea:
                # Aquí podrías añadir cualquier acción final para cerrar o resetear la interfaz
                pass

# Función para enviar la señal de inicio a la ESP32
def enviar_inicio():
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE) as ser:
            ser.write(b'S')  # Enviar la señal 'S' para iniciar el experimento
            print("Señal de inicio enviada.")
    except Exception as e:
        print(f"Error al enviar señal de inicio: {e}")

# Configuración de la interfaz gráfica
def crear_interfaz():
    root = tk.Tk()
    root.title("Experimento de Caída Libre")
    root.geometry("800x600")

    # Crear variables de Tkinter después de inicializar la ventana principal
    global time_IR1, time_IR2, time_IR3, time_PIEZO
    time_IR1 = tk.StringVar(value="Esperando...")
    time_IR2 = tk.StringVar(value="Esperando...")
    time_IR3 = tk.StringVar(value="Esperando...")
    time_PIEZO = tk.StringVar(value="Esperando...")

    tk.Label(root, text="Tiempo paso IR1:").grid(row=0, column=0, padx=10, pady=10)
    tk.Label(root, textvariable=time_IR1).grid(row=0, column=1, padx=10, pady=10)

    tk.Label(root, text="Tiempo paso IR2:").grid(row=1, column=0, padx=10, pady=10)
    tk.Label(root, textvariable=time_IR2).grid(row=1, column=1, padx=10, pady=10)

    tk.Label(root, text="Tiempo paso IR3:").grid(row=2, column=0, padx=10, pady=10)
    tk.Label(root, textvariable=time_IR3).grid(row=2, column=1, padx=10, pady=10)

    tk.Label(root, text="Tiempo final impacto:").grid(row=3, column=0, padx=10, pady=10)
    tk.Label(root, textvariable=time_PIEZO).grid(row=3, column=1, padx=10, pady=10)

    # Botón para iniciar el experimento
    start_button = tk.Button(root, text="Iniciar Experimento", command=enviar_inicio)
    start_button.grid(row=4, column=0, columnspan=2, pady=20)

    # Iniciar hilo para leer el puerto serial
    hilo_serial = threading.Thread(target=leer_datos_serial, daemon=True)
    hilo_serial.start()

    root.mainloop()

# Llamada para iniciar la interfaz
crear_interfaz()
