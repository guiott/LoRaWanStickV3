In the Wireless Stick V3, the circuit to disable voltage divider for battery voltage reading doesn’t work with a fully charged battery, causing a continuous current draining even if GPIO37 (ADC-Ctrl) is set to HIGH. 
Measuring pin 1 (ADC-IN) you always see the voltage present.
Looking to the [schematics](https://resource.heltec.cn/download/Wireless_Stick_V3/HTIT-WS_V3_Schematic_Diagram.pdf)published by the producer, we can see that the gate of the channel P mosfet (G1) is pulled-up to Vdd_3V3, while the source (S1) is attached to the VBATT. Here the related portion:

<img width="577" alt="WrongCircuit" src="https://github.com/user-attachments/assets/71bcd426-635c-4924-b041-34fb5aac2a7b">

It's designed in this way to avoid damages on GPIO 37 with a voltage greater than 3.3V but, when the battery is fully charged, VBATT can be even more than 4V, meaning a negative Vgs that exceed the threshold declared on datasheet. This cause a undesired conduction between S1 and D1.

I’ve modified the circuit adding a channel N mosfet driving channel P, in order to isolate VBATT from GPIO 37.

<img width="865" alt="BattVoltageCorrection" src="https://github.com/user-attachments/assets/0b6bffd2-824d-4a71-90f1-f249910878a1">

Now it works correctly draining current from battery only when needed

![BatteryReadModification](https://github.com/user-attachments/assets/b1d22695-d94c-4a00-a522-a777e0d7270f)

