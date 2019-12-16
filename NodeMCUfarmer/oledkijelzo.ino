/***************************************************
 * Start OLED
 **************************************************/
void oledStart(void)
{
  Wire.begin();  
  oled.init();                     
  clearOledDisplay();
  //oled.setFont(font5x7);       // (default 8x8)
  oled.clearDisplay();             
  
  oled.setTextXY(0,0); oled.putString("Node mcu farmer ");
  oled.setTextXY(1,0); oled.putString(String(SW_VERSION));  
  
  oled.setTextXY(2,0); oled.putString("AUTO_CTRL_TM");
  oled.setTextXY(2,13); oled.putString(String(AUTO_CTRL_TM));
  oled.setTextXY(3,0); oled.putString("DRY_SOIL");
  oled.setTextXY(3,13); oled.putString(String(DRY_SOIL));
  oled.setTextXY(4,0); oled.putString("COLD_TEMP");
  oled.setTextXY(4,13); oled.putString(String(COLD_TEMP));
  oled.setTextXY(5,0); oled.putString("TIME_PUMP_ON");
  oled.setTextXY(5,13); oled.putString(String(TIME_PUMP_ON));
  oled.setTextXY(6,0); oled.putString("TIME_LAMP_ON");
  oled.setTextXY(6,13); oled.putString(String(TIME_LAMP_ON));
  delay(2000);
}

/***************************************************
 * adatok kiírása
 **************************************************/
void displayData(void)
{ 
  String pumpStatusStr;
  String lampStatusStr;
  if (pumpStatus == 1) pumpStatusStr = "on ";
  if (pumpStatus == 0) pumpStatusStr = "off";
  if (lampStatus == 1) lampStatusStr = "on ";
  if (lampStatus == 0) lampStatusStr = "off";
  oled.setTextXY(0,0); oled.putString(" NodeMCU farmer");
  oled.setTextXY(1,0); oled.putString("*-");
  oled.setTextXY(3,0); oled.putString("LevegoH[C]");
  oled.setTextXY(3,11); oled.putString("     ");
  oled.setTextXY(3,11); oled.putString(String(airTemp));

  oled.setTextXY(4,0); oled.putString("LevegoN[%]");
  oled.setTextXY(4,11); oled.putString("     ");
  oled.setTextXY(4,11); oled.putString(String(airHum));

  oled.setTextXY(5,0); oled.putString("FoldH [C]");
  oled.setTextXY(5,11); oled.putString("     ");
  oled.setTextXY(5,11); oled.putString(String(soilTemp));

  oled.setTextXY(6,0); oled.putString("FoldN [%]");
  oled.setTextXY(6,11); oled.putString("     ");
  oled.setTextXY(6,11); oled.putString(String(soilMoister));

  oled.setTextXY(7,0); oled.putString("PMP ");
  oled.setTextXY(7,4); oled.putString(pumpStatusStr);

  oled.setTextXY(7,7); oled.putString("  LMP ");
  oled.setTextXY(7,13); oled.putString(lampStatusStr);
  oled.setTextXY(1,0); oled.putString("-*");
}

/***************************************************
 * törlés 
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
  oled.setTextXY(8,0); oled.putString("                ");              
}
