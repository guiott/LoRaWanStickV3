const int Batt_CTRL = 37;
const int Batt_V = 1;
float VbattMul = 4.65 / 0.95 / 1000; // to convert Values read from ADC (in mV) to Vbatt
float VbattCal = 0.1; // Voltage correction

char BattVStr[6];
char BattVMQTT[6];
float BattV;