#include <dht.h>

float t;
float f;
float h;

#define dataPin 4 // Defines pin number to which the sensor is connected

dht DHT; // Creats a DHT object

void setup() {
  Serial.begin(9600);
}

void loop() {
  int readData = DHT.read22(dataPin); // Reads the data from the sensor
  t = DHT.temperature; // Gets the values of the temperature
  f = t*1.8 + 32;
  h = DHT.humidity; // Gets the values of the humidity
  
  // Printing the results on the serial monitor
  Serial.print("Temperature = ");
  Serial.print(f);
  Serial.print(" *F ");
  Serial.print("    Humidity = ");
  Serial.print(h);
  Serial.println(" % ");
  
  delay(2000); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz
}
