/*1янв25
Термометр C / F
Проект 9
Scriptor42
*/
/*Сборный скетч */

/*Термометр на Arduino и термодатчике DS18B20 */

/*Подключение библиотек*/
#include "OneWire.h"
#include "DallasTemperature.h"
 
OneWire oneWire(10);                             // выбор порта 10 для подключения датчика
DallasTemperature ds(&oneWire);       //обмен данными  по протоколу 1-Wire 

const int alarmPin = 3;  // назначение порта 3 для вывода аварийного сигнала

void setup() {
  Serial.begin(9600);   // инициализация монитора порта
  ds.begin();                 // инициализация датчика ds18b20
  pinMode(alarmPin, OUTPUT);  // инициализация аварийного порта на выход
}

void loop() {
ds.requestTemperatures();    // запрос температуры

/*Установка высокого уровня напряжения на аварийном порту при T > 25 °C*/
float T_C = ds.getTempCByIndex(0);   //присвоение переменной значения температуры
if (T_C > 25)
    digitalWrite(alarmPin, LOW);
    else
      digitalWrite(alarmPin, HIGH);

  Serial.print("Temperature: ");  // вывод на монитор порта имя параметра
  Serial.print(ds.getTempCByIndex(0));  // вывод на монитор порта значение параметра
  Serial.println(" °C");   // вывод на монитор порта символа параметра
  delay(1000);   // приостанов работы программы для фиксации значений
}
