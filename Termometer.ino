/*1янв25
Термометр
Проект 9
Scriptor42
*/
//https://robotclass.ru/tutorials/arduino-ds18b20-roc/

#include <OneWire.h>

OneWire ds(10);

void setup() {
    Serial.begin(9600);
}

void loop() {
    byte i;
    byte data[12];
    byte addr[8];
    float celsius;
 
    // поиск адреса датчика
    if ( !ds.search(addr)) {
        ds.reset_search();
        delay(250);
        return;
    }
 
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1); // команда на измерение температуры

    delay(1000);

    ds.reset();
    ds.select(addr); 
    ds.write(0xBE); // команда на начало чтения измеренной температуры

    // считываем показания температуры из внутренней памяти датчика
    for ( i = 0; i < 9; i++) {
        data[i] = ds.read();
    }

    int16_t raw = (data[1] << 8) | data[0];
    // датчик может быть настроен на разную точность, выясняем её 
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7; // точность 9-разрядов, 93,75 мс
    else if (cfg == 0x20) raw = raw & ~3; // точность 10-разрядов, 187,5 мс
    else if (cfg == 0x40) raw = raw & ~1; // точность 11-разрядов, 375 мс

    // преобразование показаний датчика в градусы Цельсия 
    celsius = (float)raw / 16.0;
    Serial.print("t=");
    Serial.println(celsius);
}