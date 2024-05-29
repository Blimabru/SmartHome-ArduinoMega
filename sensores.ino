#include <DHT.h>  //https://www.arduino.cc/reference/en/libraries/dht-sensor-library/

#define DHTPIN 3       // Define o pino ao qual o sensor está conectado
#define DHTTYPE DHT11  // Define o tipo do sensor (DHT11, DHT21, DHT22)

DHT dht(DHTPIN, DHTTYPE);

#define SENSOR_GAS_PIN 2

void inicializaSensores() {
  pinMode(SENSOR_GAS_PIN, INPUT);
  dht.begin();  // Inicia o sensor DHT
}

void verificarTemperatura() {
  float temperatura = dht.readTemperature();  // Lê a temperatura em Celsius

  if (isnan(temperatura)) {
    enviaDadosESP("Temperatura", "Erro Sensor");
    return;
  }

  char tempStr[10];
  dtostrf(temperatura, 4, 1, tempStr);  // Converte temperatura para string

  enviaDadosESP("Temperatura", tempStr);
}


void verificarUmidade() {
  float umidade = dht.readHumidity();  // Lê a umidade relativa

  if (isnan(umidade)) {
    enviaDadosESP("Umidade", "Erro Sensor");
    return;
  }

  char umidStr[10];
  itoa((int)umidade, umidStr, 10);  // Converte umidade para string

  enviaDadosESP("Umidade", umidStr);
}

void sensorGasEfumaca() {
  bool valorGasEfumaca = !digitalRead(SENSOR_GAS_PIN);

  enviaDadosESP("Gás e Fumaça", valorGasEfumaca ? "1" : "0");
}