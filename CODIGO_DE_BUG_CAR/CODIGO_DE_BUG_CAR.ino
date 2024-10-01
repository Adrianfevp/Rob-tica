#include <Servo.h>

Servo servo;

const int MEF1 = 27; 
const int MEF2 = 25;  
const int MET1 = 24; 
const int MET2 = 26;
const int MDF1 = 31;
const int MDF2 = 29;
const int MDT1 = 28;
const int MDT2 = 30;
const int SERVO_PIN = 9;
const int BUZ = 8;     
const int TRIG = 44;    
const int ECHO = 42;    
const int LED = 39;    
#define SENSOR_E 48
#define SENSOR_D 49

const int BOTAO_PIN = 36; // Pino do botão

int modo = 1;           // Current mode
int lastModo = 0;       // Previous mode to detect mode changes
int ultimoEstadoBotao = HIGH; // Último estado do botão
unsigned long ultimoTempoBotao = 0; // Tempo da última leitura do botão
unsigned long tempoDebounce = 200; // Tempo de debounce (200 ms)

void setup() {
    Serial.begin(9600);
    Serial3.begin(9600);
    servo.attach(SERVO_PIN);
    pinMode(MEF1, OUTPUT);
    pinMode(MEF2, OUTPUT);
    pinMode(MET1, OUTPUT);
    pinMode(MET2, OUTPUT);
    pinMode(MDF1, OUTPUT);
    pinMode(MDF2, OUTPUT);
    pinMode(MDT1, OUTPUT);
    pinMode(MDT2, OUTPUT);
    pinMode(BUZ, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LED, OUTPUT);
    pinMode(SENSOR_D, INPUT);
    pinMode(SENSOR_E, INPUT);
    pinMode(BOTAO_PIN, INPUT_PULLUP); // Configura o pino do botão com pull-up interno

    digitalWrite(TRIG, LOW);
    servo.write(90);
    delay(2000);
}

void loop() {
    int leituraBotao = digitalRead(BOTAO_PIN);
    if (leituraBotao == LOW && (millis() - ultimoTempoBotao) > tempoDebounce) {
        ultimoTempoBotao = millis();

        if (ultimoEstadoBotao == HIGH) {
            modo++;
            if (modo > 3) modo = 1; // Se o modo for maior que 3, volta para 1
            Serial.print("Modo alterado para: ");
            Serial.println(modo);
        }
    }
    ultimoEstadoBotao = leituraBotao;

    if (modo != lastModo) {
        lastModo = modo;
        executarModo();
    }
}

void executarModo() {
    switch (modo) {
        case 1:
            piscarLedEBuzzer(1);
            bluetooth();
            break;
        case 2:
            piscarLedEBuzzer(2);
            seguelinha();
            break;
        case 3:
            piscarLedEBuzzer(3);
            autonomo();
            break;
    }
}

void piscarLedEBuzzer(int vezes) {
    for (int i = 0; i < vezes; i++) {
        digitalWrite(LED, HIGH);
        digitalWrite(BUZ, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        digitalWrite(BUZ, LOW);
        delay(500);
    }
}
void bluetooth() {
   while (modo == 1) {
     if (Serial3.available()) {
    char entrada = Serial3.read(); // Ler dados do módulo Bluetooth
    Serial.write(entrada);

        switch (entrada) {
            case 'F':    
                digitalWrite(MDF1, LOW);
                digitalWrite(MDF2, HIGH);   
                digitalWrite(MEF1, LOW);
                digitalWrite(MEF2, HIGH); 
                digitalWrite(MDT1, LOW);
                digitalWrite(MDT2, HIGH);   
                digitalWrite(MET1, HIGH);
                digitalWrite(MET2, LOW); 
                break;
            case 'B':    // Movimento para trás
                digitalWrite(MDF1, HIGH);
                digitalWrite(MDF2, LOW);   
                digitalWrite(MEF1, HIGH);
                digitalWrite(MEF2, LOW); 
                digitalWrite(MDT1, HIGH);
                digitalWrite(MDT2, LOW);   
                digitalWrite(MET1, LOW);
                digitalWrite(MET2, HIGH); 
                break;
            case 'L':    // Movimento para esquerda
                digitalWrite(MDF1, HIGH);
                digitalWrite(MDF2, LOW);   
                digitalWrite(MEF1, LOW);
                digitalWrite(MEF2, HIGH); 
                digitalWrite(MDT1, LOW);
                digitalWrite(MDT2, HIGH);   
                digitalWrite(MET1, LOW);
                digitalWrite(MET2, HIGH); 
                break;
            case 'R':    // Movimento para direita
                digitalWrite(MDF1, LOW);
                digitalWrite(MDF2, HIGH);   
                digitalWrite(MEF1, HIGH);
                digitalWrite(MEF2, LOW); 
                digitalWrite(MDT1, HIGH);
                digitalWrite(MDT2, LOW);   
                digitalWrite(MET1, HIGH);
                digitalWrite(MET2, LOW);  
                break;
            case 'S':    // Stop - sem movimento
                digitalWrite(MDF1, LOW);
                digitalWrite(MDF2, LOW);   
                digitalWrite(MEF1, LOW);
                digitalWrite(MEF2, LOW); 
                digitalWrite(MDT1, LOW);
                digitalWrite(MDT2, LOW);   
                digitalWrite(MET1, LOW);
                digitalWrite(MET2, LOW); 
                break;
            case 'V':    // Liga a buzina
                digitalWrite(BUZ, HIGH);                  
                break;
            case 'v':    // Desliga a buzina
                digitalWrite(BUZ, LOW);                  
                break;
            case 'W':    // Liga o led
                digitalWrite(LED, HIGH);                  
                break;
            case 'w':    // Desliga o led
                digitalWrite(LED, LOW);                  
                break;
                
        }
      }
      
        if (digitalRead(BOTAO_PIN) == LOW && (millis() - ultimoTempoBotao) > tempoDebounce) {
            ultimoTempoBotao = millis();
            modo++;
            if (modo > 3) modo = 1;
            Serial.print("Modo alterado para: ");
            Serial.println(modo);
        }
    }
}

void seguelinha() {
    while (modo == 2) {
        int sensorE = digitalRead(SENSOR_E);
        int sensorD = digitalRead(SENSOR_D);
        int velocidade = 100;
        if (sensorE == 1 && sensorD == 1) {       
            Serial.println("Detectou a linha preta nos dois sensores");
                digitalWrite(MDF1, 0);
                digitalWrite(MDF2, 0);
                digitalWrite(MEF1, 0);
                digitalWrite(MEF2, 0);
                digitalWrite(MDT1, 0);
                digitalWrite(MDT2, 0);
                digitalWrite(MET1, 0);
                digitalWrite(MET2, 0);
        } else if (sensorE == 1 && sensorD == 0) {     
            Serial.println("Detectou a linha preta na esquerda");
                digitalWrite(MDF1, velocidade);
                digitalWrite(MDF2, 0);   
                digitalWrite(MEF1, 0);
                digitalWrite(MEF2, velocidade); 
                digitalWrite(MDT1, 0);
                digitalWrite(MDT2, velocidade);   
                digitalWrite(MET1, 0);
                digitalWrite(MET2, velocidade); 
                
        } else if (sensorE == 0 && sensorD == 1) {    
            Serial.println("Detectou a linha preta na direita");
                digitalWrite(MDF1, 0);
                digitalWrite(MDF2, velocidade);   
                digitalWrite(MEF1, velocidade);
                digitalWrite(MEF2, 0); 
                digitalWrite(MDT1, velocidade);
                digitalWrite(MDT2, 0);   
                digitalWrite(MET1, velocidade);
                digitalWrite(MET2, 0); 
        } else {    
            Serial.println("Não detectou a linha preta nos dois sensores");
                digitalWrite(MDF1, 0);
                digitalWrite(MDF2, velocidade);   
                digitalWrite(MEF1, 0);
                digitalWrite(MEF2, velocidade); 
                digitalWrite(MDT1, 0);
                digitalWrite(MDT2, velocidade);   
                digitalWrite(MET1, velocidade);
                digitalWrite(MET2, 0);  
        }

        if (digitalRead(BOTAO_PIN) == LOW && (millis() - ultimoTempoBotao) > tempoDebounce) {
            ultimoTempoBotao = millis();
            modo++;
            if (modo > 3) modo = 1;
            Serial.print("Modo alterado para: ");
            Serial.println(modo);
        }
    }
}
void autonomo() { 
    while (modo == 3) {
  int tempo=0;
  long distancia=0;
  int tempo1=0;
  long distancia1=0;
  int tempo2=0;
  long distancia2=0;
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  tempo = pulseIn(ECHO, HIGH);
  delay(100);
  distancia=tempo*0.034/2;
  Serial.println(distancia);


  if(distancia<=25) {
      digitalWrite(MDF1, LOW);
      digitalWrite(MDF2, LOW);   
      digitalWrite(MEF1, LOW);
      digitalWrite(MEF2, LOW);   
      digitalWrite(MDT1, LOW);
      digitalWrite(MDT2, LOW);   
      digitalWrite(MET1, LOW);
      digitalWrite(MET2, LOW);   
      delay(300);
      digitalWrite(MDF1, HIGH);
      digitalWrite(MDF2, LOW);   
      digitalWrite(MEF1, HIGH);
      digitalWrite(MEF2, LOW); 
      digitalWrite(MDT1, HIGH);
      digitalWrite(MDT2, LOW);   
      digitalWrite(MET1, LOW);
      digitalWrite(MET2, HIGH);  
      delay(200);
      digitalWrite(MDF1, LOW);
      digitalWrite(MDF2, LOW);   
      digitalWrite(MEF1, LOW);
      digitalWrite(MEF2, LOW);   
      digitalWrite(MDT1, LOW);
      digitalWrite(MDT2, LOW);   
      digitalWrite(MET1, LOW);
      digitalWrite(MET2, LOW);   
      servo.write(0);
      delay(500);
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG, LOW);
      delayMicroseconds(2);
      tempo1=pulseIn(ECHO,HIGH);
      delay(100);
      distancia1=tempo1*0.034/2;
      int D = distancia1;     
      Serial.println(distancia1);
      servo.write(90);
      delay(500);
      servo.write(180);
      delay(500);
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG, LOW);
      delayMicroseconds(2);
      tempo2=pulseIn(ECHO,HIGH);
      delay(100);
      distancia2=tempo2*0.034/2;
      int E = distancia2;
      Serial.println(distancia2);
      servo.write(90);
      delay(500);
      if(D < E ) { 
          digitalWrite(MDF1, HIGH);
          digitalWrite(MDF2, LOW);   
          digitalWrite(MEF1, LOW);
          digitalWrite(MEF2, HIGH); 
          digitalWrite(MDT1, LOW);
          digitalWrite(MDT2, HIGH);   
          digitalWrite(MET1, LOW);
          digitalWrite(MET2, HIGH);
        delay(500); 
      } else if(D > E  ) {
          digitalWrite(MDF1, LOW);
          digitalWrite(MDF2, HIGH);   
          digitalWrite(MEF1, HIGH);
          digitalWrite(MEF2, LOW); 
          digitalWrite(MDT1, HIGH);
          digitalWrite(MDT2, LOW);   
          digitalWrite(MET1, HIGH);
          digitalWrite(MET2, LOW);   
        delay(500);
      }
    } else {
      digitalWrite(MDF1, LOW);
      digitalWrite(MDF2, HIGH);   
      digitalWrite(MEF1, LOW);
      digitalWrite(MEF2, HIGH);   
      digitalWrite(MDT1, HIGH);
      digitalWrite(MDT2, LOW);   
      digitalWrite(MET1, HIGH);
      digitalWrite(MET2, LOW); 
   }
        if (digitalRead(BOTAO_PIN) == LOW && (millis() - ultimoTempoBotao) > tempoDebounce) {
            ultimoTempoBotao = millis();
            modo++;
            if (modo > 3) modo = 1;
            Serial.print("Modo alterado para: ");
            Serial.println(modo);
        }
    }
}
