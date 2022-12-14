/*
Who: Kassandra Karger, Laurin Wandel (kaka1024, wala1011 - Laurin.Wandel@web.de)
When: 19.11.2022
What: Readout of BME280 in defined cycle. DeepSleep between Readout. 
Switch between data upload to database and data on display depending on Deepsleep Interupt (Touch or Timer)

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

int long cycle = 10000000;    //Cycle time in microseconds (must be higher than 5 seconds)

const char* ssid     = "Vodafone-A680";   
//const char* ssid     = "FRITZ!Box 7590 UP";  
const char* password = "JtnFDurAbpdetHBa";  
//const char* password = "45525509900873963179";

const char* server = "script.google.com";  // Server URL
const char* key = "AKfycbzZ730s0HOAxjby1vl6fYl4TYu146GwFhbD1Mpn8UTGgGsvalUbRYphoTq_AnyZVECB"; // google script key

#define debug true

#define I2C_SDA 23
#define I2C_SCL 19

#define THRESHOLD 40
#define OLED_RESET -1 

#define SEALEVELPRESSURE_HPA (1013.25)

//Wificlient anlegen
WiFiClientSecure client;
//BME280 anlegen
Adafruit_BME280 bme;
//Display anlegen
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  long int t_start = micros();      //Timer Start

  init_Display_BME();               //Init Display and BME

  touchAttachInterrupt(T0, gotTouched, THRESHOLD);    //define touch interrupt
  
  switch_database_display();        //switch between uploading measurement to database and showing measurement on display 

  Serial.println("Ich schlafe wieder");

  long int t_end = micros();         //timer stop
  long int t_difference = t_end-t_start;  //calculate time for one cycle
  if (t_difference  > cycle){             
    t_difference  = cycle - 10;                    
  }  

  startDeepSleep(t_difference);
}

void loop() { 
  Serial.println("Schleife");
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

void switch_database_display(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_TIMER : uploadValues(); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : printOnDisplay(); break;
  }
}

// Function to start the DeepSleep
void startDeepSleep(long int Zeit){
    esp_sleep_enable_timer_wakeup(cycle - Zeit); //difference between timer and required cyle = sleep time
    esp_sleep_enable_touchpad_wakeup();
    esp_deep_sleep_start();
}

void gotTouched(){
}

void uploadValues() {

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

  String URL="https://script.google.com/macros/s/";
  URL += key;
  URL += "/exec?";
  URL += "1_Spalte=";
  URL += bme.readTemperature();
  URL += "&2_Spalte=";
  URL += (bme.readPressure() / 100.0F);
  URL += "&3_Spalte=";
  URL += bme.readHumidity();

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
}



