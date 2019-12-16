/***************************************************************************************************************
 *  NodeMCU ESP-12 Develop Kit V1.0
 *  DHT csatlakoztatva a pin D3-ra (Hőmérséklet és Páratartalom)
 *  Földnedvesség az A0-n
 *  Szenzor adatok OLED kijelzőn
 *  Automatizált rendszer
 *  Kijelzőn láthatók indításkor rövid ideig a főbb paraméterek (pl mikor induljon be az öntözőrendszer, illetve a lámpa)
 *  Szenzor adatok továbbítva a Blynk alkalmazásba
 *  Vezérlés a blynk alkalmazásból
 *  Documentumok hozzá: http://www.blynk.cc
 *  
 *  V1.0 fordított logika reléknél - HIGH az alapállapot - LOW az aktív
 ********************************************************************************************************************************/
#define SW_VERSION "   SW Ver. 1.0"
#include "definiciok.h"     // Project definíciók
#include "blynk.h"

/* ESP & Blynk */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>  
WidgetLED PUMPa(V0);
WidgetLED LAMPa(V1); // Blynk Alkalmazáshoz virtualpin 0-pumpa 1- lámpa

/* időzítők */
#include <SimpleTimer.h>
SimpleTimer timer;

/* OLED */
#include <ACROBOTIC_SSD1306.h> //SCL ==> D1; SDA ==> D2
#include <SPI.h>
#include <Wire.h>

/* DHT11 */
#include "DHT.h"
DHT dht(DHTPIN, DHTTYPE);

/* One wire Hőmérséklet szenzor */
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Nodemcu farmer");
  Serial.println(".... Starting");
  Serial.println(" ");

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(soilMoisterVcc, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  oledStart();
  dht.begin();
  DS18B20.begin();

  PUMPa.off();
  LAMPa.off();
  digitalWrite(PUMP_PIN, HIGH); // fordított logika (alapállás high)
  digitalWrite(LAMP_PIN, HIGH);
  digitalWrite (soilMoisterVcc, LOW); 
  oled.clearDisplay();
  startTimers();
}

void loop()
{
  timer.run(); //SimpleTimer inicializálás
  Blynk.run();
      getDhtData();
      getSoilMoisterData();
      getSoilTempData();
      displayData();
}

/****************************************************************
* Blynkből jövő parancsok olvasása
****************************************************************/
BLYNK_WRITE(3) // Pumpa virtual pin 3
{
  int i=param.asInt();
  if (i==1) 
  {
    pumpStatus = !pumpStatus;
    aplyCmd();
  }
}

BLYNK_WRITE(4) // Lámpa virtual pin 4
{
  int i=param.asInt();
  if (i==1) 
  {
    lampStatus = !lampStatus;
    aplyCmd();
  }
}

 

/***************************************************
* parancs végrehajtás - fordított logika reléknél
****************************************************/
void aplyCmd()
{
  if (pumpStatus == 1) 
  {
    Blynk.notify("Ontozes folyamatban!");
    Blynk.email("borosdavid45@gmail.com", "A Nodemcu ontoz!");
    digitalWrite(PUMP_PIN, LOW); //(fordított logika: aktív ha LOW)
    getDhtData();
    getSoilMoisterData();
    getSoilTempData();
    displayData();
    PUMPa.on();
  }
  else
      {
        digitalWrite(PUMP_PIN, HIGH); //(fordított logika: alapállásban HIGH)
        getDhtData();
        getSoilMoisterData();
        getSoilTempData();
        displayData();
        PUMPa.off();
      }
  
  if (lampStatus == 1) 
  {
    Blynk.notify("Lámpa bekapcsolva!");
    Blynk.email("borosdavid45@gmail.com", "A lámpa ég!");
    digitalWrite(LAMP_PIN, LOW); //(fordított logika: aktív ha LOW)
    getDhtData();
    getSoilMoisterData();
    getSoilTempData();
    displayData();
    LAMPa.on();
  }
  else
      {
        digitalWrite(LAMP_PIN, HIGH);//(fordított logika: alapállásban HIGH)
        getDhtData();
        getSoilMoisterData();
        getSoilTempData();
        displayData();
        LAMPa.off();
      }
}

/***************************************************
* Automatikus vezérlés
****************************************************/
void autoControlPlantation(void)
{ 
  if (soilMoister < DRY_SOIL) 
  {
    turnPumpOn();
  }

  if (airTemp < COLD_TEMP) 
  {
    turnLampOn();
  }
}

/***************************************************
* Pumpa be
****************************************************/
void turnPumpOn()
{
  pumpStatus = 1;
  aplyCmd();
  delay (TIME_PUMP_ON*1000);
  pumpStatus = 0;
  aplyCmd();
}

/***************************************************
* Lámpa be
****************************************************/
void turnLampOn()
{
  lampStatus = 1;
  aplyCmd();
  delay (TIME_LAMP_ON*1000);
  lampStatus = 0;
  aplyCmd();
}

/***************************************************
 *data to Blynk
 **************************************************/
void sendUptime()
{
  Blynk.virtualWrite(10, airTemp); //virtual pin V10
  Blynk.virtualWrite(11, airHum); // virtual pin V11
  Blynk.virtualWrite(12, soilMoister); // virtual pin V12
  Blynk.virtualWrite(13, soilTemp); //virtual pin V13
}
