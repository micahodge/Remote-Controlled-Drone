#include <Wire.h> // add wire library
#include <SoftwareSerial.h> // add SDA/SCL library
#include <Adafruit_Sensor.h> // gyro library
#include <Adafruit_BNO055.h> // gyro library
#include <Servo.h> // add servo library

Servo esc1; // first motor
Servo esc2;// second motor
Servo esc3; // thrid motor
Servo esc4; // fourth motor
SoftwareSerial BTSerial(10,11); // make SDA/SCL to 10 and 11
Adafruit_BNO055 bno = Adafruit_BNO055(); // gyroscope

int power = 52, buddy = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0; // initializing variables
int stop = 1000, hover = 1400, up = 1410, down = 1325, speed = 1000, startup = 1200; // initializing motor speed variables
float cat = 0, sum = 0, average = 0, proportion = 2.25, derivative = 2.25, changeintime = 0.0, proportionZ = 0.0, proportionY = 0.0, derivativeZ = 0.0, derivativeY = 0.0;// initializing variables
float zaxis = 0, yaxis = 0, zadjust = 0, yadjust = 0, lastZ = 0.0, lastY = 0.0;// initializing variables
long lasttime = 0.0, currenttime = 0.0; // initializng millis variables
String finale = "";// initializing string

void setup() {
  pinMode(power, OUTPUT); // red test LED
  bno.begin(); // start gyro
  BTSerial.begin(9600); // begin BT monitor
  Serial.begin(9600); // begin serial monitor
  bno.setExtCrystalUse(true);
  esc1.attach(9); // pin for first motor
  esc2.attach(7); // pin for second motor
  esc3.attach(6); // pin for third motor
  esc4.attach(5); // pin for fourth motor
  esc1.writeMicroseconds(1000); // start at 0 throttle
  esc2.writeMicroseconds(1000);// start at 0 throttle
  esc3.writeMicroseconds(1000);// start at 0 throttle
  esc4.writeMicroseconds(1000);// start at 0 throttle
  delay(3000); // delay 3 seconds
  lasttime = millis(); // start millis
}

void loop() { // start loop
 if(BTSerial.available()) // if the port is open
  {finale = BTSerial.readStringUntil('\n');}  // read the value coming from visual studio program
  char delaying = finale[0]; //initializing delaying variable
switch (delaying) // switch case for delaying
{
case '1': // case 1
{
  digitalWrite(power, 1); // turn on test light
  break;} // break from case
case '2': // case 2
{
  digitalWrite(power, 0); // turn off test light
  break; // break from case
}
case '3': // case 3
{
  speed = up; // speed = up
  break; // break from case
}
case '4': // case 4
{
  speed = down; // speed = down
  break; // break from case
}
case '5': // case 5
{
  speed = stop; //speed = 0
  break; // break from case
}
case '6': // case 6
{
  speed = hover; // speed = hover
  break; // break from case
}}
 gyroscope(); // call gyro function
}

void gyroscope() // gyro function
{
  currenttime = millis(); // read millis time
  changeintime = (currenttime - lasttime) / 1000.0; // calculate change in time
  lasttime = currenttime; // make the last time the current time for future "changeintime" calculations
  sensors_event_t snickers = sensors_event_t(); // start the gyro sensor (called in "snickers" after our recent horse)
  bno.getEvent(&snickers, Adafruit_BNO055::VECTOR_EULER); // start the gyro sensor
  zaxis = snickers.orientation.z + 1.8; // calibrate zaxis to 0 at rest
  yaxis = snickers.orientation.y + 2.28;// calibrate yaxis to 0 at rest
  Serial.println(zaxis); // for testing purposes
  Serial.println(yaxis);// for testing purposes
  proportionZ = proportion * zaxis; // calculate proportionZ change
  proportionY = proportion * yaxis; // calculate proportionY change
  derivativeZ = derivative * ((zaxis - lastZ) / changeintime); // calculate derivative Z change 
  derivativeY = derivative * ((yaxis - lastY) / changeintime); // calculate derivative Y change 
  lastZ = zaxis; // set current value as zaxis for next loop calculation
  lastY = yaxis;// set current value as yaxis for next loop calculation
  zadjust = proportionZ + derivativeZ; // calculate final adjust value for zaxis
  yadjust = proportionY + derivativeY;// calculate final adjust value for yaxis
  int speed1 = constrain(speed - zadjust + yadjust, 1000, 2000);// find speed for motor 1 and constrain it to 1000-2000
  int speed2 = constrain(speed - zadjust - yadjust, 1000, 2000);// find speed for motor 2 and constrain it to 1000-2000
  int speed3 = constrain(speed + zadjust + yadjust, 1000, 2000);// find speed for motor 3 and constrain it to 1000-2000
  int speed4 = constrain(speed + zadjust - yadjust, 1000, 2000);// find speed for motor 4 and constrain it to 1000-2000
  esc1.writeMicroseconds(speed2); // send signal to motor 1 (speed1 does not go to  esc1 beacuse the gyroscope is not facing forward on the drone)
  esc2.writeMicroseconds(speed1); // send signal to motor 2
  esc3.writeMicroseconds(speed4); // send signal to motor 3
  esc4.writeMicroseconds(speed3);// send signal to motor 4
  Serial.println(speed2); // for testing purposes
  Serial.println(speed1);// for testing purposes
  Serial.println(speed4);// for testing purposes
  Serial.println(speed3);// for testing purposes
  delay(1200); // to stop over correction
}