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

  Serial.println(dados);

  // Encontra os índices do nome do dispositivo e do estado na mensagem
  int idxInicioNome = dadosStr.indexOf("\"") + 1;
  int idxFimNome = dadosStr.indexOf("\":", idxInicioNome);
  int idxInicioValor = idxFimNome + 3;
  int idxFimValor = dadosStr.indexOf("\"", idxInicioValor);

  String operacao = dadosStr.substring(idxInicioNome, idxFimNome);
  String valor = dadosStr.substring(idxInicioValor, idxFimValor);
  bool enviado = "false";

  // Passa os valores extraídos para a função controleDispositivos
  if (operacao != "message") {
    controleDispositivos(operacao.c_str(), valor.c_str());
  } else {
    Serial.println("Mensagem do sistema\n");
  }
}