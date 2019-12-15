/***************************************************************************************************************
 * dht + foldnedvesseg kijelzon
 *  DHT csatlakoztatva D3-ra
 *  Földnedvesség csatlakoztatva A0-ra
 *
 ********************************************************************************************************************************/

/* OLED */
#include <ACROBOTIC_SSD1306.h> // SCL ==> D1; SDA ==> D2
#include <SPI.h>
#include <Wire.h>

#include "DHT.h"
#define DHTPIN D3  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float hum = 0;
float temp = 0;

/* foldnedvesseg*/
#define soilMoisterPin A0
#define soilMoisterVcc D4
int soilMoister = 0;

void setup() 
{
  Serial.begin(115200);
  delay(10);
  dht.begin();
  oledStart();
  digitalWrite (soilMoisterVcc, LOW);
}

void loop() 
{
  getDhtData();
  getSoilMoisterData();
  displayData();
  delay(2000); // késleltetés
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
  oled.putString(" Teszt ");
}

/***************************************************
 * DHT
 **************************************************/
void getDhtData(void)
{
  float tempIni = temp;
  float humIni = hum;
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  if (isnan(hum) || isnan(temp))  
  {
    Serial.println("Hiba leolvasakor a DHT szenzorrol!");
    temp = tempIni;
    hum = humIni;
    return;
  }
}

/***************************************************
 * Adatgyujtes szenzorokrol
 **************************************************/
void getSoilMoisterData(void)
{
  soilMoister = 0;
  digitalWrite (soilMoisterVcc, HIGH);
  delay (500);
  int N = 3;
  for(int i = 0; i < N; i++) // Nszer olvas és átlag
  {
    soilMoister += analogRead(soilMoisterPin);   
    delay(150);
  }
  digitalWrite (soilMoisterVcc, LOW);
  soilMoister = soilMoister/N; 
  Serial.println(soilMoister);
  soilMoister = map(soilMoister, 380, 0, 0, 100); 
}

/***************************************************
 * kiíratás szerialra és kijelzőre
 **************************************************/
void displayData(void)
{
  Serial.print(" Hom: ");
  Serial.print(temp);
  Serial.print("oC   Parat: ");
  Serial.print(hum);
  Serial.println("%");
  
  oled.setTextXY(3,0);              
  oled.putString("Hom: " + String(temp) + " oC");
  oled.setTextXY(5,0);              
  oled.putString("Parat:  " + String(hum) + " %");
   oled.setTextXY(7,0);              
  oled.putString("Nedv: " + String(soilMoister) + "%");
}

/***************************************************
 * képernyo torles
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

