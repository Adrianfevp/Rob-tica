#include <LiquidCrystal.h>
#include <DHT.h> 

#define Dht DHT11
#define Dhtpin A2
#define Umidpin A1

const int pinRelay = 8;

DHT dht(Dhtpin, Dht);
LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  dht.begin();
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, LOW);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    lcd.print("Error");
  } else {
    lcd.print(temp, 1);
    lcd.print("C"); 
  }

  lcd.setCursor(0, 1);
  lcd.print("Umid : ");
  lcd.setCursor(7, 1);
  float hum = dht.readHumidity();
  if (isnan(hum)) {
    lcd.print("Error");
  } else {
    lcd.print(hum, 1);
    lcd.print("%");
  }
  Serial.print("Temperatura ambiente: ");
  Serial.print(temp);
  Serial.print("  Umidade ambiente: ");
  Serial.println(hum);
  
  int Dados_sensor = analogRead(Umidpin);
  int Umid = map(Dados_sensor, 0, 1023, 100, 0);
  Serial.print("Umidade do solo:");
  Serial.println(Umid);
  if (Umid >= 50) {
    digitalWrite(pinRelay, HIGH);
  } else { 
    digitalWrite(pinRelay, LOW);
  }
  delay(1000);
}
