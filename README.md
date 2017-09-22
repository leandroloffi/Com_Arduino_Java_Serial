# Com_Arduino_Java_Serial

Application IOT - Internet of Things - to collect data from Sensors using Arduino. This data is sent to Raspberry, in which it has a stack, after that in another application Raspberry sends to some cloud the data at a certain time!

Equipment:
-> Sensor Pluviometer Digital
-> Sensor BMP180
-> Sensor DHT 22
-> Arduino
-> Raspberry
-> Cloud Computing (Configured in IOT - Amazon)

---------------------
<<All class in Java>>

Buffer_main.java                = class main
Entrada.java                    = class input data
LocalShell.java                 = class stack
Saida.java                      = class output data
syn_Valores.java                = class list stack

-------------------------------------
<<All class in Node.js (JavaScript)>>
conexao.js                      = class in .js for communication Raspberry with Cloud

-------------------
<<Class in Arduino>>

Adafruit_BMP085.cpp             = class for barometer (pressure, temperature and altitude)
Adafruit_BMP085.h               = class for barometer (pressure, temperature and altitude)
Adafruit_GFX.cpp                = class for Image in LCD
Adafruit_GFX.h                  = class for Image in LCD
Adafruit_PCD8544.cpp            = class for LCD
Adafruit_PCD8544.h              = class for LCD
DHT.cpp                         = class for Temperature and Humidity in .h
DHT.h                           = class for Temperature and Humidity in .c
Thread.cpp                      = class for Thread in .c
Thread.h                        = class for Thread in .h
ThreadController.cpp            = class for Thread Controller (group) in .c
ThreadController.h              = class for Thread Controller (group) in .h
gfxfont.h                       = class font in .h
glcdfont.c                      = class font in .c
Arduino_DTH_BMP180_PLUV_LCD.ino = PROGRAMA PRINCIPAL

###########################################################################

Steps for execute!

sudo apt-get install librxtx-java
sudo dpkg -i teamviewer_11.0.67687_i386.deb ; sudo apt-get install -f   // PRESTAR ATENÇÃO NA VERSÃO

Application JAVA RASPBERRY

javac -cp /usr/share/java/RXTXcomm-2.2pre2.jar:. Buffer_main.java Entrada.java Saida.java syn_Valores.java LocalShell.java

##Execute in Raspberry in Terminal
java -Djava.library.path=/usr/lib/jni -cp /usr/share/java/RXTXcomm-2.2pre2.jar:. Buffer_main

aplication NODE.JS RASPBERRY

sudo apt-get install node
sudo apt-get install npm
npm install aws-iot-device-sdk

##Execute in Raspberry in new Terminal
node conexao.js
