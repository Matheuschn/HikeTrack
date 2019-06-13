#include <SPI.h>  //Inclui a biblioteca de comunicação com o módulo (comunicação serial)
#include "RF24.h" //Inclui a biblioteca do módulo (interpretação)

RF24 radio(7,8); // Pinos utilizados para comunicação com o módulo RF

char textoRecebido[32];
char textoEnviado[32] = "";
byte enderecoRecebido;
byte enderecos[][6] = {"1GRPO","2GRPO","3GRPO","4GRPO","5GRPO"};  //Define os nomes dos grupos

void setup() {
    Serial.begin(115200); //Taxa de transmissão utilizada na comunicação com o arduíno
    radio.begin();  //Inicializa o módulo RF
    
    radio.setPALevel(RF24_PA_MIN);  //Define  a potência do módulo RF
    radio.setDataRate(RF24_250KBPS);  //Define a taxa de transmissão
    radio.setChannel(125);  //Define a frequência utilizada pelo módulo (2400 + o número dos parênteses)
    //radio.openWritingPipe(enderecos[0]);  // openWritingPipe inicia o canal de transmissão
    //radio.openWritingPipe(enderecos[1]);  // openWritingPipe inicia o canal de transmissão
    //radio.openWritingPipe(enderecos[2]);  // openWritingPipe inicia o canal de transmissão
    //radio.openWritingPipe(enderecos[3]);  // openWritingPipe inicia o canal de transmissão
    //radio.openWritingPipe(enderecos[4]);  // openWritingPipe inicia o canal de transmissão
    radio.openReadingPipe(1,enderecos[0]);  // openReadingPipe inicia o canal de recepção
    radio.openReadingPipe(2,enderecos[1]);  // openReadingPipe inicia o canal de recepção
    radio.openReadingPipe(3,enderecos[2]);  // openReadingPipe inicia o canal de recepção
    radio.openReadingPipe(4,enderecos[3]);  // openReadingPipe inicia o canal de recepção
    radio.openReadingPipe(5,enderecos[4]);  // openReadingPipe inicia o canal de recepção
    radio.setPayloadSize(32);  //Define o tamanho da informação a ser enviada
    radio.startListening();  //Faz com que o módulo RF comece de receber
}

void loop() {
                                                      
    if (radio.available(&enderecoRecebido)) { //Enquanto estiver recebendo informação:                                 
      radio.read(&textoRecebido, sizeof(textoRecebido)); //Lê a mensagem recebida e guarda na variável "texto"
      Serial.print("GRUPO ");
      Serial.print(enderecoRecebido);
      Serial.print(": ");
      Serial.println(textoRecebido);
    }

    if (Serial.available()) { //Se tiver mensagem pra enviar
      int len = Serial.readBytesUntil('\n', textoEnviado, 31);  //Corta a mensagem em 31 bytes
      textoEnviado[len] = '\0';
      radio.stopListening(); //Muda para o modo de transmissão
      radio.write(&textoEnviado, sizeof(textoEnviado)); //Transmite a mensagem
      Serial.println("Enviado.");
      radio.startListening(); //Volta para o modo recepção
    }
    
}
