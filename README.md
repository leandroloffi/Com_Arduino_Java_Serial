# Com_Arduino_Java_Serial
<br>
<br>Application IOT - Internet of Things - to collect data from Sensors using Arduino. This data is sent to Raspberry, in which it has a stack, after that in another application Raspberry sends to some cloud the data at a certain time!
<br>
<br>Equipment:
<br>-> Sensor Pluviometer Digital
<br>-> Sensor BMP180
<br>-> Sensor DHT 22
<br>-> Arduino
<br>-> Raspberry
<br>-> Cloud Computing (Configured in IOT - Amazon)
<br>
<br>---------------------
<br>##All class in Java##
<br>
<br>Buffer_main.java                = class main
<br>Entrada.java                    = class input data
<br>LocalShell.java                 = class stack
<br>Saida.java                      = class output data
<br>syn_Valores.java                = class list stack
<br>
<br>-------------------------------------
<br>##All class in Node.js (JavaScript)##
<br>conexao.js                      = class in .js for communication Raspberry with Cloud
<br>
<br>-------------------
<br><<Class in Arduino>>
<br>
<br>Adafruit_BMP085.cpp             = class for barometer (pressure, temperature and altitude)
<br>Adafruit_BMP085.h               = class for barometer (pressure, temperature and altitude)
<br>Adafruit_GFX.cpp                = class for Image in LCD
<br>Adafruit_GFX.h                  = class for Image in LCD
<br>Adafruit_PCD8544.cpp            = class for LCD
<br>Adafruit_PCD8544.h              = class for LCD
<br>DHT.cpp                         = class for Temperature and Humidity in .h
<br>DHT.h                           = class for Temperature and Humidity in .c
<br>Thread.cpp                      = class for Thread in .c
<br>Thread.h                        = class for Thread in .h
<br>ThreadController.cpp            = class for Thread Controller (group) in .c
<br>ThreadController.h              = class for Thread Controller (group) in .h
<br>gfxfont.h                       = class font in .h
<br>glcdfont.c                      = class font in .c
<br>Arduino_DTH_BMP180_PLUV_LCD.ino = PROGRAMA PRINCIPAL
<br>
<br>###########################################################################
<br>
<br>Steps for execute!
<br>
<br>sudo apt-get install librxtx-java
<br>sudo dpkg -i teamviewer_11.0.67687_i386.deb ; sudo apt-get install -f   // PRESTAR ATENÇÃO NA VERSÃO
<br>
<br>Application JAVA RASPBERRY
<br>
<br>javac -cp /usr/share/java/RXTXcomm-2.2pre2.jar:. Buffer_main.java Entrada.java Saida.java syn_Valores.java LocalShell.java
<br>
<br>##Execute in Raspberry in Terminal
<br>java -Djava.library.path=/usr/lib/jni -cp /usr/share/java/RXTXcomm-2.2pre2.jar:. Buffer_main
<br>
<br>aplication NODE.JS RASPBERRY
<br>
<br>sudo apt-get install node
<br>sudo apt-get install npm
<br>npm install aws-iot-device-sdk
<br>
<br>##Execute in Raspberry in new Terminal
<br>node conexao.js
<br>
