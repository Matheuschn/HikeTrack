int tempoPonto = 333;
int tempoTraco = 1000;
int tempoIntervalo = 333;
int tempoIntervaloLetras = 666;
int tempoIntervaloPalavras = 1333;

void setup() {
  pinMode(13, OUTPUT);  //Inicializa o pino 13 como saída
}

void ponto() {
  digitalWrite(13, HIGH);
  delay(tempoPonto);
  digitalWrite(13, LOW);
  delay(tempoIntervalo);
}

void traco() {
  digitalWrite(13, HIGH);
  delay(tempoTraco);
  digitalWrite(13, LOW);
  delay(tempoIntervalo);
}

void S() {
  ponto();
  ponto();
  ponto();
  delay(tempoIntervaloLetras);
}

void O() {
  traco();
  traco();
  traco();
  delay(tempoIntervaloLetras);
}
void loop() {
  S();
  O();
  S();
  delay(tempoIntervaloPalavras);
}
