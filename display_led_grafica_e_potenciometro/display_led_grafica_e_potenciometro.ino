const int LEDs = 10;
const int pinosLEDs[] = {3,4,5,6,7,8,9,10,11,12};
const int pot = A0;
int potenciometro = 0;
int barraleds = 0;
void setup() {
  for (int i=0; i<=LEDs; i++) {
    pinMode(pinosLEDs[i], OUTPUT);
  }
}
void loop() {
  potenciometro = analogRead(pot);
  barraleds = map(potenciometro,0,1023,0,10);
  for (int i=0; i<LEDs; i++) {
    if (i < barraleds) {
      digitalWrite(pinosLEDs[i], HIGH);
    }
    else {
      digitalWrite(pinosLEDs[i],LOW);
    }
  }
}
