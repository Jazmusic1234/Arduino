
//Ultrasonic Sensor Libraries
#include <NewPing.h>

//DS18b20 Libraties
#include <OneWire.h>
#include <DallasTemperature.h>

//LCD Libraries
#include <LiquidCrystal.h>

#define PING_PIN 4 // Arduino pin for both trig and echo
NewPing sonar(PING_PIN, PING_PIN );

#define ONE_WIRE_BUS_PIN A0 // Arduino pin for the DS18b20 data bus
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);
// Device addresses to be found in another sketch and assigned here
DeviceAddress Probe01 = { 0x28, 0xFF, 0xB2, 0x76, 0xB5, 0x16, 0x05, 0xD5 }; 
DeviceAddress Probe02 = { 0x28, 0xFF, 0xD4, 0xEA, 0xC1, 0x16, 0x04, 0x84 }; 
// Device addresses end

//LCD Setup Code
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define PUMP_PIN 5// Arduino pin for pump

//Variable Definitions
#define MAX_DIS 10
#define MIN_DIS 8

boolean isPumping = false;
int sum = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  // For ds18b20 code
  sensors.begin();
  sensors.setResolution(Probe01, 12);
  sensors.setResolution(Probe02, 12);
  // ds18b20 code end
  
  pinMode(5, OUTPUT); // For power switch
}

void loop() {
  // First will get the temperatures and update LCD:
 /*
  sensors.requestTemperatures(); // General initialization command
  delay(100); // Wait before request
  float temp = printTemperature(Probe01); // Get probe 1 temp and then print data to screen
  lcd.setCursor(0,0);
  lcd.print("T1: ");
  lcd.setCursor(5,0);
  lcd.print(temp);
  delay(250); //Wait before overwriting
  float temp2 = printTemperature(Probe02); // Get probe 1 temp and then print data to screen
  lcd.setCursor(0,0);
  lcd.print("T2: ");
  lcd.setCursor(5,0);
  lcd.print(temp2);
*/
  // Now we get the water level. Remember that max distance is further from the sensor but is the lower water level
//  delay(200); // Need at least 29ms total between pings due to sensor processing limitations

  float distance = getDistance();
  lcd.clear();
  Serial.println(distance);
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.setCursor(10,0);
  lcd.print(distance);

  if(distance > MAX_DIS) {
    
    digitalWrite(5, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Status: Filling");
    Serial.println("Status: Filling");
    delay(20000);
    
    digitalWrite(5, LOW);
    delay(7000);
  }

  if (distance < 2) {
    lcd.setCursor(0,1);
    lcd.print("Sensor Blocked!");
    //digitalWrite(5, LOW); 
  }
  else if (distance <= MAX_DIS && distance >= MIN_DIS) {
    lcd.setCursor(0,1);
    lcd.print("Status: Full");
    //digitalWrite(5, LOW); 
  }
  else if (distance > 300) {
    lcd.setCursor(0,1);
    lcd.print("Sensor Error");
    //digitalWrite(5, LOW); 
  }
  

}
/*
//ds18b20 code functions
float printTemperature(DeviceAddress deviceAddress)
{

    float tempC = sensors.getTempC(deviceAddress);

   if (tempC == -127.00) 
   {
   Serial.print("Error getting temperature  ");
   } 
   else
   {
   Serial.print("C: ");
   Serial.print(tempC);
   Serial.print(" F: ");
   Serial.println(DallasTemperature::toFahrenheit(tempC));
   return(DallasTemperature::toFahrenheit(tempC));
   }
}
// ds18b20 end code
  */

float getDistance() {
  sum = 0;
  /* for loop to average distance */
  for(int i = 0; i < 20; i++) {
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    sum = sum + (uS / US_ROUNDTRIP_CM); // Convert ping to distance
    delay(70);
  }
  float distance = sum/20;
  return distance;
}
