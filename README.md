# DS2482-800 for Tasmota
The DS2482-100 works too. It ignores the switching of the channels.
Tasmota currently doesn't support these I2C 1wire bridges so the idea is to create driver support for it.

As far as I understand, the code initially was offered by Dallas Semiconductor, later Maxim, now Analog Semiconductors. 
This code is collected for early testing purposes, only. I tweaked it from various sources because there were still issues
and will try to resynchronize to original sources.

* [Arduino-Temperature-Control-Library](https://github.com/milesburton/Arduino-Temperature-Control-Library)
* [DS2482_OneWire](https://github.com/cybergibbons/DS2482_OneWire)

The work done definitely is not my benefit. Check twice for copyright and license before using! 
I'll add the required info, next.
