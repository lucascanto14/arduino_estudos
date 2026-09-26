//receptor esp32 lora telemetria
#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(915E6)) {
    Serial.println("Erro ao iniciar Receptor!");
    while (true);
  }

  LoRa.setSpreadingFactor(7);
  Serial.println("--- BASE TELEMETRIA BAJA (AGUARDANDO DADOS) ---");
  Serial.println("Formato: RPM;TempMotor;TempCVT;Combustivel;Velocidade;Satelites | RSSI");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    String dados = "";
    while (LoRa.available()) {
      dados += (char)LoRa.read();
    }

    // Exibe no Serial para leitura direta no Python, Serial Plotter ou Excel
    Serial.print(dados);
    Serial.print(";");
    Serial.println(LoRa.packetRssi()); // Adiciona o nível do sinal no final
  }
}