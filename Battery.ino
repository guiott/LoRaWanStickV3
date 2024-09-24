#ifndef BATT_H
#define BATT_H
  #include "Battery.h"
#endif

void BattSetup()
{
  //According to the schematics the ADC pin 1 reads from battery through a 390k-100k divider
  //The Battery voltage is applied to a mosfet switch controlled by GPIO 37
  pinMode(Batt_V, INPUT);
  analogReadResolution(13); // On S3 this means values from 0 to 8191
  analogSetPinAttenuation(Batt_V, ADC_0db); // On S3 means  range from 0 to 950mV = 0 to 4.65V
  pinMode(Batt_CTRL, OUTPUT);
}

void BattRead()
{
  BattCTRL(true);
  BattV = analogReadMilliVolts(Batt_V) * VbattMul + VbattCal;
  BattCTRL(false);
  sprintf(BattVStr, "%.2fV", BattV );
  Serial.printf("Vbatt: %s\n", BattVStr);
  sprintf(BattVMQTT, "%.0f", BattV * 100 );
}

void BattCTRL(bool on)
{
  if(on)
  {
    digitalWrite(Batt_CTRL, HIGH);
    //Serial.println("Battery reading enabled");
  }
  else
  {
    digitalWrite(Batt_CTRL, LOW);
    //Serial.println("Battery reading disabled");
  }
}

bool BattProtection()
{// BattStop1 > BattStop2 > BattStop3
  if(BattV < BattStop1)
  {// battery too low to make anything
    Serial.println("==== BATTERY TOO LOW. CONSUMPTION REDUCED");

    if(BattV < BattStop3)
    {
      if (appTxDutyCycle < 86400000)
      {
        appTxDutyCycle = 86400000; //very very low, TX once a day
      }
    }
    else if(BattV < BattStop2)
    {
      if (appTxDutyCycle < 3600000)
      {
        appTxDutyCycle = 3600000; //very low, TX once an hour
      }
    }
    else if(appTxDutyCycle < 1800000)
    {
      appTxDutyCycle = 1800000; // low, TX once every half an hour
    } 

    return true; //Disable display and sensor reading
  }
  else
  {
    return false;
  }
}