void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED, OUTPUT);   
  pinMode(RED_LED, OUTPUT);  
}

void loop() {
  int sensorValue = analogRead(A3);
  float voltage = sensorValue * (1.0 / 1023.0);   

  if (voltage > 0.5) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  }
  else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
}
