#define dataPin A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dataPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(dataPin));
  delay(1000);
}
