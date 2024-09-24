/* Heltec Automation LoRaWAN communication example
 *
 * Function:
 * 1. Upload node data to the server using the standard LoRaWAN protocol.
 *  
 * Description:
 * 1. Communicate using LoRaWAN protocol.
 * 
 * HelTec AutoMation, Chengdu, China
 * 成都惠利特自动化科技有限公司
 * www.heltec.org
 *
 * */

#ifndef LORAWAN_H
#define LORAWAN_H
  #include "LoRaWan_APP.h"
#endif

#ifndef DISPLAY_H
#define DISPLAY_H
  #include "Display.h"
#endif

#ifndef CONFIG_H
#define CONFIG_H
  #include "Config.h"
#endif

#ifndef BATT_H
#define BATT_H
  #include "Battery.h"
#endif

#ifndef SENSOR_H
#define SENSOR_H
  #include "Sensor.h"
#endif

RTC_DATA_ATTR bool BattTooLow = false;

/* Prepares the payload of the frame */
static void prepareTxFrame( uint8_t port )
{
  /*appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h".
  *appDataSize max value is LORAWAN_APP_DATA_MAX_SIZE.
  *if enabled AT, don't modify LORAWAN_APP_DATA_MAX_SIZE, it may cause system hanging or failure.
  *if disabled AT, LORAWAN_APP_DATA_MAX_SIZE can be modified, the max value is reference to lorawan region and SF.
  *for example, if use REGION_CN470, 
  *the max value for different DR can be found in MaxPayloadOfDatarateCN470 refer to DataratesCN470 and BandwidthsCN470 in "RegionCN470.h".
  */
    char appDataS[20];
    appDataSize = sprintf(appDataS, "T:%s;H:%s;V:%s", TempMQTT, HumStr, BattVMQTT);
    Serial.println(appDataS);
    //appDataSize = sizeof(appDataS);
    for(int i=0; i < appDataSize; i++)
    {
      appData[i] = (int)appDataS[i];
    }
    /*
    appDataSize = 4;
    appData[0] = 0x00;
    appData[1] = 0x01;
    appData[2] = 0x02;
    appData[3] = 0x03;
    */
}

void setup() 
{
  #ifdef DEBUG_ON
    Serial.begin(115200);
  #endif
  Mcu.begin(HELTEC_BOARD,SLOW_CLK_TPYE);
  BattSetup();
  BattRead();
  BattTooLow = BattProtection();

  if(!BattTooLow)
  {
    displaySetup();
    SetWE_HDIS();
    ReadWE_HIDS();
  }
}

void loop()
{
  switch( deviceState )
  {
    case DEVICE_STATE_INIT:
    {
      #if(LORAWAN_DEVEUI_AUTO)
        LoRaWAN.generateDeveuiByChipID();
      #endif
      LoRaWAN.init(loraWanClass,loraWanRegion);
      //both set join DR and DR when ADR off 
      LoRaWAN.setDefaultDR(3);
      char cstr[20];
      if(!BattTooLow)
      {
        displayInit();
      }
      break;
    }
    case DEVICE_STATE_JOIN:
    {
      Serial.println("================ JOIN ============");
      LoRaWAN.join();
      if(!BattTooLow)
      {
        displayJoining();
      }
      break;
    }
    case DEVICE_STATE_SEND:
    {
      Serial.println("================ SEND ============");
      prepareTxFrame( appPort );
      LoRaWAN.send();
      deviceState = DEVICE_STATE_CYCLE;
      break;
    }
    case DEVICE_STATE_CYCLE:
    {
      Serial.println("================ SEND ============");
      // Schedule next packet transmission
      txDutyCycleTime = appTxDutyCycle + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND );
      LoRaWAN.cycle(txDutyCycleTime);
      deviceState = DEVICE_STATE_SLEEP;
      
      if((LoRaWAN.Display_ACK() != 0) && (!BattTooLow))
      {
        displaySignalData();
      }
      break;
    }
    case DEVICE_STATE_SLEEP:
    {
      LoRaWAN.sleep(loraWanClass);
      break;
    }
    default:
    {
      deviceState = DEVICE_STATE_INIT;
      break;
    }
  }
}