# List of parts


Pcs. | Part
-----|---------------------------------------------------------------------------------
 1   | Arduino Nano (Rev3.0)
 1   | Adafruit Ultimate GPS Breakout	
 1   | Adafruit HMC5883L Compass Breakout	
 1   | Electrolytic Capacitor; voltage 6V; capacitance 4.7µF
 1   | Electrolytic Capacitor; voltage 20V; capacitance 100µF
 1   | N20 DC Gear Motor Miniature High Torque Electric Gear Box Motor; voltage 3V
 3   | 100kΩ Resistor; power 1/4W; tolerance ±1%
 1   | L293D
 1   | Bourns ACE 128 absolute rotary encoder
 1   | Voltage Regulator - 5V; 7805 or equivalent


## Notes on parts


### Arduino Mini

https://www.arduino.cc/en/Main/ArduinoBoardMini  
https://www.arduino.cc/en/Main/ArduinoBoardProMini

Same circuit can be made with Arduino Mini or Arduino Pro Mini. Those board are based on the same Atmega micro controller, and have all the same features as Arduino Nano, except for the USB connection - they require external TTL module to program.


### Motor

Motor in driven directly from L293D even though the chip is powered by 5V. Because of L293D internal structure, some voltage loss happens, so the motor is actually driven at close to 4V. There seems to be no need to reduce the voltage further to 3V. 

It seems extremely unlikely that one or two additional volts will cause any harm to the motor. If however, that becomes required, a resistor can be inserted in series with the motor that will reduce voltage drop across the motor. Resistance value should be roughly 1 Ohm, with 2W power rating. But again, it is not necessary, and will actually impair speed control.


### Misc

Capacitance values of the two capacitors are not critical - they can be off even by a factor of 10. Voltages, however, should not be lower then specified. Higher is ok.


Any three resistors above 20k will do, as long as they are identical. Should not go much over 100k, because ADC errors will increase. 




## Possible upgrades


### Switching Voltage Regulator

http://www.ezsbc.com/index.php/psu2-5.html

An integrated switching voltage regulator that is a drop-in replacement for 7805 series.
It claims better efficiency and full compatibility.

Available on eBay as well.

Note: `BATTERY_TRESHOLD` should be updated to reflect wider range of regulator tolerance. This regulator can provide 5V output with 6.4V input, as opposed to 7805 that requires 7.5V input. Note: 6.4 claim not tested and probably depends on the load.


### Accelerometer

Adding accelerometer will allow a simple way to compensate for compass heading drift when the device is tilted.

Adafruit provides integrated compass&accelerator modules. It is possible to replace current magnetometer with this board:

https://www.adafruit.com/products/1120

Note: some additional firmware development is required in order to make use of the accelerometer feature.


### Magnetic Rotary Encoder

http://www.usdigital.com/products/encoders/absolute/rotary/shaft/ma3

This encoder has higher precision then Bourns ACE 128, is cheaper, smaller, and simpler to integrate into Arduino-based device. 

The only downside is possible magnetic interference with the compass module.

If its magnetic field is not rotating, then it is possible to gauge the compass module to compensate for it. Unfortunately there seems to be no information about field's strength and nature in the encoder datasheet.

