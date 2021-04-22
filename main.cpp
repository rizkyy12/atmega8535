#include <Arduino.h>

unsigned char btn0 = 0x00;

void setup() {
  DDRA = 0x00; //sebagai input
  DDRA &= ~(1 << PINA0);
  DDRA &= ~(1 << PINA1);
  DDRA &= ~(1 << PINA2);
  DDRB = 0xFF; //sebagain output
}

void s0(){
  //Geser kanan
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
      if(bit_is_clear(PINA, 0)){
        s0();
        break;
      }
    }
  }
}

void s2(){
  //Geser kiri kanan
  for (int a = 0; a < 1; a++){
    for (int i = 0; i <= 128; i++){
      if (i == 1 || i == 2 || i == 4 || i == 8 || i == 16 || i == 32 || i == 64 || i == 128){
        PORTB = i;
        _delay_ms(10);
        if(bit_is_clear(PINA, 0)){
          s0();
          break;
        }
      }
    }
    continue;
    for (int j = 128; j >= 0; j--){
      if (j == 1 || j == 2 || j == 4 || j == 8 || j == 16 || j == 32 || j == 64 || j == 128){
        PORTB = j;
        _delay_ms(10);
      }
    }
  }
}

void loop() {
  while (1){
    if(bit_is_clear(PINA, 0)){
      s0();
    }
    else if(bit_is_clear(PINA, 1)){
      s1();
    }
    else if(bit_is_clear(PINA, 2)){
      s2();
    }
  }
}