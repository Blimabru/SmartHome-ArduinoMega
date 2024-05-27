#define ComunicacaoUART Serial1

void setup() {
  Serial.begin(115200);
  ComunicacaoUART.begin(115200);  // Inicializa a comunicação serial com o ESP8266

  iniciaDisplay();
}

void loop() {
  recebeDadosESP();
  verificarTemperaturaEumidade();
  sensorGasEfumaca();

}
