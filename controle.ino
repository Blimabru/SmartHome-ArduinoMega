#define led1  22
#define led2  23
#define led3  24
#define led4  25
#define led5  26
#define led6  27
#define led7  28
#define led8  29
#define led9  30
#define led10 31

void controleDispositivos(String dispositivo, String estado) {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  if (dispositivo == "luz-andar00-sala01") {

    if (estado == "1") {

      digitalWrite(led1, HIGH);

    } else if (estado == "0") {

      digitalWrite(led1, LOW);
    }
  }

  if (dispositivo == "luz-andar00-sala02") {

    if (estado == "1") {

      digitalWrite(led2, HIGH);

    } else if (estado == "0") {
      
      digitalWrite(led2, LOW);
    }
  }

}