// Conecte o pino TX do ESP8266 ao pino RX1 (19) do Arduino Mega.
// Conecte o pino RX do ESP8266 ao pino TX1 (18) do Arduino Mega.
// Conecte os pinos GND de ambos os dispositivos.

void enviaDadosESP(String dispositivo, String valor) {
  
  ComunicacaoUART.flush();
  ComunicacaoUART.println("Sensor: " + dispositivo + " - Valor: " + valor);

  delay(150);
}


void recebeDadosESP() {
  if (ComunicacaoUART.available() > 0) {                            // Verifica se há dados disponíveis para leitura
    String dadosRecebidos = ComunicacaoUART.readStringUntil('\n');  // Lê a mensagem recebida

    Serial.print("Recebe ESP: ");
    Serial.println(dadosRecebidos);
    Serial.print("\n");
    
    int idxDispositivo = dadosRecebidos.indexOf("Dispositivo: "); // Localiza a posição da substring "Dispositivo: " na mensagem recebida
    int idxEstado = dadosRecebidos.indexOf(" - Estado: ");  // Localiza a posição da substring " - Estado: " na mensagem recebida

    // Verifica se ambas as substrings foram encontradas
    if (idxDispositivo != -1 && idxEstado != -1) {
      // Extrai o nome do dispositivo a partir da posição após "Dispositivo: "
      String dispositivo = dadosRecebidos.substring(idxDispositivo + 13, idxEstado);

      // Extrai o estado a partir da posição após " - Estado: "
      String estado = dadosRecebidos.substring(idxEstado + 11);

      dispositivo.trim(); // Apagar espaços em branco
      estado.trim(); // Apagar espaços em branco

      // Chama a função para processar e exibir o nome do dispositivo e seu estado
      controleDispositivos(dispositivo, estado);
      delay(150);
    }
  }
}