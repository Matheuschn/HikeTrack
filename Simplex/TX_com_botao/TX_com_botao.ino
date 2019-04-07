#include <SPI.h>  //Inclui a biblioteca de comunicação com o módulo (comunicação serial)
#include "RF24.h" //Inclui a biblioteca do módulo (interpretação) 

RF24 radio(7,8);
const int botao1 = 2; //Define o pino 2 como entrada do sinal do botao1
const int botao2 = 3; //Define o pino 3 como entrada do sinal do botao2
const int botao3 = 4; //Define o pino 4 como entrada do sinal do botao3
int contato1 = 0;
int contato2 = 0;
int contato3 = 0;
int led_confirmacao = 6;
void setup() {
    Serial.begin(115200); //Taxa de transmissão utilizada na comunicação com o arduíno
    pinMode(botao1, INPUT); //Define o botão 1 como sinal de entrada
    pinMode(botao2, INPUT); //Define o botão 2 como sinal de entrada
    pinMode(botao3, INPUT); //Define o botão 3 como sinal de entrada
    pinMode(led_confirmacao, OUTPUT); //Define o pino 6 (led_confirmacao) como saída de sinal
    radio.begin();  //Inicializa o módulo
    radio.setPALevel(RF24_PA_MAX);  //Define a potência do módulo
    radio.setChannel(125);  //Define a frequência utilizada pelo módulo (2400 + o número dos parênteses)
    radio.openWritingPipe(0xF0F0F0F0F0LL);  // openWritingPipe inicia o canal de transmissão  
    radio.openReadingPipe(1,0xF0F0F0F0AALL);  // openReadingPipe inicia o canal de recepção
    
    radio.stopListening();  //Faz com que o módulo pare de receber
}
void loop() {
    contato1 = digitalRead(botao1); // Realacionando o contato 1 com a leitura da entrada do botão1 na porta do arduíno
    contato2 = digitalRead(botao2); // Realacionando o contato 2 com a leitura da entrada do botão2 na porta do arduíno
    contato3 = digitalRead(botao3); // Realacionando o contato 3 com a leitura da entrada do botão3 na porta do arduíno
    if (contato1 == HIGH){ // Se o botão estiver sendo pressionado (contato), faça:
        delay(500); // tempo máximo que o botão pode ficar apertado
        char texto[] = "Quebrei a perna!"; // Variável do tipo texto com a informação a ser transmitida
        Serial.print(F("Enviando. ")); //Mensagem na tela                         
         if (!radio.write(&texto, sizeof(texto))){  //Se houver erro durante a transmissão ou a mensagem enviada conter problemas, faça:
           Serial.println(F("Falha!")); //Mensagem de falha
         }else {
          digitalWrite (led_confirmacao, HIGH); // Acende o led de confirmação
          delay(500); // Delay de meio segundo até o led apagar
          digitalWrite (led_confirmacao, LOW); // Apaga o led de confirmação
          Serial.println(F("Mensagem enviada.")); //Mensagem enviada
         }
    }
    if (contato2 == HIGH){ // Se o botão estiver sendo pressionado (contato), faça:
        delay(500); // tempo máximo que o botão pode ficar apertado
        char texto[] = "Me perdi! Ajuda!"; // Variável do tipo texto com a informação a ser transmitida
        Serial.print(F("Enviando. ")); //Mensagem na tela                         
         if (!radio.write(&texto, sizeof(texto))){  //Se houver erro durante a transmissão ou a mensagem enviada conter problemas, faça:
           Serial.println(F("Falha!")); //Mensagem de falha
         }else {
          digitalWrite (led_confirmacao, HIGH); // Acende o led de confirmação
          delay(500); // Delay de meio segundo até o led apagar
          digitalWrite (led_confirmacao, LOW); // Apaga o led de confirmação
          Serial.println(F("Mensagem enviada.")); //Mensagem enviada
         }
    }
    if (contato3 == HIGH){ // Se o botão estiver sendo pressionado (contato), faça:
        delay(500); // tempo máximo que o botão pode ficar apertado
        char texto[] = "Ataque de cobra!"; // Variável do tipo texto com a informação a ser transmitida
        Serial.print(F("Enviando. ")); //Mensagem na tela                         
         if (!radio.write(&texto, sizeof(texto))){  //Se houver erro durante a transmissão ou a mensagem enviada conter problemas, faça:
           Serial.println(F("Falha!")); //Mensagem de falha
         }else { 
          digitalWrite (led_confirmacao, HIGH); // Acende o led de confirmação
          delay(500); // Delay de meio segundo até o led apagar
          digitalWrite (led_confirmacao, LOW); // Apaga o led de confirmação
          Serial.println(F("Mensagem enviada.")); //Mensagem enviada
         }
     }
         
  }
