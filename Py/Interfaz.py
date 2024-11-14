# interfaz.py

import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from conexion import ConexionSerial

class InterfazGrafica:
    def __init__(self, root, conexion_serial):
        self.root = root
        self.root.title("Interfaz de Mensajes y Gráficos")
        self.root.geometry("800x600")

        self.conexion = conexion_serial

        # Configurar la sección de mensajes
        self.texto_recibido = tk.Text(self.root, height=10, width=60, wrap=tk.WORD, state=tk.DISABLED)
        self.texto_recibido.pack(pady=10)

        # Configurar gráfico
        self.figura, self.ax = plt.subplots(figsize=(6, 4))
        self.canvas = FigureCanvasTkAgg(self.figura, self.root)
        self.canvas.get_tk_widget().pack(pady=10)
        
        # Configurar botones
        self.boton_actualizar = ttk.Button(self.root, text="Actualizar Gráfico", command=self.actualizar_grafico)
        self.boton_actualizar.pack(pady=10)  # Ajustar espacio de separación
        self.boton_refrescar = ttk.Button(self.root, text="Refrescar Datos", command=self.actualizar_interfaz)
        self.boton_refrescar.pack(pady=10)  # Empacar el nuevo botón para visibilidad

    def actualizar_interfaz(self):
        """Actualiza el área de texto con los mensajes recibidos"""
        mensajes = self.conexion.obtener_mensajes()
        if mensajes:
            self.texto_recibido.config(state=tk.NORMAL)
            self.texto_recibido.delete(1.0, tk.END)  # Limpiar el texto antes de añadir
            for mensaje in mensajes[-5:]:  # Solo mostrar los últimos 5 mensajes
                self.texto_recibido.insert(tk.END, mensaje + '\n')
            self.texto_recibido.yview(tk.END)
            self.texto_recibido.config(state=tk.DISABLED)

    def actualizar_grafico(self):
        """Genera un gráfico con los datos de los mensajes"""
        mensajes = self.conexion.obtener_mensajes()
        if mensajes:
            datos = [list(map(int, msg.split(','))) for msg in mensajes]
            datos = [item for sublist in datos for item in sublist]  # Aplanar la lista
            
            # Actualizar el gráfico
            self.ax.clear()
            self.ax.plot(datos, label='Datos recibidos', color='b')
            self.ax.set_title("Gráfico de Datos Recibidos")
            self.ax.set_xlabel("Índice")
            self.ax.set_ylabel("Valor")
            self.ax.legend()
            
            self.canvas.draw()  # Redibuja el gráfico

    def iniciar(self):
        """Inicia la interfaz gráfica"""
        self.conexion.iniciar_lectura()
        self.root.after(1000, self.actualizar_interfaz)  # Llama a actualizar cada 1 segundo
        self.root.mainloop()
