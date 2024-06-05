/* 
 * Project: MonitorOneEnvironment
 * Author: Abhi Bhullar
 * Date: 25/05/2024
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

#include "Particle.h"
#include "Adafruit_BME680.h"

// Particle prerequisites
SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// BME680 initialization
Adafruit_BME680 bme;
 
// delay for checking sensor data
std::chrono::milliseconds sensorCheckPeriod = 10s;
unsigned long lastSensorCheckMs;

// sensor variables
double temp;
double hum;
double pressure;
double gas_pressure;

// functions initialization
void getSensorReadings();
void publishData();

void setup() {
  //Begin Serial
  //Serial.begin(9600);
  //while(!Serial);
  //Serial.println(F("BME680 start"));

  //Begin BME680 Sensor
  if(!bme.begin()){
    Serial.println("could not find sensor");
  }

  // Creating varibles for particle cloud
  Particle.variable("Tempurature", temp);
  Particle.variable("Humidity", hum);
  Particle.variable("Pressure", pressure);
  Particle.variable("Gas Pressure", gas_pressure);

  // Adjusting sensor sensitivity
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);

  // Publishing data once on startup
  getSensorReadings();
  publishData();
}

void loop()
{
  if(millis() - lastSensorCheckMs >= sensorCheckPeriod.count()) // runs after delay
  {
    // Getting and publishing data to cloud
    getSensorReadings();
    publishData();

    // Updating timer
    lastSensorCheckMs = millis();
  }
}

void getSensorReadings() // reads data from sensor
{
  // Performing reading from sensor
    if(!bme.performReading()){
      Serial.println("Failed to read data!");
      return;
    }

    // Updating data values
    temp = bme.temperature;
    hum = bme.humidity;
    gas_pressure = bme.gas_resistance;
    pressure = bme.pressure;
}

void publishData() // publish data to cloud
{
  // JSON Buffer
  char buf[256];
  memset(buf, 0, sizeof(buf));
  JSONBufferWriter writer(buf, sizeof(buf) - 1);

  // Parsing data to JSON format
  writer.beginObject();
  writer.name("temp").value(String(temp, 1));
  writer.name("humidity").value(String(hum, 0));
  writer.name("pressure").value(String((pressure/100.0), 2));
  writer.name("gas").value(String((gas_pressure/1000.0), 2));
  writer.endObject();

  // Publishing "data" event
  Particle.publish("data", writer.buffer(), PRIVATE);
}