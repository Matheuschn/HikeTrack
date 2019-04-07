#include <SPI.h>  //Inclui a biblioteca de comunicação com o módulo (comunicação serial)
#include "RF24.h" //Inclui a biblioteca do módulo (interpretação) 

RF24 radio(7,8);

void setup() {
    Serial.begin(115200); //Taxa de transmissão utilizada na comunicação com o arduíno
    
    radio.begin();  //Inicializa o módulo
    radio.setPALevel(RF24_PA_MAX);  //Define  a potência do módulo
    radio.setChannel(125);  //Define a frequência utilizada pelo módulo (2400 + o número dos parênteses)
    radio.openWritingPipe(0xF0F0F0F0F0LL);  // openWritingPipe inicia o canal de transmissão  
    radio.openReadingPipe(1,0xF0F0F0F0AALL);  // openReadingPipe inicia o canal de recepção
    
    radio.stopListening();  //Faz com que o módulo pare de receber
}
void loop() {
    Serial.print(F("Enviando. ")); //Mensagem na tela
    char texto[] = "abc"; //Variável do tipo texto com a informação abc                         
     if (!radio.write(&texto, sizeof(texto))){  //Se houver erro durante a transmissão ou a mensagem enviada conter problemas, faça:
       Serial.print(F("Falha!")); //Mensagem de falha
     }else {
      Serial.println(F("Mensagem enviada.")); //Mensagem enviada
     }
  }
