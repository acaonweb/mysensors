// Enable debug prints to serial monitor
#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_NRF24
#define CHILD_ID 0

//
#define MY_SMART_SLEEP_WAIT_DURATION_MS 5000

#include <MySensors.h>
//
#define SLEEP_MODE true
//

// Here we are setting up some water thresholds that we will
// use later. Note that you will need to change these to match
// your soil type and environment. It doesn't do much for me because I'm using domoticz
int thresholdUp = 400;
int thresholdDown = 075;
MyMessage msg(CHILD_ID, V_LEVEL);
//MyMessage msg(CHILD_ID, V_TEXT);
unsigned long SLEEP_TIME = 600000;

// We are setting up the pin A0 on the redboard to be our sensor
// pin input:
int sensorPin = A0;

void presentation()
{
present(CHILD_ID, S_MOISTURE);
//present(CHILD_ID, S_INFO);
}


void setup ()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("Warm up"));
  delay(15000);
}

void loop()
{
int sensorValue;
int sensorValueRaw;
int xa, xb, ya, yb;

xa=10;
xb=150;
ya=100;
yb=0;



sensorValueRaw = analogRead(sensorPin);
//sensorValue = analogRead(sensorPin);



sensorValue = map(sensorValueRaw, 950, 360, 100, 0);


//send back the values
send(msg.set(sensorValue));
// delay until next measurement (msec)
//Serial.print ("test");
Serial.println(F("sleeping"));
Serial.println(sensorValueRaw);
Serial.println(sensorValue);
sleep(SLEEP_TIME);
}
