#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <vector>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Configuração do Botão
const int PINO_BOTAO = 18;
bool medindo = false;
bool estadoBotaoAnterior = HIGH;
unsigned long ultimoDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Estrutura Lista de Listas
std::vector<uint16_t> sessaoAtual;
std::vector<std::vector<uint16_t>> historicoSessoes;

void imprimirHistoricoCompleto();

void setup() {
  Serial.begin(115200);
  pinMode(PINO_BOTAO, INPUT_PULLUP);

  while (!Serial) delay(1);

  Serial.println("Iniciando VL53L0X...");
  if (!lox.begin()) {
    Serial.println(F("Falha ao iniciar VL53L0X!"));
    while(1);
  }

  // --- CONFIGURAÇÃO DE LONGO ALCANCE E ALTA PRECISÃO NATIVA ---
  // Aplica os parâmetros internos de longo alcance configurados pela Adafruit
  lox.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE);

  // Aumenta a janela de leitura para ~200ms para maior estabilidade e precisão
  lox.setMeasurementTimingBudgetMicroSeconds(200000);

  Serial.println("Sensor configurado com sucesso para Longo Alcance!");
  Serial.println(">>> Pressione o botao para INICIAR / PAUSAR as medicoes <<<\n");
}

void loop() {
  // --- LÓGICA DO BOTÃO ---
  int leituraBotao = digitalRead(PINO_BOTAO);

  if (leituraBotao != estadoBotaoAnterior) {
    ultimoDebounceTime = millis();
  }

  if ((millis() - ultimoDebounceTime) > debounceDelay) {
    static bool ultimoEstadoEstavel = HIGH;
    if (leituraBotao == LOW && ultimoEstadoEstavel == HIGH) {
      medindo = !medindo;
      
      if (medindo) {
        sessaoAtual.clear();
        Serial.println("\n----------------------------------");
        Serial.print("--- SESSAO ");
        Serial.print(historicoSessoes.size() + 1);
        Serial.println(" INICIADA ---");
      } else {
        if (!sessaoAtual.empty()) {
          historicoSessoes.push_back(sessaoAtual);
        }
        Serial.println("--- SESSAO PAUSADA E SALVA ---");
        imprimirHistoricoCompleto();
      }
    }
    ultimoEstadoEstavel = leituraBotao;
  }
  estadoBotaoAnterior = leituraBotao;

  // --- LÓGICA DE MEDIÇÃO ---
  if (medindo) {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4) { 
      uint16_t distancia = measure.RangeMilliMeter;
      sessaoAtual.push_back(distancia);

      Serial.print("Distancia (mm): "); 
      Serial.print(distancia);
      Serial.print(" | [Lidos nesta sessao: ");
      Serial.print(sessaoAtual.size());
      Serial.println("]");
    } else {c:\Users\lucas\OneDrive\Documents\projeto_geral_baja\baja_piratas_do_vale\eletrica\hardware\datasheets\.gitkeep.txt
    }
      
    delay(100);
  }
}

void imprimirHistoricoCompleto() {
  Serial.println("\n===== HISTORICO COMPLETO DE MEDICOES =====");
  Serial.print("Total de sessoes registradas: ");
  Serial.println(historicoSessoes.size());

  for (size_t i = 0; i < historicoSessoes.size(); i++) {
    Serial.print("Sessao ");
    Serial.print(i + 1);
    Serial.print(" [");
    Serial.print(historicoSessoes[i].size());
    Serial.print(" medicoes]: { ");

    for (size_t j = 0; j < historicoSessoes[i].size(); j++) {
      Serial.print(historicoSessoes[i][j]);
      if (j < historicoSessoes[i].size() - 1) {
        Serial.print(", ");
      }
    }
    Serial.println(" }");
  }
  Serial.println("===========================================\n");
}