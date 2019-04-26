#include <SPI.h>  //Inclui a biblioteca de comunicação com o módulo (comunicação serial)
#include "RF24.h" //Inclui a biblioteca do módulo (interpretação) 

RF24 radio(7,8);  //Pinos utilizados para comunicação como o rádio

void setup() {
    radio.begin();  //Inicializa o módulo
    radio.setDataRate(RF24_250KBPS);  //Define a taxa de transmissão
    radio.setPALevel(RF24_PA_MAX);  //Define  a potência do módulo RF
    radio.setChannel(125);  //Define a frequência utilizada pelo módulo (2400 + o número dos parênteses)
    radio.openWritingPipe(0xF0F0F0F0F0LL);  // openWritingPipe inicia o canal de transmissão  
    radio.setAutoAck(false); //Desabilita a confirmação de recebimento
    radio.setCRCLength(RF24_CRC_8); //Define o tamanho campo de verificação de erros para 8
    radio.setPayloadSize(32);  //Define o tamanho da informação a ser enviada
    radio.stopListening();  //Faz com que o módulo pare de receber
}

char texto[] = ""; //Variável do tipo texto vazia   

void loop() {                 
     radio.write(&texto, sizeof(texto));  //Envia o pacote
}
