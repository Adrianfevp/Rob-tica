#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
Servo s6;
Servo s7;

void setup() {
  s1.attach(3);
  s2.attach(4);
  s3.attach(5);
  s4.attach(6);
  s5.attach(7);
  s6.attach(8);
  s7.attach(9);

  Em_cima();  
  delay(3000);
}

void loop() {
  Em_baixo(); delay(2000);
  Em_cima(); delay(2000);
  entra(); delay(2000);
}

void Em_cima(){
  s1.write(90);
  s2.write(90);
  s3.write(90);
  s4.write(90);
  s5.write(90);
  s6.write(90);
  s7.write(90);
}

void Em_baixo(){
  num9(); delay(1000);
  num8(); delay(1000);
  num7(); delay(1000);
  num6(); delay(1000);
  num5(); delay(1000);
  num4(); delay(1000);
  num3(); delay(1000);
  num2(); delay(1000);
  num1(); delay(1000);
  num0(); delay(1000);
}

void entra(){
  num0(); delay(1000);
  num1(); delay(1000);
  num2(); delay(1000);
  num3(); delay(1000);
  num4(); delay(1000);
  num5(); delay(1000);
  num6(); delay(1000);
  num7(); delay(1000);
  num8(); delay(1000);
  num9(); delay(1000);
}

// POSICAO DOS SERVOS SEGiNDO O NUMERO
void num0(){
  s1.write(180);
  s2.write(0);
  s3.write(180);
  s4.write(0);
  s5.write(0);
  s6.write(90);
  s7.write(180);
}

void num1(){
  s1.write(90);
  s2.write(0);
  s3.write(180);
  s4.write(90);
  s5.write(90);
  s6.write(90);
  s7.write(90);  
}

void num2(){
  s1.write(180);
  s2.write(0);
  s3.write(90);
  s4.write(0);
  s5.write(0);
  s6.write(180);
  s7.write(90);
}

void num3(){
  s1.write(180);
  s2.write(0);
  s3.write(180);
  s4.write(0);
  s5.write(90);
  s6.write(180);
  s7.write(90);  
}

void num4(){
  s1.write(90);
  s2.write(0);
  s3.write(180);
  s4.write(90);
  s5.write(90);
  s6.write(180);
  s7.write(180);  
}

void num5(){
  s1.write(180);
  s2.write(90);
  s3.write(180);
  s4.write(0);
  s5.write(90);
  s6.write(180);
  s7.write(180);
}

void num6(){
  s1.write(180);
  s2.write(90);
  s3.write(180);
  s4.write(0);
  s5.write(0);
  s6.write(180);
  s7.write(180);  
}

void num7(){
  s1.write(180);
  s2.write(0);
  s3.write(180);
  s4.write(90);
  s5.write(90);
  s6.write(90);
  s7.write(90);  
}

void num8(){
  s1.write(180);
  s2.write(0);
  s3.write(180);
  s4.write(0);
  s5.write(0);
  s6.write(180);
  s7.write(180);  
}

void num9(){
  s1.write(180);
  s2.write(0);
  s3.write(180);
  s4.write(0);
  s5.write(90);
  s6.write(180);
  s7.write(180);  
}
