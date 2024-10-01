
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define LED_PIN 12
#define LED_COUNT 150

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Function declarations
void rainbow(int wait);
void colorWipe(uint32_t color, int wait);

bool rainbowActive = false;           // Indica se o efeito rainbow está ativo
unsigned long rainbowStartTime = 0;   // Armazena o momento em que o efeito rainbow foi iniciado
const unsigned long rainbowDuration = 10000;  // Duração do efeito rainbow em milissegundos (10 segundos)

void setup() {
  Serial.begin(9600);

  // Adjust clock speed for ATtiny85 if needed
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  strip.begin();           
  strip.show();           
  strip.setBrightness(50); 
}

void loop() {


void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
