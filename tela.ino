#include <LiquidCrystal_I2C.h>  // Download: www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/

LiquidCrystal_I2C lcd(0x27, 16, 2);


void iniciaDisplay() {

  lcd.begin(16, 2);
  lcd.init();

  msgInicial();
}

void msgInicial() {

  int tempoAnimacaoPontinhos = 100;

  lcd.clear();
  lcd.setBacklight(HIGH);

  Serial.println("Iniciando sistema... \n");

  lcd.setCursor(0, 0);
  lcd.print("   Iniciando    ");

  lcd.setCursor(0, 1);
  lcd.print("                ");

  // Animação de pontos
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.print(".");
    delay(tempoAnimacaoPontinhos);
  }

  piscaLcd();

  Serial.println("***************");
  Serial.println("*  SmartHome  *");
  Serial.println("*   Versão 2  *");
  Serial.println("*************** \n");

  lcd.setCursor(0, 0);
  lcd.print("   SmartHome    ");

  lcd.setCursor(0, 1);
  lcd.print("    Versao 2    ");
  delay(1000);

  piscaLcd();

  telaEspera();
}

void telaEspera() {

  lcd.setCursor(0, 0);
  lcd.print("    Projeto     ");

  lcd.setCursor(0, 1);
  lcd.print("   SmartHome    ");
}

void msgConectando() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Conectando ao  ");
  lcd.setCursor(0, 1);
  lcd.print("      WiFi      ");
}

void msgConectado(String wifiConectado) {

  piscaLcdDuplo();

  lcd.setCursor(0, 0);
  lcd.print("Conectado! WiFi:");

  lcd.setCursor(0, 1);
  lcd.print(wifiConectado);

  delay(1000);
}

void msgErroConexao(String status) {

  piscaLcdTriplo();

  lcd.setCursor(0, 0);
  lcd.print("      Erro      ");

  lcd.setCursor(0, 1);
  lcd.print(status);

  delay(1000);
}

void wifiDesconectado() {

  piscaLcdTriplo();

  lcd.setCursor(0, 0);
  lcd.print("Erro na conexao ");

  lcd.setCursor(0, 1);
   lcd.print("     Wi-Fi!     ");

  delay(1000);
}

void piscaLcd() {

  lcd.clear();
  lcd.setBacklight(LOW);
  delay(300);
  lcd.setBacklight(HIGH);
}

void piscaLcdDuplo() {

  lcd.clear();
  lcd.setBacklight(LOW);
  delay(150);
  lcd.setBacklight(HIGH);
  delay(150);
  lcd.setBacklight(LOW);
  delay(150);
  lcd.setBacklight(HIGH);
}

void piscaLcdTriplo() {

  lcd.clear();
  lcd.setBacklight(LOW);
  delay(250);
  lcd.setBacklight(HIGH);
  delay(250);
  lcd.setBacklight(LOW);
  delay(250);
  lcd.setBacklight(HIGH);
}