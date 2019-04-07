#include <LiquidCrystal.h>
#include <SPI.h>  //Inclui a biblioteca de comunicação com o módulo (comunicação serial)
#include "RF24.h" //Inclui a biblioteca do módulo (interpretação)

RF24 radio(7,8);
LiquidCrystal lcd(6, 9, 5, 4, 3, 2); // Pinos do arduíno a serem dedicados ao módulo

void setup() {
    pinMode(4, OUTPUT); //Define o pino 4 como saída de sinal
    Serial.begin(115200); //Taxa de transmissão utilizada na comunicação com o arduíno
    lcd.begin(16, 2); //Inicializa o módulo LCD
    
    radio.begin();  //Inicializa o módulo RF
    radio.setPALevel(RF24_PA_MAX);  //Define  a potência do módulo
    radio.setChannel(125);  //Define a frequência utilizada pelo módulo (2400 + o número dos parênteses)
    radio.openReadingPipe(1,0xF0F0F0F0F0LL);  // openReadingPipe inicia o canal de recepção
    radio.openWritingPipe(0xF0F0F0F0AALL);  // openWritingPipe inicia o canal de transmissão
    radio.startListening();  //Faz com que o módulo comece de receber
    lcd.setCursor(0, 0);  //Define coluna e linha do texto no LCD
    lcd.print("Mensagem:"); //Imprime o texto na tela do LDC
}
void loop() {

    char texto[32]; //Variável do tipo texto
    char resposta[] = "OK"; //Variável do tipo texto, contendo a informação de resposta
    if(radio.available()){ //Se tiver informação para receber, executa:                                                            
      while (radio.available()) { //Enquanto estiver recebendo informação:                                  
        radio.read(&texto, sizeof(texto)); //Lê a mensagem recebida e guarda na variável "texto"
      }
      radio.stopListening();  //Para de receber
      radio.write(&resposta, sizeof(resposta)); //Envia uma resposta    
      radio.startListening(); //Começa a escutar de novo
      Serial.print(F("Recebido! Mensagem: ")); //Mensagem no monitor
      Serial.println(texto); //Mensagem recebida no monitor
      lcd.setCursor(0, 1);  //Define coluna e linha do texto na tela do LCD
      lcd.print(texto); //Imprime o texto recebido na tela do LCD
      delay(5000);
      lcd.clear();  //Limpa a tela
      lcd.setCursor(0, 0);  //Define coluna e linha do texto na tela do LCD
      lcd.print("Mensagem:"); //Imprime o texto na tela
   }
}
