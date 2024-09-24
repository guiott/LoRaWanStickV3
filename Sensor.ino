#ifndef SENSOR_H
#define SENSOR_H
  #include "Sensor.h"
#endif

//WSEN-HIDS / SHT40 functions--------------------------------------------------
void SetWE_HDIS(void)
{//WSEN-HIDS Sensor
  VextON();
  Serial.println("\nHIDS setup =================================================================");
  Wire1.begin(SDA, SCL);
  WE_HIDS.begin(Wire1, SHT40_I2C_ADDR_44); 
  uint32_t serialNumber;
  error = WE_HIDS.serialNumber(serialNumber);
  if (error) 
  {
    errorToString(error, errorMessage, 256);
    Serial.printf("Error trying to execute HIDS serialNumber(): %s", errorMessage);
  } 
  else 
  {   
    Serial.printf("HIDS Serial Number:  %d\n", serialNumber);
    char serialNumberStr[10];
    dtostrf(serialNumber, TrimCharArray(serialNumber),0,serialNumberStr);
  }
    VextOFF();
    Serial.println("=================================================================== HIDS set");
}

void ReadWE_HIDS()
{//Read WSEN-HIDS temperature + humidity sensor
  uint16_t error;
  char errorMessage[256];
  VextON();
  error = WE_HIDS.measureHighPrecision(temperature, humidity);
  if (error) 
  {
    errorToString(error, errorMessage, 256);
    Serial.printf("Error trying to execute measureHighPrecision():  %s ", errorMessage);
  } 
  else 
  {
    dtostrf(temperature, TrimCharArray(temperature),1,TempStr); 
    dtostrf(humidity, TrimCharArray(humidity),0,HumStr);
    dtostrf(temperature * 10, TrimCharArray(temperature),0,TempMQTT); 
    Serial.printf("Temp: %s°C - Hum: %S\%%\n", TempStr, HumStr);
  }
  VextOFF();
}

int TrimCharArray(int Num)
{
  if(Num < 10)
  {
    return 1;
  }
  else if(Num < 100)
  {
    return 2;
  }
  else if(Num < 1000)
  {
    return 3;
  }
  else
  {
    return 4;
  }
}