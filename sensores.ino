#include <DHT.h>  // https://www.arduino.cc/reference/en/libraries/dht-sensor-library/

#define DHTPIN 3       // Define o pino ao qual o sensor está conectado
#define DHTTYPE DHT11  // Define o tipo do sensor (DHT11, DHT21, DHT22)

DHT dht(DHTPIN, DHTTYPE);

#define SENSOR_GAS_PIN 2

bool envioTemperatura = false;
bool envioUmidade = false;
bool envioGasEfumaca = false;

void inicializaSensores() {
  pinMode(SENSOR_GAS_PIN, INPUT);
  dht.begin();  // Inicia o sensor DHT
}

unsigned long tempoInicio = 0;  // Variável para armazenar o tempo inicial

void verificarSensores() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoInicio >= 5000) {  // Verifica se passaram 5 segundos (5000 ms)
    tempoInicio = tempoAtual;              // Atualiza o tempo de início para o próximo intervalo
    Serial.println("\nVerificando dados dos sensores:");
    verificarTemperatura();
    verificarUmidade();
    sensorGasEfumaca();
    envioTemperatura = false;
    envioUmidade = false;
    envioGasEfumaca = false;
  }
}

void verificarTemperatura() {
  float temperatura;
  unsigned long tempoInicioFuncao = millis();

  // while (millis() - tempoInicioFuncao < 1000) {  // Executa por 1 segundo
    temperatura = dht.readTemperature();         // Lê a temperatura em Celsius
    if (!isnan(temperatura)) {
      char tempStr[10];
      dtostrf(temperatura, 4, 1, tempStr);  // Converte temperatura para string
      enviaDadosESP("Temperatura", tempStr);
      Serial.print("Temperatura: ");
      Serial.print(tempStr);
      Serial.println(" °C");
    }
  // }
  if (envioTemperatura) return;  // Se envioTemperatura for true, sair da função
}

void verificarUmidade() {

  float umidade;
  unsigned long tempoInicioFuncao = millis();

  // while (millis() - tempoInicioFuncao < 1000) {  // Executa por 1 segundo
    umidade = dht.readHumidity();                // Lê a umidade relativa
    if (!isnan(umidade)) {
      char umidStr[10];
      itoa((int)umidade, umidStr, 10);  // Converte umidade para string
      enviaDadosESP("Umidade", umidStr);
      Serial.print("Umidade: ");
      Serial.print(umidStr);
      Serial.println(" %");
    }
  // }
  if (envioUmidade) return;  // Se envioUmidade for true, sair da função
}

void sensorGasEfumaca() {

  bool valorGasEfumaca;
  unsigned long tempoInicioFuncao = millis();

  // while (millis() - tempoInicioFuncao < 1000) {  // Executa por 1 segundo
    valorGasEfumaca = !digitalRead(SENSOR_GAS_PIN);
    enviaDadosESP("Gás e Fumaça", valorGasEfumaca ? "1" : "0");
    Serial.print("Gás e Fumaça: ");
    Serial.println(valorGasEfumaca ? "Detectado!\n" : "Ar limpo\n");
  // }
  if (envioGasEfumaca) return;  // Se envioGasEfumaca for true, sair da função
}