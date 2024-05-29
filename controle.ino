#define NUM_DISPOSITIVOS 15

const int leds[NUM_DISPOSITIVOS] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 };
const char* dispositivos[NUM_DISPOSITIVOS] = {
  "luz-cantina",
  "luz-andar00-sala01",
  "luz-andar00-sala02",
  "luz-banheiro-masculino",
  "luz-banheiro-feminino",
  "luz-hall",
  "luz-apartamento",
  "luz-andar01-sala01",
  "luz-area-circulacao",
  "luz-cozinha",
  "luz-area-servico",
  "luz-suite",
  "luz-banheiro-suite",
  "luz-banheiro-social",
  "luz-estufa"
};

bool estadosDispositivos[NUM_DISPOSITIVOS] = { false }; // Armazena o estado atual de cada dispositivo

void configuraPinos() {
  for (int i = 0; i < NUM_DISPOSITIVOS; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW); // Inicializa todos os LEDs como desligados
  }
}

void controleDispositivos(const char* dispositivo, const char* estado) {
  for (int i = 0; i < NUM_DISPOSITIVOS; i++) {
    if (strcmp(dispositivo, dispositivos[i]) == 0) {
      bool novoEstado = (estado[0] == '1');
      if (estadosDispositivos[i] != novoEstado) {
        digitalWrite(leds[i], novoEstado ? HIGH : LOW);
        estadosDispositivos[i] = novoEstado; // Atualiza o estado atual
      }
      break;
    }
  }
}