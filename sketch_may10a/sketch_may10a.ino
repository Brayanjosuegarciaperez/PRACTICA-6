#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

int RELAY_PIN = 8;   // Pin del módulo rele
int funcion = 0;
#define BUZZER_PIN 7  // Pin del zumbador
#define ONE_WIRE_BUS 2   // Pin del sensor de temperatura
#define WATER_TEMP_PRECISION 12  // Precisión del sensor de temperatura
#define WATERING_HOUR 0      // Hora a la que se activa el riego
#define WATERING_MINUTE 0   // Minuto a la que se activa el riego
#define WATERING_DURATION 20 // Duración del riego en segundos

// Inicializa los objetos para el RTC, la pantalla LCD y el sensor de temperatura
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.init();
  lcd.backlight();
  sensors.begin();
  rtc.begin();
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  sensors.requestTemperatures();
  if(funcion<452){
  	digitalWrite(RELAY_PIN,HIGH);
  	}
  	else{
  	digitalWrite(RELAY_PIN,LOW);
    delay(50);
  	}

  float waterTemp = sensors.getTempCByIndex(0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(waterTemp);
  lcd.setCursor(0, 1);
  lcd.print("Hora: ");
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  delay(1000);

  // Comprueba si es la hora de regar

  if(funcion<452){
  	digitalWrite(RELAY_PIN,HIGH);
  	}
  	else{
  	digitalWrite(RELAY_PIN,LOW);
  	}
delay(50);
    if (now.hour() == WATERING_HOUR && now.minute() == WATERING_MINUTE) {
    delay(50);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Riego en 10 seg.");
    tone(BUZZER_PIN, 1000, 5000); // sonido de alarma
     digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Regando...");
    digitalWrite(RELAY_PIN, LOW);  // Desactiva la bomba de agua
    delay(WATERING_DURATION * 1000);
    digitalWrite(RELAY_PIN, HIGH);  // activa la bomba de agua
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Riego terminado");
  }
  delay(1000);
}