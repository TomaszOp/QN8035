Library for QN8035 (radio FM chip)

Tested on esp32C3<br>
Compile platformio (framework = arduino)<br>
<br>
not everything is finished<br>
work:<br>
 initialize chip<br>
 SetFrequency<br>
 GetFrequency<br>
 SetVolume<br>
 <br>
 <br>
All registers (and setting fields) are finished <br>
I didn't have a quartz, i made a virtual quartz using PWM (add resistor 10k to PWMPin and XCLK)

 
  
