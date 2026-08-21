#include <Arduino.h>

const int RX1_PIN = 6; 
const int TX1_PIN = 7;

unsigned long ultimoMensajeViva = 0;

void setup() {
  Serial.begin(115200); 
  
  // OBLIGATORIO PARA ESP32-C3: Detener el programa hasta que el monitor USB de PlatformIO se abra
  while (!Serial) {
    delay(10); 
  }
  
  Serial.println("--- [CONEXIÓN USB ESTABLECIDA] ---");
  
  // Inicializamos la conexión con el LoRa
  Serial1.begin(9600, SERIAL_8N1, RX1_PIN, TX1_PIN);
  Serial.println("Buscando senal LoRa en pines 6 (RX) y 7 (TX)...");
}

void loop() {
  // 1. Verificar si hay datos que vengan desde el módulo LoRa
  if (Serial1.available()) {
    String mensaje = Serial1.readStringUntil('\n'); // Lee de forma más eficiente hasta el fin de línea
    Serial.print("[LoRa] Mensaje recibido: ");
    Serial.println(mensaje);
  }

  // 2. Mensaje de control: Imprime en PC cada 3 segundos para confirmar que la placa responde
  if (millis() - ultimoMensajeViva >= 3000) {
    Serial.println("[Sistema] El receptor funciona, esperando datos por antena...");
    ultimoMensajeViva = millis();
  }
}
