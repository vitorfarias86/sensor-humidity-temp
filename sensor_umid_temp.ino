#include <DHT.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN D3
#define DHTTYPE DHT22

// DISPLAY
#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

float umidade;
float temperatura;

void setup() {
  Serial.begin(115200);
  configurarDisplay();

}


void loop() {
  medirTemperaturaUmidade();
  mostrarTemperaturaUmidade();
}

void medirTemperaturaUmidade() {
  umidade = dht.readHumidity();
  temperatura = dht.readTemperature(false);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("ºC ");
  Serial.print("  ");
  Serial.print("Umidade: ");
  Serial.println(umidade);
  delay(5000);
}

void configurarDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();
}

void mostrarTemperaturaUmidade() {
  mostrarMensagemNoDisplay("Temperatura", (temperatura), " C");
  mostrarMensagemNoDisplay("Umidade", (umidade), " %");
}

void mostrarMensagemNoDisplay(const char* texto1, float medicao, const char* texto2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(texto1);
  display.setTextSize(2);
  display.setCursor(20, 20);
  display.print(medicao);
  display.setTextSize(1);
  display.print(texto2);
  display.display();
  delay(2000);
}

