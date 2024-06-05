/* 
 * Project: Particle MonitorOne Display
 * Author: Abhi Bhullar
 * Date: 25/05/2024
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */


#include "Particle.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7789.h"

// Particle prerequisite
SYSTEM_MODE(AUTOMATIC);

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

// display pins
#define TFT_RST 6
#define TFT_DC 5
#define TFT_CS 4

// ST7789 display initialization
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST); 

// variables for data
const char* temp = "--";
const char* hum = "--";
const char* pressure = "--";
const char* gas_pressure = "--";

// variables for datetime
String currWeekDay;
String currDate;
String currTime;
String currTimeFlag;

// Timer that runs updateTime function every 5 seconds
Timer dateTimeTimer(5000, updateTime);

// functions initialization
void dataHandler(const char* eventName, const char *data);
void drawWidget();
void updateWidgets();
void updateTime();

void setup() {
  //Serial.begin(115200);

  // Starting display and rotating in landscape mode
  tft.init(320, 240);                                                  
  tft.fillScreen(ST77XX_BLACK);                                       
  tft.setRotation(1);                                                 

  // Attaching dataHandler to "data" publish event from MonitorOne
  Particle.subscribe("data", &dataHandler); 

  // Starts the timer for updateTime function
  dateTimeTimer.start();                                    

  /*Adjust time zone offset according to your timezone
  i.e. 5.5 for India (+5:30)*/
  Time.zone(5.5);                                           

  // Drawing dummy data to screen until it updates
  drawWidget();
  updateWidgets();
}

void loop() {

}

void dataHandler(const char* eventName, const char* data) // runs on every publish event from MonitorOne
{
  // Parsing data to json format
  JSONValue outerObj = JSONValue::parseCopy(data);
  JSONObjectIterator iter(outerObj);
  
  // Unpacking and updating data
  while(iter.next())
  {
    if(iter.name() == "temp") temp = (const char*)iter.value().toString();
    else
    if(iter.name() == "humidity") hum = (const char*)iter.value().toString();
    else
    if(iter.name() == "pressure") pressure = (const char*)iter.value().toString();
    else
    if(iter.name() == "gas") gas_pressure = (const char*)iter.value().toString();
  }

  // Updating UI
  updateWidgets();
}

void drawWidget(){ // runs once on start
  tft.drawLine(0, 70 ,320, 70, ST77XX_WHITE);
  tft.drawLine(0, 150 ,320, 150, ST77XX_WHITE);
  tft.drawLine(160, 151, 160, 240, ST77XX_WHITE);

  tft.drawCircle(0, 0, 120, ST77XX_WHITE);
  tft.fillCircle(0, 0, 119, ST77XX_BLACK);

  tft.setTextSize(2);
  tft.setCursor(0,0);
  tft.println("TEMP");

  tft.setCursor(130, 0);
  tft.println("HUMIDITY");

  tft.setCursor(30, 160);
  tft.println("PRESSURE");

  tft.setCursor(60, 220);
  tft.println("hPa");

  tft.setCursor(200, 160);
  tft.println("VOC GAS");
  
  tft.setCursor(210 ,220);
  tft.println("KOhms");

  tft.setTextSize(3);

  tft.setCursor(12, 70);
  tft.print((char)247);
  tft.println("C");

  tft.setCursor(220, 30);
  tft.println("%");
}

void updateWidgets(){ // updates on every new data event
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  tft.setTextSize(4);

  // temperature position
  tft.setCursor(6, 30);
  tft.println(temp);

  // humidity position
  tft.setCursor(160, 25);
  tft.println(hum);

  tft.setTextSize(3);

  // pressure position
  tft.setCursor(30, 190);
  tft.println(pressure);

  // voc gas position
  tft.setCursor(190, 190);
  tft.println(gas_pressure);
}


void updateTime() // updates every 5 seconds by dateTimeTimer
{ 
  // Getting Time From Particle Time API
  time_t currDateTime = Time.now();

  // Formatting in desired format
  currDate = Time.format(currDateTime, "%d-%b-%Y") ;
  currWeekDay = Time.format(currDateTime, "%a");
  currTime = Time.format(currDateTime, "%I:%M");
  currTimeFlag = Time.format(currDateTime, "%p");

  // Showing time on display
  tft.setTextSize(5);
  tft.setCursor(131, 100);
  tft.println(currTime);
  tft.setTextSize(2);
  tft.setCursor(290, 100);
  tft.println(currTimeFlag);

  // Showing date on display
  tft.setTextSize(2);
  tft.setCursor(120, 65);
  tft.print(currWeekDay);
  tft.print(", ");
  tft.println(currDate);
}