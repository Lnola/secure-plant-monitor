// *** RGB ***
// int red = 2; // select the pin for the red LED
// int green = 3 ;// select the pin for the green LED
// int blue = 4; // select the pin for the blue LED

// void setup () {
//   pinMode (red, OUTPUT);
//   pinMode (blue, OUTPUT);
//   pinMode (green, OUTPUT);
// }

// void loop ()
// {
//   analogWrite(blue, 0);
//   analogWrite(red, 255);
//   delay(1000);
//   analogWrite(red, 0);
//   analogWrite(green, 255);
//   delay(1000);
//   analogWrite(green, 0);
//   analogWrite(blue, 255);
//   delay(1000);
// }
// *** RGB ***

// *** BUZZER ***
// const int buzzerPin = D7;

// void setup() {
//   pinMode(buzzerPin, OUTPUT);
// }

// void loop() {
//   tone(buzzerPin, 1000); // Produces a 1 kHz tone, comfortable for most people.
//   delay(1000);           // Keep the tone for 1 second.
//   noTone(buzzerPin);     // Stop the tone.
//   delay(1000);           // Wait for 1 second.
// }
// *** BUZZER ***

// *** PHOTORESISTOR ***
// const int outputPin = A0;

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Analog Sensor Test Sketch...\nReading Sensor.");
// }

// void loop() {
//   int sensorVal = analogRead(outputPin);

//   Serial.print("Sensor value: ");
//   Serial.println(sensorVal);

//   delay(100);
// }
// *** PHOTORESISTOR ***

// *** HUMIDITY + TEMP ***
// #include <DHT.h> //Please make sure you search for, and install the DHT11 library.
//  //Refer to the section on installing libraries for assistance.

// //Variables:
// DHT dht(D7, DHT11); //Initialize the object for the sensor. Pin 7 in this case, and a DHT11 sensor.

// void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  Serial.println("Temp and Humidity (DHT11) demo by Tyson Popynick, please freely edit and use this code for any purpose.\nprot3us1@gmail.com\n\n");
//  dht.begin(); //Begin communication with sensor
// }
// void loop() {
//   float humidity = dht.readHumidity(); //Read and store the humidity from the sensor
//   float temperature = dht.readTemperature(); //Read and store the temperature from the sensor (Celcius)
//   if (isnan(humidity) || isnan(temperature)) { //isnan means is not a number. If the data is coming back corrupt this should catch it
//     Serial.println("Error reading");
//     return; //This will return to the start of the loop without executing the code below.
//   }

//   float heatIndex = dht.computeHeatIndex(temperature,humidity,false); //Read and store the heat index from the sensor
//   Serial.print("Humidity: ");
//   Serial.print(humidity);
//   Serial.print(" Temperature: ");
//   Serial.print(temperature);
//   Serial.print(" Heat Index: ");
//   Serial.println(heatIndex); //Print all the values to the serial monitor
//   delay(2000); //Wait 2 seconds so we arent scrolling the serial screen too fast.
// }
// *** HUMIDITY + TEMP ***

// *** FIRE + DIGITAL TEMP (crveni) ***
// /*
// Modify these variables to change parameters.
// At the bottom of the code there are functions that are activated based on the sensor readings.
// Add your own code inside these functions if you wish to use this code as a starting point.
// The code is well-commented, so you should be able to follow easily.
// ----By Tyson Popynick 2016 - Free to modify or use unrestricted without credit or remuneration. ----
// */
// //Variables:
// int debug_showDigital = 0; //Show digital result in serial output?
// int debug_showAnalog = 1; //Show analog result in serial output?
// int timeDelay = 500; //Time to wait between readings. 1000 = 1 second.
// int thresholdVal = 500; //Threshold level for triggers
// void setup() {
//  // put your setup code here, to run once:
//   Serial.begin(9600); //Start serial communication with the Arduino
//   Serial.println("Arduino Analog/Digital module sketch...\nSerial Started."); //The arduino sends this through the serial monitor to show it is ready.
//   pinMode(D7, INPUT); //Set the digital pin to input. Analog pins are automatically input.
// }
// void loop() {
//   //Read the sensor and store the values.
//   int digitalVal = digitalRead(D7); //Read Digital pin and store result
//   int analogVal = analogRead(A0); //Read analog pin and store result
//   //Debug output
//   if (debug_showDigital) { //If the debug_showDigital variable is set to 1 output data to serial.
//     Serial.print("Digital Result: ");
//     Serial.print(digitalVal);
//   if (debug_showAnalog) {
//     Serial.print(" ");
//   }
//   else {
//     Serial.print("\n");
//   }
//   }
//   if (debug_showAnalog) { //If the debug_showAnalog variable is set to 1 output data to serial.
//     Serial.print("Analog Result: ");
//     Serial.println(analogVal);
//   }
//   //Delay
//   delay(timeDelay); //Wait for specified period, then repeat.
// }
// *** FIRE ***

// *** TEMP DIGITAL ***
//----Begin Code (copy from here)----
//Includes:
#include <OneWire.h> //includes the functions needed to communicate with the 1-wire protocol
#include <DallasTemperature.h> //includes conversion functions from F to C etc, as well as the actual code to talk to the sensor.
//Variables:
OneWire oneWire(D7); //Set the One Wire Data bus on pin 7.
DallasTemperature sensor(&oneWire); //This is passing a reference to the sensor object. This isnt commonly needed. 

void setup() {
 // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Communicating with the temperature sensor via 1-wire protocol. \nFetching data...");
sensor.begin(); //Begin talking to the sensor
}
void loop() {
 // put your main code here, to run repeatedly:
sensor.requestTemperatures(); //Request temperatures from the sensor
Serial.print("Temp: "); //print "Temp: "
Serial.print(sensor.getTempCByIndex(0)); //populate the temperature reading.
Serial.println("c"); //print "Temp: "
}
// *** TEMP DIGITAL ***