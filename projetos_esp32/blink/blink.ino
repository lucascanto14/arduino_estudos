// VIDA DE SILICIO
// KIT ESP32
// AULA 1 
// PROGRAMA 2 : BLINK
void setup() { 
pinMode(2, OUTPUT); //Configura o pino GPIO2 ou D2 como saída, permitindo que ele forneça um sinal elétrico com nível lógico alto ou baixo para controlar dispositivos externos.
} 


void loop() { 
digitalWrite(2, HIGH); // a função HIGH define a porta digital seu nível lógico como ALTO, assim ligando o led.
delay(5000); // Espera 5 segundos.
digitalWrite(2, LOW); // a função LOW define a porta digital seu nível lógico como BAIXO, assim desligando o led.
delay(1000); // Espera 1 segundo.
}