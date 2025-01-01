/*1янв25
Термометр
Проект 9
Scriptor42
*/
/*Сборный скетч */

#include "OneWire.h"
#include "DallasTemperature.h"
 
OneWire oneWire(10);  // порт подключения датчиков
DallasTemperature ds(&oneWire);

void setup() {
  Serial.begin(9600);   // инициализация монитора порта
  ds.begin();                 // инициализация датчика ds18b20
}

void loop() {

ds.requestTemperatures();
  float temperatureC = ds.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  delay(1000);
}