// VIDA DE SILICIO
// KIT ESP32
// AULA 1 
// PROGRAMA 1 : HELLO WORLD

void setup() // SETUP: Define as funções que o ESP32 realizará apenas uma vez após sua inicialização.
{
Serial.begin(115200); // Define a velocidade de comunicação serial entre o microcontrolador e o dispositivo externo conectado a ele.
// Certifique-se de que o valor de 115200 baund descrito no programa seja a mesma taxa no seu monitor serial.

}

void loop() // LOOP: Define as funções que o ESP32 realizará repetidas vezes enquanto o programa solitar ou estiver ligado. 
{
Serial.println("Hello World!"); // Imprime no monitor serial a frase escrita entre as aspas.
delay(1000); // Atraso de 1000 milisegundos ou 1 segundo.
}