/*1янв25
Термометр
Проект 9
Этап 2
Scriptor42
*/
/*Сборный скетч */

/*Термометр на Arduino и термодатчике DS18B20 */

/*Подключение библиотек*/
#include "OneWire.h"
#include "DallasTemperature.h"
 
OneWire oneWire(10);    // выбор порта 10 для подключения датчика
DallasTemperature ds(&oneWire);    //обмен данными  по протоколу 1-Wire 

void setup() {
  Serial.begin(9600);   // инициализация монитора порта
  ds.begin();    // инициализация датчика ds18b20
}

void loop() {
ds.requestTemperatures();    // запрос температуры
  Serial.print("Temperature: ");  // вывод на монитор порта имя параметра
  Serial.print(ds.getTempCByIndex(0));  // вывод на монитор порта значение параметра
  Serial.println(" °C");   // вывод на монитор порта символа параметра
  delay(1000);   // приостанов работы программы для фиксации значений
}