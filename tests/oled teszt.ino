
/***********************************************************************
*  NodeMCU és Oled kijelzo teszt
************************************************************************/

#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

void setup()
{
  Wire.begin();  
  oled.init();                      // OLED kijelző inicializálása
  oled.clearDisplay();              // Képernyő törlés
  oled.setTextXY(0,0);              //Kurzor pozíció a 0. sor elejére
  oled.putString("Oled teszt");
  oled.setTextXY(4,0);              //Kurzor pozíció a 4. sor elejére
  oled.putString("  HELLO, WORLD");
}

void loop()
{
}
