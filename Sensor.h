//WSEN-HIDS Sensor = SHT40------------
#include <SensirionI2cSht4x.h>

SensirionI2cSht4x WE_HIDS;
float temperature;
float humidity;
char TempStr[6];
char TempMQTT[6];
char HumStr[5];
static int16_t error;
static char errorMessage[256];


