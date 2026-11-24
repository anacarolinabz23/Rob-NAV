/**
  Robô NAV
  @authors Murilo Aguiar Cabral, Felipe, Guilherme, João Gustavo, Ana Carolina, Victor
  @version 1.0
  @link https://github.com/aguiarcabralmurilo-debug/robo-nav
*/
 
// Sensor ultrassônico
#define echo 11  //recebe o pulso
#define trig 12  //envia pulso
// LED indicador
#define led 13 // led indicador
// Motores
#define M1A 5 // Motor esquerda
#define M1B 6 // Motor esquerda
#define M2A 9 // Motor direita
#define M2B 10 // Motor direita

//Variáveis para ajuste de velocidade
int velM1 = 150; // velocidade do motor M1 (0 a 150)
int velM2 = 150; // velocidade do motor M2 (0 a 150)

void setup() {
  pinMode(led, OUTPUT);  // Led provisório
  pinMode(trig, OUTPUT); //Sensor
  pinMode(echo, INPUT); //Sensor
  pinMode(M1A, OUTPUT); //Motor esquerda
  pinMode(M1B, OUTPUT); //Motor esquerda
  pinMode(M2A, OUTPUT); //Motor direita
  pinMode(M2B, OUTPUT); //Motor direita
  Serial.begin(9600);  //teste do sonar
}
 
void loop() {
  // executa a função ping (dispara o pulso) e guarda na variável distancia
  int distancia = ping();
  Serial.print(distancia);
  Serial.println(" cm");
 
  //lógica principal
  if (distancia < 30) {
    digitalWrite(led, HIGH);
    parar();
    delay(1000); // ficar parado por 1s.
    direita(); // girar sentido horário
    delay(300); // por 300ms
  } else {
    digitalWrite(led, LOW);
    frente();
  }
 
  delay(60);  //60ms entre leituras para evitar eco residual
}
 
// função para ler o sensor e retornar o valor em cm.
int ping() {
  // iniciar o trig desligado
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // enviar pulso de 10 microsegundos
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // ler o tempo de duração(retorno) no echo
  long duracao = pulseIn(echo, HIGH);
  // converter para centímetros
  int distancia = duracao / 58.0;
  //retorna o valor da distância em cm
  return distancia;
}

//função para mover o robô para frente
void frente() {
  analogWrite(M1A, velM1);
  analogWrite(M1B, 0);
  analogWrite(M2A, velM2);
  analogWrite(M2B, 0);
}

// função para mover o robô de ré
void re(){
  analogWrite(M1B, velM1);
  analogWrite(M1A, 0);
  analogWrite(M2B, velM2);
  analogWrite(M2A, 0);
}

// função para virar o robô no sentido horário (direita)
void direita(){
  analogWrite(M1B, velM1);
  analogWrite(M1A, 0);
  analogWrite(M2A, velM2);
  analogWrite(M2B, 0);
}

// função para virar o robô no sentido anti-horário (esquerda)
void esquerda(){
  analogWrite(M1A, velM1);
  analogWrite(M1B, 0);
  analogWrite(M2B, velM2);
  analogWrite(M2A, 0);
}

//função parar o robô
void parar() {
  analogWrite(M1A, 0);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, 0);
  
}
