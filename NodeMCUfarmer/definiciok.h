/* Automatikus paraméterek */
#define DRY_SOIL      25
#define WET_SOIL      45
#define COLD_TEMP     15
#define HOT_TEMP      24
#define TIME_PUMP_ON  15
#define TIME_LAMP_ON  15

/* idozito */
// masodpercekben
#define READ_SOIL_TEMP_TM 1L
#define READ_SOIL_HUM_TM  1L
#define READ_AIR_DATA_TM  2L
#define SEND_UP_DATA_TM   1L
#define AUTO_CTRL_TM      30L     


/* DHT11*/
#define DHTPIN D3  
#define DHTTYPE DHT11 
float airHum = 0;
float airTemp = 0;

/* Földnedvesség */
#define soilMoisterPin A0
#define soilMoisterVcc D8
int soilMoister = 0;

/* onewire szenzor */
#define ONE_WIRE_BUS 2 //pin D4 
float soilTemp;

/* Relék */
#define PUMP_PIN D6     
#define LAMP_PIN D7              
boolean pumpStatus = 0;
boolean lampStatus = 0;
