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

// Here we are setting up ,some water thresholds that we will
// use later. Note that you will need to change these to match
// your soil type and environment. It doesn't do much for me because I'm using domoticz
int thresholdUp = 400;
int thresholdDown = 075;
MyMessage msg(CHILD_ID, V_LEVEL);
//MyMessage msg(CHILD_ID, V_TEXT);
unsigned long SLEEP_TIME = 1800000;
int BATTERY_SENSE_PIN = A1;
int oldBatteryPcnt = 0;

// We are setting up the pin A0 on the redboard to be our sensor
// pin input:
int sensorPin = A0;

void presentation()
{
  sendSketchInfo("Soil Moisture", "2.0");
  sendSketchInfo("Battery Meter", "1.0");
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
  int dryvalue = 950;
  int wetvalue = 360;
  sensorValueRaw = analogRead(sensorPin);
  //sensorValue = analogRead(sensorPin);
  //sensorValue = map(sensorValueRaw, 950, 360, 100, 0);
  sensorValue = map(sensorValueRaw, dryvalue, wetvalue, 100, 0);

  //send back the values
  send(msg.set(sensorValue));
  // delay until next measurement (msec)
  //Serial.print ("test");
  Serial.println(F("sleeping"));
  Serial.println(sensorValueRaw);
  Serial.println(sensorValue);
  
  // get the battery Voltage
  int sensorValueBattery = analogRead(BATTERY_SENSE_PIN);
  #ifdef MY_DEBUG
    Serial.println(sensorValueBattery);
  #endif

    // 1M, 470K divider across battery and using internal ADC ref of 1.1V
    // Sense point is bypassed with 0.1 uF cap to reduce noise at that point
    // ((1e6+470e3)/470e3)*1.1 = Vmax = 3.44 Volts
    // 3.44/1023 = Volts per bit = 0.003363075


  int batteryPcnt = sensorValueBattery / 10;
  #ifdef MY_DEBUG
    float batteryV  = sensorValueBattery * 0.003363075;
    Serial.print("Battery Voltage: ");
    Serial.print(batteryV);
    Serial.println(" V");

    Serial.print("Battery percent: ");
    Serial.print(batteryPcnt);
    Serial.println(" %");
  #endif

  if (oldBatteryPcnt != batteryPcnt) {
        // Power up radio after sleep
        sendBatteryLevel(batteryPcnt);
        oldBatteryPcnt = batteryPcnt;
  }


  sleep(SLEEP_TIME);
}
