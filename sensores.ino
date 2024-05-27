#include <DHT.h>  //https://www.arduino.cc/reference/en/libraries/dht-sensor-library/

#define DHTPIN 3       // Define o pino ao qual o sensor está conectado
#define DHTTYPE DHT11  // Define o tipo do sensor (DHT11, DHT21, DHT22)

DHT dht(DHTPIN, DHTTYPE);

void verificarTemperaturaEumidade() {

  dht.begin();  // Inicia o sensor DHT

  float t = dht.readTemperature();  // Lê a temperatura em Celsius
  float u = dht.readHumidity();     // Lê a umidade relativa

  // Verifica se houve erro nas leituras
  if (isnan(t) || isnan(u)) {

    enviaDadosESP("temperatura", "Erro Sensor");
    delay(150);
    enviaDadosESP("umidade", "Erro Sensor");
    delay(150);
    return;
  }

  // Converter valores para String
  String temperatura = String(t, 1) + " °C";  // 1 indica uma casa decimal
  String umidade = String((int)u) + " %";

  // Envia dados para o site
  enviaDadosESP("temperatura", temperatura);
  delay(150);
  enviaDadosESP("umidade", umidade);
  delay(150);

  //Serial.println("Temperatura: " + temperatura);
  //Serial.println("Umidade: " + umidade);
}

#define sensorGas 2

void sensorGasEfumaca() {

  pinMode(sensorGas, INPUT);

  bool gas = !digitalRead(sensorGas);

}