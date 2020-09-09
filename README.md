# Package-Damage-Detector
Using an Arduino and components to detect and alert operators of possible damage to a mail package while in transit.

## Full Description
Final project for Sensors and Actuators course. With delivery soaring in popularity (Amazon), this prototype is meant to mitigate potential damage while in transit. An accelerometer was used to detect movement of the package above a certain speed threshold. If breached, the red LED would light up and a speaker tone would play indicating potential damage. The larger the acceleration, the louder the speaker tone. A sonar sensor was used to detect proximity of package to anything solid object in the surrounding environment. If the package began to get close to another object past a certain distance threshold, a tone would play and the red LED would light up. The closer the package gets, the louder the speaker tone. When no damage is detected, the package is in a no-potential-damage state indicated by a lit green LED

## Technical Components used
* Arduino Uno
* ADXL 335 Accelerometer
* SONAR Sensor
* 2 Simple Resistance Speakers
* 1 Green LED, 1 Red LED

*Group Members: Ross Vrana-Godwin and John Polak*
