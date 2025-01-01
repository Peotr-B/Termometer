/*1янв25
Термометр
Проект 9
Scriptor42
*/
#include <OneWire.h>
#include <DallasTemperature.h>

//https://wikihandbk.com/wiki/Arduino:%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D1%8B/DS18x20_Temperature

// Чтение данных с температурных датчиков типа 1-Wire: DS18S20, DS18B20, DS1822
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// Библиотека DallasTemperature может сделать это все за вас!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(10);  // на 10-ом контакте (если необходимо, подключите резистор на 4,7 кОм)

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  
  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");  //  "Адресов больше нет."
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  
  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");  //  "CRC не корректен!"
      return;
  }
  Serial.println();
 
  // первый ROM-байт, определяет, с каким чипом мы имеем дело:
  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  //  "  Чип – DS18S20" или старый DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");  //  "  Чип – DS18B20"
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");  //  "  Чип – DS1822"
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");  //  "Устройство не принадлежит семейству DS18x20."
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // запускаем конверсию и включаем паразитное питание
  
  delay(1000);     // 750 миллисекунд может хватить, а может и нет;
                   // здесь можно использовать ds.depower(), 
                   // но об этом позаботится сброс 
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // считываем scratchpad-память

  Serial.print("  Data = ");  //  "  Данные = "
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // нам нужно 9 байтов
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // конвертируем данные в температуру; поскольку результат - это
  // 16-битное целое знаковое число, оно должно быть записано в типе 
  // данных "int16_t", который всегда будет 16-битным – даже если
  // данные скомпилированы на 32-битном процессоре.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // разрешение по умолчанию – 9 бит
    if (data[7] == 0x10) {
      // регистр "count remain" дает полное 12-битное разрешение
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // при низком разрешении младшие биты не определяются, поэтому обнуляем их:
    if (cfg == 0x00) raw = raw & ~7;  // 9-битное разрешение (93,75 миллисекунд)
    else if (cfg == 0x20) raw = raw & ~3;  // 10-битное разрешение (187,5 миллисекунд)
    else if (cfg == 0x40) raw = raw & ~1;  // 11-битное разрешение (375 миллисекунд)

    //// по умолчанию стоит 12-битное разрешение; время конверсии – 750 миллисекунд
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  Serial.print("  Temperature = ");  //  "Температура = "
  Serial.print(celsius);
  Serial.print(" Celsius, ");  //  " по Цельсию, "
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");  //  " по Фаренгейту"
}