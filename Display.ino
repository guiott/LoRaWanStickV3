#ifndef DISPLAY_H
#define DISPLAY_H
  #include "Display.h"
#endif

void displayJoining()
{
  #ifdef DISP_ON
    VextON();
    strcpy(Temp1, "LoRaWAN");
    strcpy(Temp2, "joining");
    if(overTheAirActivation)
    {
      strcpy(Temp3, "OTAA");
      if(LoRaWAN.LoRaWan_ADR())
      {
        strcat(Temp3, " ADR");
      }
    }
    else
    {
      strcpy(Temp3, "ABP");
    }
    dispScreen(CENTER, Temp1, Temp2, Temp3);
  #endif
}

void displayJoined()
{
  #ifdef DISP_ON
    VextON();
    strcpy(Temp1, "");
    strcpy(Temp2, "JOINED");
    strcpy(Temp3, "");
    dispScreen(CENTER, Temp1, Temp2, Temp3);
  #endif
}

void displaySignalData()
{
  #ifdef DISP_ON
    VextON();
    if(BattV < BattLow)
      {
        display.clear();
        display.setFont(ArialMT_Plain_16);
        display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.drawString(display.getWidth()/2, 0,"BATT");
        display.drawString(display.getWidth()/2, 16,"LOW");
        display.display();
      }
      else
      {  
        strcpy(Temp1, LoRaWAN.dispSignal());
        strcpy(Temp2, LoRaWAN.dispDataRate());
        strcpy(Temp3, BattVStr);
        dispScreen(CENTER, Temp1, Temp2, Temp3);
      }
  #endif
}

void displayInit()
{
    #ifdef DISP_ON
      VextON();
      sprintf(Temp2, "Class: %X",loraWanClass+10 );
      strcpy(Temp3, "DR: 3");
      dispScreen(CENTER, Region(), Temp2, Temp3);
      delay(3000);
      VextOFF();
    #endif
}

void displaySetup()
{
  #ifdef DISP_ON
    Serial.println("================Disp Init============");
    VextON();
    delay(100);
    // Initialising the UI will init the display too.
    display.init();
    VextOFF();
  #else
    VextOFF();
  #endif
}

void dispScreen(int Align, char *Line1, char *Line2, char *Line3)
{
  #ifdef DISP_ON
    int x;
    display.clear();
    display.setFont(ArialMT_Plain_10);
    switch(Align)
    {
      case LEFT:
      {
          display.setTextAlignment(TEXT_ALIGN_LEFT);
          x = 0;
          break;
      }
      case CENTER:
      {
          display.setTextAlignment(TEXT_ALIGN_CENTER);
          x = display.getWidth()/2;
          break;
      }
      case RIGHT:
      {
          display.setTextAlignment(TEXT_ALIGN_RIGHT);
          x = display.getWidth();
          break;
      }
    }

    display.drawString(x,  0, Line1);
    display.drawString(x, 10, Line2);
    display.drawString(x, 20, Line3);
    display.display();
  #endif
}

void dispTest()
{
  #ifdef DISP_ON
    //Serial.println("Test");
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0,  0,"ABCDEFGHIJ");
    display.drawString(0, 10,"ABCDEFGHIJ");
    display.drawString(0, 20,"ABCDEFGHIJ");
    display.display();
  #endif
}

void drawTextFlow() 
{
  #ifdef DISP_ON
    //Serial.println("Flow");
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 64,
    "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
    display.display();
  #endif
}

void drawProgressBar() 
{// draw the progress bar
  #ifdef DISP_ON
    //Serial.println("Bar");
    int progress = (counter / 5) % 100;
    display.clear();
    display.drawProgressBar(0, 10, 63, 10, progress);

    // draw the percentage as String
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(32, 20, String(progress) + "%");
    display.display();
  #endif
}

void VextON(void)
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) //Vext default OFF
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, HIGH);
}

char* Region(void)
{
    static char regionString[30];
    switch(loraWanRegion)
    {
      case LORAMAC_REGION_AS923_AS1:
        return strcpy(regionString, "AS923(AS1:922.0-923.4MHz)");        
        break;
      case LORAMAC_REGION_AS923_AS2:
        return strcpy(regionString, "AS923(AS2:923.2-924.6MHz)");
        break;
      case LORAMAC_REGION_AU915:
        return strcpy(regionString, "AU915");        
        break;
      case LORAMAC_REGION_CN470:
        return strcpy(regionString, "CN470");        
        break;
      case LORAMAC_REGION_CN779:
        return strcpy(regionString, "CN779");        
        break;
      case LORAMAC_REGION_EU433:
        return strcpy(regionString, "EU433");        
        break;
      case LORAMAC_REGION_EU868:
        return strcpy(regionString, "EU868");        
        break;
      case LORAMAC_REGION_KR920:
        return strcpy(regionString, "KR920");        
        break;
      case LORAMAC_REGION_IN865:
        return strcpy(regionString, "IN865");        
        break;
      case LORAMAC_REGION_US915:
        return strcpy(regionString, "US915");        
        break;
      case LORAMAC_REGION_US915_HYBRID:
        return strcpy(regionString, "US915_HYBRID");        
        break;
      default:
        return strcpy(regionString, "ERROR");        
        break;
    }
}