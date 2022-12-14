/*
Who: Kassandra Karger, Laurin Wandel (kaka1024, wala1011 - Laurin.Wandel@web.de)
When: 19.11.2022
What: Readout of BME280 in defined cycle. 
Used fpr Power consumption test.

Lolin32 Lite with BME280 and SSD1306 

Development: Arduino IDE 2.0.1
Port: GPIO 5 --> DIN
GND --> GND
3,3V --> +5V
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "WiFiClientSecure.h" 
#include <WiFi.h>
#include <HTTPClient.h> 

//int long cycle = 10000000;    //Cycle time in microseconds (must be higher than 5 seconds)

//const char* ssid     = "Vodafone-A680";   
const char* ssid     = "FRITZ!Box 7590 UP";  
//const char* password = "JtnFDurAbpdetHBa";  
const char* password = "45525509900873963179";

const char* server = "script.google.com";  // Server URL
const char* key = "AKfycbzX9wwUrPA0tzw8yjO00H1P9aHWGG4u-wQfClPQYbAZhvVfkP6rqUwULGwXuvCI6Cua"; // google script key

int DisplayPin = 4;
long int t;
long int t_end;


#define debug true

#define I2C_SDA 23
#define I2C_SCL 19

#define OLED_RESET -1 

#define SEALEVELPRESSURE_HPA (1013.25)

//Wificlient anlegen
WiFiClientSecure client;
//BME280 anlegen
Adafruit_BME280 bme;
//Display anlegen
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

void setup() {
  pinMode(DisplayPin, INPUT);

  Serial.begin(9600);

  init_Display_BME();               //Init Display and BME
  
  //switch_database_display();        //switch between uploading measurement to database and showing measurement on display 

  Serial.println("Warte auf Verbindung");
  WiFi.begin(ssid, password);

  int abbruch=0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    abbruch++;
    if (abbruch==20)ESP.restart();
  }
  Serial.println("");
  Serial.print("IP Addresse: ");
  Serial.println(WiFi.localIP());
}

void loop() { 

  uploadValues();

}

void init_Display_BME(){
  Wire.begin(I2C_SDA, I2C_SCL);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(10);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.2);
  display.setTextColor(WHITE);
  
  bool status;
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}


void uploadValues() {
  digitalWrite(DisplayPin, LOW);

  t = millis();
  t_end = t + 1000;
  String URL="https://script.google.com/macros/s/";
  URL += key;
  URL += "/exec?";
  URL += "1_Spalte=";
  URL += bme.readTemperature();
  URL += "&2_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&3_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
      digitalWrite(DisplayPin, LOW);
    
    }
    t = millis();
  }
  Serial.println("1");
  Serial.println(URL);

  t_end = t_end + 1000;
  URL += "&4_Spalte=";
  URL += bme.readTemperature();
  URL += "&5_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&6_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
      digitalWrite(DisplayPin, LOW);
    }

    t = millis();
  }
  Serial.println("2");
  Serial.println(URL);

  t_end = t_end + 1000;
  URL += "&7_Spalte=";
  URL += bme.readTemperature();
  URL += "&8_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&9_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
      digitalWrite(DisplayPin, LOW);
    
    }
    t = millis();
  }
  Serial.println("3");
  Serial.println(URL);

  t_end = t_end + 1000;
  URL += "&10_Spalte=";
  URL += bme.readTemperature();
  URL += "&11_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&12_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
      digitalWrite(DisplayPin, LOW);
    
    }
    t = millis();
  }
  Serial.println("4");
  Serial.println(URL);

  t_end = t_end + 1000;
  URL += "&13_Spalte=";
  URL += bme.readTemperature();
  URL += "&14_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&15_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
      digitalWrite(DisplayPin, LOW);
    
    }
    t = millis();
  }
  Serial.println("5");
  Serial.println(URL);
  
  t_end = t_end + 1000;
  URL += "&16_Spalte=";
  URL += bme.readTemperature();
  URL += "&17_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&18_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
      digitalWrite(DisplayPin, LOW);
    
    }
    t = millis();
  }
  Serial.println("6");
  Serial.println(URL);

  t_end = t_end + 1000;
  URL += "&19_Spalte=";
  URL += bme.readTemperature();
  URL += "&20_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&21_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
      digitalWrite(DisplayPin, LOW);
    
    }
    t = millis();
  }
  Serial.println("7");
  Serial.println(URL);

  t_end = t_end + 1000;
  URL += "&22_Spalte=";
  URL += bme.readTemperature();
  URL += "&23_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&24_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
      digitalWrite(DisplayPin, LOW);
    
    }

    t = millis();
  }
  Serial.println("8");
  Serial.println(URL);

  t_end = t_end + 1000;
  URL += "&25_Spalte=";
  URL += bme.readTemperature();
  URL += "&26_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&27_Spalte=";
  URL += bme.readHumidity();
  t = millis();
  while (t <= t_end) {
    if  (digitalRead(DisplayPin) == HIGH) {
      printOnDisplay();
    
    }
    t = millis();
  }
  Serial.println("9");
  Serial.println(URL);

  URL += "&28_Spalte=";
  URL += bme.readTemperature();
  URL += "&29_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&30_Spalte=";
  URL += bme.readHumidity();
  
  Serial.println("10");
  Serial.println(URL);


  if ((WiFi.status() == WL_CONNECTED)) { //Noch verbunden?
 
    HTTPClient http;
 
    http.begin(URL); //Specify the URL                                //verbindung zum Skript aufbauen
    int httpCode = http.GET();                                        //sende den Link an das Skript 
    http.end(); //Free the resources
  if(debug)Serial.println("Gesendet."); 
  }
  else
  {
  Serial.println("keine Verbindung mehr. Esp startet neu");
  ESP.restart(); 
  }  

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

void printOnDisplay() { 
  
  display.setCursor(0,0);
  display.clearDisplay();
  
  display.print("Temperature: "); display.print(bme.readTemperature()); display.println(" *C");

  display.print("Pressure: "); display.print(bme.readPressure() / 100.0F); display.println(" hPa");

  display.print("Humidity: "); display.print(bme.readHumidity()); display.println(" %");

  Serial.println();
  display.display();
  delay(4000);
  display.clearDisplay();
  display.display();
 }



