#include <Arduino.h>

unsigned char btn0 = 0x00;

void setup() {
  DDRA = 0x00; //sebagai input
  DDRB = 0xFF; //sebagain output
}

void s0(){
  for (int i = 128; i >= 0; i--){
    if (i == 1 || i == 2 || i == 4 || i == 8 || i == 16 || i == 32 || i == 64 || i == 128){
      PORTB = i;
      _delay_ms(10);
    }
  }
}

void s1(){
  //Geser kiri 
  for (int i = 0; i <= 128; i++){
    if (i == 1 || i == 2 || i == 4 || i == 8 || i == 16 || i == 32 || i == 64 || i == 128){
      PORTB = i;
      _delay_ms(10);
    }
  }
}

void s2(){
  //Geser kiri kanan
  while(true){
    for (int i = 0; i <= 128; i++){
      if (i == 1 || i == 2 || i == 4 || i == 8 || i == 16 || i == 32 || i == 64 || i == 128){
        PORTB = i;
        _delay_ms(10);
      }
    }
    for (int j = 128; j >= 0; j--){
      if (j == 1 || j == 2 || j == 4 || j == 8 || j == 16 || j == 32 || j == 64 || j == 128){
        PORTB = j;
        _delay_ms(10);
      }
    }
  }
}

void loop() {
  // PINA = button;
  if (PINA == btn0){
    while (true){
      s0();
    }
  }
}