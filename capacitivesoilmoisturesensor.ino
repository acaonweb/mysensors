//  Made by Piplikoc
//  Piplikoc Tutorials
//  youtube.com/channel/UClFlzxH3Mw1ZsRq7IDPgX-A

int sensorInput = A0; // soil probe is on analog input A5

double soilMoisture;  // we will store the percentage here that we got from the sensor

void setup()   {
  Serial.begin(9600); // some debug messages will display sensor raw data
  Serial.println("Ready to write");
}

void loop() {
  Serial.println (analogRead(sensorInput));
  Serial.print ("New Sensor Reading: ");
  soilMoisture = map(analogRead(sensorInput), 267, 604, 100, 0); // first: get the data   second: lowest value of the analogRead(sensorInput)   third: highest value of the analogRead(sensorInput)
  Serial.print (soilMoisture);
  Serial.println (" %");
  delay(1000);
}
