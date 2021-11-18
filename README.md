# QT-NodeMCU-Application
Reading ADC of NodeMCU and sending data to QT Application over UDP 

>> The following program should be used to run Lua Script: 
https://github.com/hwiguna/g33k/tree/master/ArduinoProjects/Windows/ESP8266_Related
LuaUploader_1.0.2.4

>> Timer Function: tmr.alarm(id, interval, repeat, function do())
	id: alarmer id  => 0
	interval: alarm time, unit: millisecond => 10  (10ms)
	repeat: 0 - one time alarm, 1 - repeat => 1 
	function do(): callback function for alarm timed out => TimerFunc
  
 Usage: tmr.alarm(0, 10, 1, function() TimerFunc() end)
 
 >> NodeMCU shows 3.3 Voltage in 10 bit resolution (1024). 

>> QCustomPlot library is used for graphical representation.

---
Compilation Note: 
- The following relative path should be added to "ui_mainwindow.h" file.
 #include "../../qcustomplot.h"
