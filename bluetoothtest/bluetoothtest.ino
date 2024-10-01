void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Serial3.begin(9600); // Inicializa a comunicação com o módulo Bluetooth (pinos Serial1)
}

void loop() {
  // Verifica se há dados disponíveis para leitura
  if (Serial3.available()) {
    char receivedChar = Serial3.read(); // Lê um caractere recebido
    Serial.print("Recebido: "); // Exibe no Serial Monitor
    Serial.println(receivedChar);
  }
}
