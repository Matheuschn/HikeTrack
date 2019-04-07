#include <SPI.h>  //Inclui a biblioteca de comunicação com o módulo (comunicação serial)
#include "RF24.h" //Inclui a biblioteca do módulo (interpretação) 

RF24 radio(7,8);
const int botao1 = 2;
const int botao2 = 3;
const int botao3 = 4;
int contato1 = 0;
int contato2 = 0;
int contato3 = 0;
void setup() {
    Serial.begin(115200); //Taxa de transmissão utilizada na comunicação com o arduíno
    pinMode(botao1, INPUT); //Define o pino 2 como entrada do sinal do botao
    pinMode(botao2, INPUT); //Define o pino 3 como entrada do sinal do botao
    pinMode(botao3, INPUT); //Define o pino 4 como entrada do sinal do botao
    radio.begin();  //Inicializa o módulo
    radio.setPALevel(RF24_PA_MAX);  //Define  a potência do módulo
    radio.setChannel(125);  //Define a frequência utilizada pelo módulo (2400 + o número dos parênteses)
    radio.openWritingPipe(0xF0F0F0F0F0LL);  // openWritingPipe inicia o canal de transmissão  
    radio.openReadingPipe(1,0xF0F0F0F0AALL);  // openReadingPipe inicia o canal de recepção
    
    radio.stopListening();  //Faz com que o módulo pare de receber
}
void loop() {
  
    contato1 = digitalRead(botao1); 
    contato2 = digitalRead(botao2); 
    contato3 = digitalRead(botao3); 
    if (contato1 == HIGH){
        delay(200);
        char texto[] = "Quebrei a perna!"; //Variável do tipo texto com a informação abc 
        //while (contato1 = HIGH){}
        Serial.print(F("Enviando. ")); //Mensagem na tela                         
         if (!radio.write(&texto, sizeof(texto))){  //Se houver erro durante a transmissão ou a mensagem enviada conter problemas, faça:
           Serial.print(F("Falha!")); //Mensagem de falha
         }else {
          Serial.println(F("Mensagem enviada.")); //Mensagem enviada
         }
    }
    if (contato2 == HIGH){
        delay(200);
        char texto[] = "Me perdi! Ajuda!"; //Variável do tipo texto com a informação abc 
        //while (contato2 = HIGH){}
        Serial.print(F("Enviando. ")); //Mensagem na tela                         
         if (!radio.write(&texto, sizeof(texto))){  //Se houver erro durante a transmissão ou a mensagem enviada conter problemas, faça:
           Serial.print(F("Falha!")); //Mensagem de falha
         }else {
          Serial.println(F("Mensagem enviada.")); //Mensagem enviada
         }
    }
    if (contato3 == HIGH){
        delay(200);
        char texto[] = "Ataque de cobra!"; //Variável do tipo texto com a informação abc 
        //while (contato3 = HIGH){}
        Serial.print(F("Enviando. ")); //Mensagem na tela                         
         if (!radio.write(&texto, sizeof(texto))){  //Se houver erro durante a transmissão ou a mensagem enviada conter problemas, faça:
           Serial.print(F("Falha!")); //Mensagem de falha
         }else {
          Serial.println(F("Mensagem enviada.")); //Mensagem enviada
         }
    }
}
