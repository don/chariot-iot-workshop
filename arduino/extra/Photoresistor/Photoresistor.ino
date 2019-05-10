// Wire one leg of photoresistor to positive rail
// Connect the other leg to ground with 10kΩ resistor
// The leg with the resistor should be wired to pin A0

#define PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(PIN, INPUT);
  analogReadResolution(12);
}

void loop() {
  Serial.println(analogRead(PIN));
  delay(100);
}
