#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  
  // Inicializa I2C nos pinos padrão da ESP32
  Wire.begin(21, 22);

  Serial.println("Iniciando o sensor VL53L0XV2...");
  if (!lox.begin()) {
    Serial.println("Erro ao identificar o sensor! Verifique a fiação e o barramento I2C.");
    while (1);
  }

  // Configura para o modo de alta velocidade (High-Speed)
  // Nota: Isso aumenta a taxa de medição (~30-50 Hz), mas reduz levemente a precisão.
  lox.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_SPEED);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // Realiza o disparo de medição

  if (measure.RangeStatus != 4) { // Status 4 indica que o objeto está fora do alcance
    Serial.print("Distancia (mm): ");
    Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println("Fora de alcance!");
  }

  delay(20); // Intervalo mínimo de leitura (~50 Hz)
}