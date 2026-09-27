#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Configuração do Botão
const int PINO_BOTAO = 18;       // Pino digital onde o botão está conectado
bool medindo = false;            // Armazena se está medindo (true) ou parado (false)
bool estadoBotaoAnterior = HIGH; // Estado do botão na leitura anterior
unsigned long ultimoDebounceTime = 0;
const unsigned long debounceDelay = 50; // Tempo de filtro para o botão (50ms)

void setup() {
  Serial.begin(115200);

  // Configura o pino do botão usando o resistor interno de PULLUP
  pinMode(PINO_BOTAO, INPUT_PULLUP);

  while (!Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  
  // Ajuste para maior precisão (~200ms por leitura)
  lox.setMeasurementTimingBudgetMicroSeconds(200000);
  
  Serial.println(F("VL53L0X API Simple Ranging example\n")); 
  Serial.println(">>> Pressione o botao para INICIAR / PARAR as meidcoes <<<\n");
}

void loop() {
  // --- LÓGICA DO BOTÃO (LIGA / DESLIGA) ---
  int leituraBotao = digitalRead(PINO_BOTAO);

  // Se o estado do botão mudou, reseta o temporizador de debounce
  if (leituraBotao != estadoBotaoAnterior) {
    ultimoDebounceTime = millis();
  }

  // Verifica se o sinal do botão ficou estável por tempo suficiente
  if ((millis() - ultimoDebounceTime) > debounceDelay) {
    // Quando o botão é pressionado (vai para LOW por causa do INPUT_PULLUP)
    static bool ultimoEstadoEstavel = HIGH;
    if (leituraBotao == LOW && ultimoEstadoEstavel == HIGH) {
      medindo = !medindo; // Inverte o estado (Se estava medindo -> para. Se estava parado -> começa)
      
      if (medindo) {
        Serial.println("\n--- MEDICAO INICIADA ---");
      } else {
        Serial.println("--- MEDICAO PAUSADA ---\n");
      }
    }
    ultimoEstadoEstavel = leituraBotao;
  }
  estadoBotaoAnterior = leituraBotao;

  // --- LÓGICA DE MEDIÇÃO ---
  // Só executa a leitura se a variável 'medindo' for verdadeira (true)
  if (medindo) {
    VL53L0X_RangingMeasurementData_t measure;
      
    Serial.print("Reading a measurement... ");
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4) { 
      Serial.print("Distance (mm): "); 
      Serial.println(measure.RangeMilliMeter);
    } else {
      Serial.println(" out of range ");
    }
      
    delay(100);
  }
}
