# Arduino-Simon

Arduino SW is the arduino sketch for the simon game. The sketch is written for the custom board with arduino/genuino micro bootloader. The required software I2C and display libraries are included for the following reason. As of the first board revision there was no plan to have a display so I2C lines were used for buttons. To add the display and use 4 analog pins for it required the software I2C library. The display library of course needed some modification to work with this as well.

Eagle HW has the Eagle board and schematic files. Also included are PDF versions of both files viewable from a browser. The display used is a .96" ssd1306 I2C OLED display found places like adafruit, amazon, and ebay. The arcade style light up buttons were bought from addicore.com. Will add schematics for the amplifier "soon". It is just an LM386 based amplifier with a logarithmic pot and a voltage divider on the input signal since they don't really want 5V input signal.
