
int soil_val = 0; // moisture value
int soil_pin = A0; // pin plugged into
int max_val = 660;
int min_val = 200;

void setup() {
  Serial.begin(9600);// open serial for communication
  delay(100);// serial is tooo old
  Serial.println("Start");//check it works
  delay(100);
}

void loop() { 
  soil_val = analogRead(soil_pin);
  if(soil_val>max_val){
    soil_val = max_val;
  }
  if(soil_val<min_val){
    soil_val = min_val;
  }
  soil_val = map (soil_val, max_val,min_val,0,100);
  Serial.print("moisture: ");
  Serial.print(soil_val);
  Serial.println("%");
  delay(1000);
}
