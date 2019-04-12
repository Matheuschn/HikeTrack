#include <SPI.h>  //Inclui a biblioteca de comunicação com o módulo (comunicação serial)
#include "RF24.h" //Inclui a biblioteca do módulo (interpretação) 

RF24 radio(7,8);  //Pinos utilizados para comunicação como o rádio
int led = 6;  //Define a saída 6 do Arduino como o pino do LED

void setup() {
    Serial.begin(115200); //Taxa de transmissão utilizada na comunicação com o arduíno
    radio.begin();  //Inicializa o módulo
    radio.setDataRate(RF24_250KBPS);  //Define a taxa de transmissão
    radio.setPALevel(RF24_PA_MAX);  //Define  a potência do módulo RF
    radio.setChannel(125);  //Define a frequência utilizada pelo módulo (2400 + o número dos parênteses)
    radio.openWritingPipe(0xF0F0F0F0F0LL);  // openWritingPipe inicia o canal de transmissão  
    pinMode(led, OUTPUT); //Define o pino do LED como saída
    radio.setAutoAck(false); //Desabilita a confirmação de recebimento
    radio.setCRCLength(RF24_CRC_8); //Define o tamanho campo de verificação de erros para 8
    radio.setPayloadSize(1);  //Define o tamanho da informação a ser enviada como 1 byte
    radio.stopListening();  //Faz com que o módulo pare de receber
}

char texto[] = ""; //Variável do tipo texto vazia   

void loop() {                 
     radio.write(&texto, sizeof(texto));  //Envia o pacote
     Serial.print(F("Enviado"));
     digitalWrite(led, HIGH);  //Liga o LED
}
      
     
 
  
