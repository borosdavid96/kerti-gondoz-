/***************************************************************************************************************
 * IoT DHT Hőmérséklet/páratartalom szenzor NodeMCU ESP-12 
 *  DHT csatlakoztatva a NodeMCU D3-as pinjéhez
 *  DHT adat az oled kejlzőre írva
 *
 ********************************************************************************************************************************/

/* OLED */
#include <ACROBOTIC_SSD1306.h> //  SCL ==> D1; SDA ==> D2
#include <SPI.h>
#include <Wire.h>

/* DHT11*/
#include "DHT.h"
#define DHTPIN D3  
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
float para = 0;
float temp = 0;

void setup() 
{
  Serial.begin(115200);
  delay(10);
  dht.begin();
  oledStart();
}

void loop() 
{
  getDhtData();
  displayData();
  delay(2000); // késleltetés a DHT11 adatokhoz
}

/***************************************************
 * Start OLED
 **************************************************/
void oledStart(void)
{
  Wire.begin();  
  oled.init();                      
  clearOledDisplay();
  oled.clearDisplay();             
  oled.setTextXY(0,0);              
  oled.putString(" NodeMCU farmer");
}

/***************************************************
 *  DHT adat
 **************************************************/
void getDhtData(void)
{
  float tempIni = temp;
  float paraIni = para;
  temp = dht.readTemperature();
  para = dht.readHumidity();
  if (isnan(para) || isnan(temp))   // beolvasási hibánál nehogy túl hamar lépjen ki
  {
    Serial.println("Hiba beolvasásnál a DHT szenzorról!");
    temp = tempIni;
    para = paraIni;
    return;
  }
}

/**************************************************************
 * Adatok kiírása szerial kimenetre illetve az oled kijelzőre
 **************************************************************/
void displayData(void)
{
  Serial.print(" Homerseklet: ");
  Serial.print(temp);
  Serial.print("oC   Páratartalom: ");
  Serial.print(para);
  Serial.println("%");
  
  oled.setTextXY(3,0);              // Kurzor pozíció a 3. sorra
  oled.putString("Hőm: " + String(temp) + " oC");
  oled.setTextXY(5,0);              // Kurzor pozíció az 5. sorra
  oled.putString("Páratartalom:  " + String(para) + " %");
}

/***************************************************
 * Oled kijelző törlés
 **************************************************/
void clearOledDisplay()
{
  oled.setFont(font8x8);
  oled.setTextXY(0,0); oled.putString("                ");
  oled.setTextXY(1,0); oled.putString("                ");
  oled.setTextXY(2,0); oled.putString("                ");
  oled.setTextXY(3,0); oled.putString("                ");
  oled.setTextXY(4,0); oled.putString("                ");
  oled.setTextXY(5,0); oled.putString("                ");
  oled.setTextXY(6,0); oled.putString("                ");
  oled.setTextXY(7,0); oled.putString("                ");
  oled.setTextXY(0,0); oled.putString("                ");              
}
