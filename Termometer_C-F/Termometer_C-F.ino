/*1янв25
Термометр C / F
Проект 9
Scriptor42
*/
/*Сборный скетч */

#include "OneWire.h"
#include "DallasTemperature.h"
 
OneWire oneWire(10);  // Порт подключения датчиков
DallasTemperature ds(&oneWire);

void setup() {
  Serial.begin(9600);   // Инициализация монитора порта
  ds.begin();                 // Инициализация датчика ds18b20
}

void loop() {

ds.requestTemperatures();
Serial.print("Celsius temperature: ");
  // "Температура в Цельсиях: "
  // Почему "byIndex"? к одной шине может быть подключено 
  // больше одного датчика; самое первое устройство на шине - это "0":
  //float temperatureC = ds.getTempCByIndex(0);
  Serial.print(ds.getTempCByIndex(0));
  Serial.print(" - Fahrenheit temperature: ");
  //  " - Температура в Фаренгейтах: "
  Serial.println(ds.getTempFByIndex(0));
  delay(1000);
}