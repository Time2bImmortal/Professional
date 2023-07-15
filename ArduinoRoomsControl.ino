#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

#define ONE_WIRE_BUS 2  // Data wire is connected to digital pin 2
#define DHTPIN2 3      // DHT22 sensor on digital pin 3
#define DHTTYPE2 DHT22   // DHT 22
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds(&oneWire);

DHT dht2(DHTPIN2, DHTTYPE2);

double adultsRoomHumidity, adultsRoomTemperature, larvaeRoomTemperature;

void setup() {
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

  // print sensor readings every 2 minutes
  Serial.print(adultsRoomTemperature);
  Serial.print(",");
  Serial.print(adultsRoomHumidity);
  Serial.print(",");
  Serial.print(larvaeRoomTemperature);
  Serial.println();

  delay(120000); // delay for 2 minutes
}
