
int pin = 6; // Analog pin in that 

#define floatPin 4  // Digital pin that float value is connected to
#define switchPin 2 // Digital pin that switch is connected to
#define relayPin 6 // Digital pin that switch is connected to

int sensorValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);

  pinMode(4, INPUT);
  pinMode(2, INPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = digitalRead(floatPin);
  Serial.println(sensorValue);
  if(sensorValue == 1) {
    digitalWrite(relayPin, HIGH);
  } else if(sensorValue == 0) {
    digitalWrite(relayPin, LOW);
  }    
  delay(2000); 

}
