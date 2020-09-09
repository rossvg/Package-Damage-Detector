
// ADXL 335 PINS
// Analog pins that the accelerometer will connect to on the arduino
const int xPin = A3;
const int yPin = A2;
const int zPin = A1;

//ADXL Variables
// Thresholds that indicate when the package is in potential danger
// These values were calibrated in testing and are subject to change
const float adxlThreshHigh = 2.01;
const float adxlThreshLow = 1.30;
// Final value variables for the accelerometer after they have been converted to voltage
float xval;
float yval;
float zval;



//SONAR PINS
// Analog pin for the sonar sensor into the Arduino
const int sonarPin = A0;

//SONAR Variables
long sonarVolt, cm; // Sonar voltage, and cm is how far away the object is from the sensor
int sum = 0; // variable used in the subroutine
int sonarSampleSize = 30; // how many samples are taken before a final value is calculated
int sonarThresh = 30; // The treshold will indicate danger 30cm away

//ADXL SPEAKER
const int adxlSpeakerPin = 11;

//SONAR SPEAKER
const int sonarSpeakerPin = 10;

//GREEN LED
const int greenLED = 7;

//RED LED
// Warning LED
const int redLED = 8;




void setup() {

  Serial.begin(9600); // open up serial port communications

  //LED PIN SETUP
  //set LED pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);






}

/********************MAIN PROGRAM*****************************/

void loop() {

  //..................READ ADXL VALUES...............
  // This section converts the accelerometer values to voltage and displays them in readable format on the serial monitor.
  xval = analogRead(xPin) * (3.3 / 675.84);
  yval = analogRead(yPin) * (3.3 / 675.84);
  zval = analogRead(zPin) * (3.3 / 675.84);

  Serial.print(xval);
  Serial.print(" ")
  Serial.print(yval);
  Serial.print(" ")
  Serial.print(zval);
  Serial.println();
  //.................. FINISHED READ ADXL VALUES...............


  //...............SPEAKER TONE AND WARNING...................
  //This section plays the speaker warning for the sonar sensor if potential damage is detected
  if (getDist() <= sonarThresh) { // If damage is detected, execute the if statement
    tone(sonarSpeakerPin, getDist() * 100); // play the warning tone more frequently as the object gets closer to the sensor
    digitalWrite(redLED, HIGH); // turn on the warning led
    digitalWrite(greenLED, LOW); // turn on the green led
  }

  //............. END SPEAKER TONE AND WARNING........................

  //ADXL WARNING
  // This section plays the warning tone for the adxl 
  else if (testX() || testY() || testZ()) { //if any of the tresholds are breached, execute the if statement

    digitalWrite(redLED, HIGH); //turn on warning led
    digitalWrite(greenLED, LOW); // turn off green led

    tone(adxlSpeakerPin, 5000); // play the speaker tone.
  }

// This else statment is for when the object is in no potential danger
  else {
    noTone(adxlSpeakerPin);
    noTone(sonarSpeakerPin);
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  }
  // END ADXL WARNING
}
/***********************************END MAIN PROGRAM**********************/7



//..................SONAR SENSOR METHODS................................

// The following subroutine calcualtes the distance in centimetres how far away an object is
int getDist() {

  sum = 0; //reset sum to zero. This is the sum of all the sample sizes

  for (int i = 0; i < sonarSampleSize ; i++) // this for loop gathers all samples for the sonar
  {
    cm = analogRead(sonarPin) * 1.27; // convert the value into cm
    sum = sum + cm; // add to the running total
    delay(5); // delayso the sensor can accurately read the next value
  }
  
  return (sum / sonarSampleSize); // return the average of all the values the main program

}

//........................ADXL METHODS ..........................................
// The folowing methods read values from the accelerometer. If the values exceed the 
// calibrated thresholds, a value of 1 is returned to the main program.
// All 3 axis are tested for values being outside the threshold range.

boolean testX () { // test the x-axis

  xval = analogRead(xPin) * (3.3 / 675.84); // read values and convert to voltage

  if (xval < adxlThreshLow || xval > adxlThreshHigh) { // if the value is too high or too low, return a 1
    return true;
  }
  else { // value is within threshold.
    return false;
  }
}


boolean testY () {

// These variables are specific to the y -axis as the sensor had trouble properly reading this axis
float yThreshHigh = 1.8;
float yThreshLow = 1.5;

  yval = analogRead(yPin) * (3.3 / 675.84);


  if (yval < yThreshLow || yval > yThreshHigh) {
    return true;
  }
  else {
    return false;
  }
}


boolean testZ () {

  zval = analogRead(zPin) * (3.3 / 675.84);

  if (zval < adxlThreshLow || zval > adxlThreshHigh) {
    return true;
  }
  else {
    return false;
  }
}

//...................................END ADXL METHODS....................................







