#ifndef LoRaWan_APP_H
#define LoRaWan_APP_H
  #include "LoRaWan_APP.h"
  //For a connection via I2C using the Arduino Wire include:
#endif

#ifndef CONFIG_H
#define CONFIG_H
  #include "Config.h"
#endif

#include <Wire.h>               

#ifdef DISP_ON
  #include "HT_SSD1306Wire.h"
  RTC_DATA_ATTR SSD1306Wire  display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_64_32, RST_OLED); // addr , freq , i2c group , resolution , rst
#endif

enum Align
{
  LEFT,
  CENTER,
  RIGHT
};

char Temp1[20];
char Temp2[20];
char Temp3[20];

int counter;

void dispInit();
void drawTextFlow();
void drawProgressBar();
void VextON(void);
void VextOFF(void);
char* Region(void);



