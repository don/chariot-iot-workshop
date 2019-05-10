// Arduino IoT Workshop
// Hardware Test
//
// Run this sketch to test that your hardware is wired correctly. 
// This blinks the LED, prints the temperature, humidity, 
// and button state to the serial console.

// Adafruit DHT Sensor Library https://github.com/adafruit/DHT-sensor-library
// Adafruit Unified Sensor Library https://github.com/adafruit/Adafruit_Sensor

const int buttonPin = 5;

#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // initialize the serial output
  Serial.begin(9600);

  // initialize temperature sensor
  dht.begin();

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLDOWN);

  // turn the LED on
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for the serial connection from the computer
  while (!Serial) {
  }

  Serial.println("IoT Workshop MKR 1010 Hardware Test");
  
}

void loop() {

  // turn LED on
  digitalWrite(LED_BUILTIN, HIGH);
  // wait 1 second
  delay(1000);

  // turn LED off
  digitalWrite(LED_BUILTIN, LOW);
  // wait one second
  delay(1000);
  
  // read temperature and humidity
  float temperature = dht.readTemperature(true);
  float humidity = dht.readHumidity();

  // print sensor data to the serial console
  Serial.print(temperature);
  Serial.print("°F ");
  Serial.print(humidity);
  Serial.println("% RH");
  
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Button is pressed.");
  } else {
    Serial.println("Button is released.");    
  }

  Serial.println();

}
