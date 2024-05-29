void enviaDadosESP(String sensor, String valor) {
  ComunicacaoUART.flush();
  ComunicacaoUART.print("{\"sensor\":\"");
  ComunicacaoUART.print(sensor);
  ComunicacaoUART.print("\",\"valor\":\"");
  ComunicacaoUART.print(valor);
  ComunicacaoUART.println("\"}");
  ComunicacaoUART.print("\n");
}

void recebeDadosESP() {
  static char dadosRecebidos[200];
  static unsigned int index = 0;
  static bool mensagemCompleta = false;

  while (ComunicacaoUART.available() > 0) {
    char c = ComunicacaoUART.read();

    if (c == '{') {  // Início de mensagem
      index = 0;
      mensagemCompleta = false;
    }

    if (!mensagemCompleta) {
      dadosRecebidos[index++] = c;

      if (c == '}') {                  // Fim de mensagem
        dadosRecebidos[index] = '\0';  // Termina a string
        mensagemCompleta = true;
        processaDadosRecebidos(dadosRecebidos);
        Serial.println(dadosRecebidos);
        break;
      }
    }
  }
}

void processaDadosRecebidos(char* dados) {
  String dadosStr(dados);

  // Encontra os índices do nome do dispositivo e do estado na mensagem
  int idxInicioNome = dadosStr.indexOf("\"") + 1;
  int idxFimNome = dadosStr.indexOf("\":", idxInicioNome);
  int idxInicioValor = idxFimNome + 3;
  int idxFimValor = dadosStr.indexOf("\"", idxInicioValor);

  String operacao = dadosStr.substring(idxInicioNome, idxFimNome);
  String valor = dadosStr.substring(idxInicioValor, idxFimValor);

  if ((operacao == "Temperatura") && (valor == "Ok")) {

    envioTemperatura = true;

  } else if ((operacao == "Umidade") && (valor == "Ok")) {

    envioUmidade = true;

  } else if ((operacao == "Gás e Fumaça") && (valor == "Ok")) {

    envioGasEfumaca = true;

  } else {
    // Processa os dispositivos conforme a lógica original
    controleDispositivos(operacao.c_str(), valor.c_str());
  }
}