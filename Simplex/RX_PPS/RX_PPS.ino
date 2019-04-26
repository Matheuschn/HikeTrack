#include <LiquidCrystal.h>  //Inclui a biblioteca do LCD
#include <SPI.h>  //Inclui a biblioteca de comunicação com o módulo (comunicação serial)
#include "RF24.h" //Inclui a biblioteca do módulo (interpretação)

RF24 radio(7,8); // Pinos utilizados para comunicação com o módulo RF
LiquidCrystal lcd(6, 9, 5, 4, 3, 2); // Pinos do arduíno a serem dedicados ao módulo LCD

unsigned long pacotesrecebidos = 0;
unsigned long tempoultimaatt = 0;
unsigned long pacotestotal = 0;
char texto[32];
char textolcdpps[16];
char textolcdtotal[16];

void setup() {
    pinMode(4, OUTPUT); //Define o pino 4 como saída
    Serial.begin(115200); //Taxa de transmissão utilizada na comunicação com o arduíno
    lcd.begin(16, 2); //Inicializa o módulo LCD
    radio.begin();  //Inicializa o módulo RF
    
    radio.setPALevel(RF24_PA_MAX);  //Define  a potência do módulo RF
    radio.setDataRate(RF24_250KBPS);  //Define a taxa de transmissão
    radio.setAutoAck(false);  //Desabilita a confirmação de recebimento
    radio.setChannel(125);  //Define a frequência utilizada pelo módulo (2400 + o número dos parênteses)
    radio.openReadingPipe(1,0xF0F0F0F0F0LL);  // openReadingPipe inicia o canal de recepção
    radio.setCRCLength(RF24_CRC_8); //Define o tamanho campo de verificação de erros para 8
    radio.setPayloadSize(32);  //Define o tamanho da informação a ser enviada
    radio.startListening();  //Faz com que o módulo RF comece de receber
    lcd.clear(); //Limpa a tela do LCD
}

void loop() {                                                         
    while (radio.available()) { //Enquanto estiver recebendo informação:                                  
      radio.read(&texto, sizeof(texto)); //Lê a mensagem recebida e guarda na variável "texto"
      Serial.println("Recebido!");
      pacotesrecebidos++; //Adiciona 1 à variável de pacotes recebidos
    }

    unsigned long tempoatual = millis();  //Define uma variável com o tempo atual
    if(tempoatual - tempoultimaatt > 500) { //Caso faça mais de 500ms que a tela não é atualizada, roda o código abaixo
        lcd.clear();  //Limpa a tela
        pacotesrecebidos = pacotesrecebidos * 2;  //Multipilica a quantidade de pacotes recebidos em 500ms por 2, pra conseguir a quantidade de pacotes por segundo
        pacotestotal = pacotestotal + pacotesrecebidos; //Acrescenta a quantidade de pacotes recebidos nesses 500ms na variável de pacotes totais
        sprintf(textolcdpps, "PPS: %ld", pacotesrecebidos);  //Formata o texto pra ser enviado ao LCD
        lcd.setCursor(0, 0);  //Seleciona a linha de cima
        lcd.print(textolcdpps); //Envia o texto pra linha de cima
        sprintf(textolcdtotal, "Total: %ld", pacotestotal);  //Formata o texto pra ser enviado ao LCD
        lcd.setCursor(0, 1);  //Seleciona a linha de baixo
        lcd.print(textolcdtotal); //Envia o texto pra linha de baixo
        pacotesrecebidos = 0; //Zera a quantidade de pacotes recebidos
        tempoultimaatt = millis();  //Anota o tempo da última atualização da tela
    }

}
