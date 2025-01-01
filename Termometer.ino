/*1янв25
Термометр
Проект 9
Scriptor42
*/
#include <OneWire.h>
#include <DallasTemperature.h>

//https://роботехника18.рф/%d1%82%d0%b5%d1%80%d0%bc%d0%be%d0%b4%d0%b0%d1%82%d1%87%d0%b8%d0%ba-%d0%b0%d1%80%d0%b4%d1%83%d0%b8%d0%bd%d0%be/
//
// Библиотека DallasTemperature может сделать это все за вас!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire oneWire(10);  // порт подключения датчика
DallasTemperature ds(&oneWire);

void setup() {
  Serial.begin(9600);   // инициализация монитора порта
  ds.begin();                 // инициализация датчика ds18b20
}

void loop() {
  ds.requestTemperatures();                       // считываем температуру с датчика
  
  Serial.print(ds.getTempCByIndex(0));   // выводим температуру на монитор
  Serial.println("C");
}