Library for QN8035 (radio FM chip)

Tested on esp32C3<br>
Compile platformio (framework = arduino)<br>
chip radio - serial number 8035 0259 4TCE <br>
<br>
not everything is finished<br>
work:<br>
 Initialize chip<br>
 SetFrequency<br>
 GetFrequency<br>
 SetVolume<br>
 SetMute<br>
 SetMono<br>
 GetSnr<br>
 GetRssi<br>
 ScanFrequency (to improve parameter XCCADL now is 4)<br>
 <br>
 to do
 read RDS
 <br>
All registers (and setting fields) are finished <br>
I didn't have a quartz, i made a virtual quartz using PWM (add resistor 10k to PWMPin and XCLK)

 
  
