
/***************************************************
* időzítők
****************************************************/
void startTimers(void)
{
  timer.setInterval(READ_SOIL_TEMP_TM*1000, getSoilTempData);
  timer.setInterval(READ_AIR_DATA_TM*1000, getDhtData);
  timer.setInterval(READ_SOIL_HUM_TM*1000, getSoilMoisterData);
  timer.setInterval(SEND_UP_DATA_TM*1000, sendUptime);
  timer.setInterval(AUTO_CTRL_TM*1000, autoControlPlantation);
}
