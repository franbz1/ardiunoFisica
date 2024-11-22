from flask import Flask, jsonify, request
from Esp32Connection import ESP32Connection

esp32 = ESP32Connection(port='COM10', baud_rate=115200)

# Configuración del servidor Flask
app = Flask(__name__)

@app.route('/datos', methods=['GET'])
def get_data():
    """Endpoint para obtener los datos recopilados."""
    return jsonify({"data": esp32_server.data_buffer})

@app.route('/comando', methods=['POST'])
def send_command():
    """Endpoint para enviar comandos a la ESP32."""
    command = request.json.get('command', '')
    if esp32_server.ser and esp32_server.ser.is_open:
        esp32_server.ser.write(f"{command}\n".encode('utf-8'))
        return jsonify({"status": "Command sent"}), 200
    return jsonify({"error": "ESP32 not connected"}), 500

@app.route('/cerrar', methods=['POST'])
def close_connection():
    """Endpoint para cerrar la conexión con la ESP32."""
    esp32_server.close_serial()
    return jsonify({"status": "Connection closed"}), 200

if __name__ == '__main__':
    app.run(debug=True, port=5000)
