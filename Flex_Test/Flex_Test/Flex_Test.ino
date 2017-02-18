int fsrPin = A0;
int fsrReading;

void setup() {
  Serial.begin(9600);
}

void loop() {
  fsrReading = analogRead(fsrPin);
  Serial.print("Force value: ");
  Serial.println(fsrReading);
  if(fsrReading > 250 && fsrReading < 500){
    tone(3, 253, 100); 
  }
  else if (fsrReading > 500) {
    tone(3, 659, 100);  
  }

}
