/***************************************************
 * DHT adat
 **************************************************/
void getDhtData(void)
{
  float tempIni = airTemp;
  float humIni = airHum;
  airTemp = dht.readTemperature();
  airHum = dht.readHumidity();
  if (isnan(airHum) || isnan(airTemp))
  {
    Serial.println("Hiba beolvasáskor a dht szenzorrol!");
    airTemp = tempIni;
    airHum = humIni;
    return;
  }
}

/***************************************************
 * Földnedvesség szenzor adat
 **************************************************/
void getSoilMoisterData(void)
{
  soilMoister = 0;
  digitalWrite (soilMoisterVcc, HIGH);
  delay (500);
  int N = 3;
  for(int i = 0; i < N; i++) 
  {
    soilMoister += analogRead(soilMoisterPin);   
    delay(150);
  }
  digitalWrite (soilMoisterVcc, LOW);
  soilMoister = soilMoister/N; 
  soilMoister = map(soilMoister, 1023, 0, 0, 120);
}

/***************************************************
 * föld hőmérséklet adat
 **************************************************/
void getSoilTempData()
{
  DS18B20.requestTemperatures(); 
  soilTemp = DS18B20.getTempCByIndex(0);

  int newData = ((soilTemp + 0.05) * 10); //soil temp érték fixálás
  soilTemp = (newData / 10.0);
}
