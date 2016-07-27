/* *****************************************************************************

                  Arduino EEPROM dumper

(c) 2016, Maurice Hendrix  (mausy5043)
***************************************************************************** */

#include <EEPROM.h>

int addr = 0;
byte value;
char ascii[17] = "=-EEPROM DUMP-= ";

void setup() 
{
  delay(1000);
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port...
  }

  for (addr = 0; addr < EEPROM.length(); ++addr)
  {
    if (!(addr % 16))
    {
      Serial.println(ascii);
      prnHEXval(addr, 4);
      Serial.print("\t");
    }

    value = EEPROM.read(addr);

    if ((value > 0x7F) || (value < 0x20))
    {
      ascii[addr % 16] = '.';
    }
    else
    {
      ascii[addr % 16] = char(value);
    }

    prnHEXval(value, 2);
    Serial.print(" ");
  }
  Serial.println(ascii);
  Serial.println(F("==READY=="));
}

void loop() 
{
  ; // no code here
}

void prnHEXval(int num, int nibbles) // Displays $num$ in HEX format with preceding zeros
{
  char tmp[16];
  char format[128];

  sprintf(format, "%%.%dX", nibbles); 
  sprintf(tmp, format, num);
  Serial.print(tmp); // will print no more than 2 bytes!
}
