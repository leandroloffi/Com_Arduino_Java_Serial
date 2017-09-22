 #include "DHT.h"
 #include <Wire.h>
 #include "Adafruit_BMP085.h"
 #include "Thread.h"
 #include "ThreadController.h"
 #include "Adafruit_GFX.h"
 #include "Adafruit_PCD8544.h"
 
 Adafruit_BMP085 bmp180;
 
 const int  buttonPin = 4;    // PLUVIOMETRO 

 // THREADS
 ThreadController cpu;
  
 Thread Thread_DHT22;
 Thread Thread_BMP180;
 Thread Thread_escritores;
 Thread Thread_LCD;
 Thread Thread_DIA;

 // VARIAVEIS - LCD
 Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);
 
 // PINOS DE ENTRADA
 #define DHTPIN 3             // SENSOR DE UMIDADE E TEMPERATURA
 #define DHTTYPE DHT22        // DECLARAÇÃO DE MODELO: DHT 22  (AM2302), AM2321

 DHT dht(DHTPIN, DHTTYPE);    // SETANDO A CLASSE DHT
 
 // VARIAVEIS DHT22
 float umid;
 float tempCel;

 // VARIAVEIS PLUVIOMETRO
 int buttonPushCounter = 0;   // contador para o numero de mudanças das básculas
 int buttonState = 0;         // estado atual do switch
 int lastButtonState = 0;     // estado anterior do switch
 long lastDebounceTime = 0;  // a ultima vez em que o pino de saida foi alternado
 long debounceDelay = 50;    // o tempo de debounce
 float Basculou = 0;
 float PluvDia = 0;

 // VARIAVEIS BMP180
 float tempBMP;
 float altit;
 float pressao;

void setup() {
  Serial.begin(9600);
  
  Thread_DHT22.setInterval(5000);
  Thread_DHT22.onRun(leituraDHT);
  
  Thread_BMP180.setInterval(5000);
  Thread_BMP180.onRun(leituraBMP);
  
  Thread_escritores.setInterval(5000);
  Thread_escritores.onRun(escritaSensores);

  Thread_LCD.setInterval(5000);
  Thread_LCD.onRun(LCD);

  Thread_DIA.setInterval(86400000);
  Thread_DIA.onRun(Dia);

  cpu.add(&Thread_DHT22);
  cpu.add(&Thread_BMP180);
  cpu.add(&Thread_LCD);
  cpu.add(&Thread_DIA);
  cpu.add(&Thread_escritores);
  
  display.begin();
  dht.begin();
  bmp180.begin();
}

void loop() {
  leituraPluv();
  cpu.run();
}

void leituraBMP(){
  tempBMP = bmp180.readTemperature();
  altit = bmp180.readAltitude();
  pressao = bmp180.readPressure();
}

//DHT22
void leituraDHT(){
  umid = dht.readHumidity();
  tempCel = dht.readTemperature();
 }

 void leituraPluv(){
                                             // PLUVIOMETRO   
     buttonState = digitalRead(buttonPin);  // ler o estado do switch pelo pino de entrada:
     if (buttonState != lastButtonState) {  // comparar o estado atual do switch ao seu estado anterior:
       if (buttonState == HIGH) {           // se o estado do switch muda, por ruido ou mudança de bascula,
         lastDebounceTime = millis();       // e o estado atual e high, reseta o timer do debounce
       }
       if ((millis() - lastDebounceTime) > debounceDelay) { // ELIMINADOR DE RUIDO!!
            Basculou = Basculou + 0.2794;
            PluvDia = PluvDia + 1;
       }
     // SALVA O STATUS E VAI PARA O PROXIMO LOOP
     lastButtonState = buttonState;
     }
 }

 //ESCRITORA TELA
 void escritaSensores(){
  Serial.print("ARD_01;TD");
  Serial.print(tempCel);     // TEMPERATURA DHT22
  Serial.print(";TB");
  Serial.print(tempBMP); // TEMPERATURA BMP180
  Serial.print(";U");
  Serial.print(umid);       // UMIDADE DHT22
  Serial.print(";P");
  Serial.print(pressao);       // PRESSÃO BMP180
  Serial.print(";A");
  Serial.print(altit);       // ALTITUDE BMP180
  Serial.print(";B");
  Serial.print(Basculou);       // INDICE PLUVIOMETRICO
  Serial.println("=");
  Basculou = 0;
 }

 void LCD(){
  display.setContrast(50); //Ajusta o contraste do display
  display.clearDisplay();   //Apaga o buffer e o display

  display.setTextSize(1); 
  display.setTextColor(BLACK);
  display.print("Temp:");
  display.setTextSize(2);
  String auxTemp = String(tempBMP,1); // TEMPERATURA BMP085
  display.println(auxTemp);
  display.setTextSize(1);  
  display.print("Umid:");
  display.setTextSize(2);
  String auxUmid = String(umid,1); // UMIDADE DHT22
 display.println(auxUmid);
  display.setTextSize(1);  
  display.print("Pluv:");
  display.setTextSize(2);
  String auxPluv = String(PluvDia,1);
  display.println(auxPluv);
  display.display();
}

void Dia(){ // ZERANDO O VALOR DO Pluviometro do Dia
  PluvDia = 0;
}

