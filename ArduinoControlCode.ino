#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

#define ONE_WIRE_BUS 2  // Data wire is connected to digital pin 2
#define DHTPIN2 3      // DHT22 sensor on digital pin 3
#define DHTTYPE2 DHT22   // DHT 22
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds(&oneWire);

DHT dht2(DHTPIN2, DHTTYPE2);

int adultsRoomTempAlertPin = 7;
int larvaeRoomTempAlertPin = 8;

double adultsRoomHumidity, adultsRoomTemperature, larvaeRoomTemperature;
int adultsRoomTempMin = 20;
int adultsRoomTempMax = 25;
int adultsRoomHumidityMin = 30;
int adultsRoomHumidityMax = 60;
int larvaeRoomTempMin = 28;
int larvaeRoomTempMax = 31;

void setup() {
  pinMode(adultsRoomTempAlertPin, OUTPUT);
  pinMode(larvaeRoomTempAlertPin, OUTPUT);
  digitalWrite(adultsRoomTempAlertPin, LOW);
  digitalWrite(larvaeRoomTempAlertPin, LOW);
  delay(500);
  Serial.begin(9600);
  delay(500);
  dht2.begin();
  ds.begin();
}

void loop() {
  ds.requestTemperatures();
  larvaeRoomTemperature = ds.getTempCByIndex(0);
  adultsRoomHumidity = dht2.readHumidity();
  adultsRoomTemperature = dht2.readTemperature();

  // check adults room temperature range
  if (adultsRoomTemperature < adultsRoomTempMin || adultsRoomTemperature > adultsRoomTempMax) {
    digitalWrite(adultsRoomTempAlertPin, HIGH);
  } else {
    digitalWrite(adultsRoomTempAlertPin, LOW);
  }

  // check adults room humidity range
  if (adultsRoomHumidity < adultsRoomHumidityMin || adultsRoomHumidity > adultsRoomHumidityMax) {
    digitalWrite(adultsRoomTempAlertPin, HIGH);
  } else {
    digitalWrite(adultsRoomTempAlertPin, LOW);
  }

  // check larvae room temperature range
  if (larvaeRoomTemperature < larvaeRoomTempMin || larvaeRoomTemperature > larvaeRoomTempMax) {
    digitalWrite(larvaeRoomTempAlertPin, HIGH);
  } else {
    digitalWrite(larvaeRoomTempAlertPin, LOW);
  }

  // print sensor readings every 1.25 minutes
 
    Serial.print(adultsRoomTemperature);
    Serial.print(",");
    Serial.print(adultsRoomHumidity);
    Serial.print(",");
    Serial.print(larvaeRoomTemperature);
    Serial.println();
    
  

  delay(1000);
}
