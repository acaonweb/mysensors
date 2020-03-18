// Enable debug prints to serial monitor
#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_NRF24
#define CHILD_ID 0

#include <MySensors.h>
// Here we are setting up some water thresholds that we will
// use later. Note that you will need to change these to match
// your soil type and environment. It doesn't do much for me because I'm using domoticz
int thresholdUp = 400;
int thresholdDown = 075;
MyMessage msg(CHILD_ID, V_LEVEL);
unsigned long SLEEP_TIME = 30000;

// We are setting up the pin A0 on the redboard to be our sensor
// pin input:
int sensorPin = A0;

void presentation()
{
present(CHILD_ID, S_MOISTURE);
}

void loop()
{
int sensorValue;
sensorValue = analogRead(sensorPin);
//soilMoisture = map(analogRead(sensorInput), 267, 604, 100, 0);

//send back the values
send(msg.set(sensorValue));
// delay until next measurement (msec)
Serial.print ("test");
sleep(SLEEP_TIME);
}
