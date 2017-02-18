int fsrPin = A0;
int fsrReading;

void setup() {
  Serial.begin(9600);
}

void loop() {
  fsrReading = analogRead(fsrPin);
  Serial.print("Force value: ");
  Serial.println(fsrReading);

  delay(10);

}
