#include <dht.h>

float t;
float f;
float h;

int soil_val = 0; // moisture value
int soil_pin = A0; // pin plugged into
int max_val = 660;
int min_val = 200;


#define dataPin 4 // Defines pin number to which the sensor is connected

dht DHT; // Creats a DHT object

String commandCode ="0";

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);// open serial for communication
  delay(100);// serial is tooo old
  Serial.println("Start");//check it works
  delay(100);
}

void loop() {
  if(Serial.available() > 0) {
 
    recvWithStartEndMarkers();
    showNewData();
    if(commandCode == "H") {
      int readData = DHT.read22(dataPin); // Reads the data from the sensor
      h = DHT.humidity; // Gets the values of the humidity
      Serial.print("    Humidity = ");
      Serial.print(h);
      Serial.println(" % ");
      commandCode = "0";
    }
    if(commandCode == "T") {
      int readData = DHT.read22(dataPin); // Reads the data from the sensor
      t = DHT.temperature; // Gets the values of the temperature
      f = t*1.8 + 32;
      Serial.print("Temperature = ");
      Serial.print(f);
      Serial.print(" *F ");
      commandCode = "0";
    }
    if(commandCode == "M") {
      soil_val = analogRead(soil_pin);
      if(soil_val > max_val){
        soil_val = max_val;
      }
      if(soil_val < min_val){
        soil_val = min_val;
      }
      soil_val = map (soil_val, max_val,min_val,0,100);
      Serial.print("moisture: ");
      Serial.print(soil_val);
      Serial.println("%");
      commandCode = "0";
    }

  }
  delay(2000); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz
}


//Serial buffer functions
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
 // if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
                
                commandCode = receivedChars;
                String String(commandCode);
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
  if (newData == true) {
    Serial.println(receivedChars);
    newData = false;
  }
}
