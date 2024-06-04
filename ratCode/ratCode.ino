#include <Servo.h>

#define eyeOne 9
#define eyeTwo 10
Servo myservo;

#define sensorPin A0

//for LDR
int sensorValue = 0;
//for servo
int pos = 0; 

void setup()
{
  Serial.begin(9600);
  pinMode(eyeOne, OUTPUT);
  pinMode(eyeTwo, OUTPUT);
  myservo.attach(11); 
  pinMode(sensorPin, INPUT);
}

void loop()
{ 
 //change = sensorValue - copyValue; RATE OF CHANGE IDEA

 //DATA SMOOTHING FOR LIGHT SENSOR//
 //sensorValue = analogRead(sensorPin);
 int numReads = 10; // number of samples 
 int sensorSum = 0; // sum of readings 

 //Getting a sum of readings via for loop
 for( int i = 0; i < numReads; i++){
  sensorValue = analogRead(sensorPin);
  sensorSum += sensorValue;
  delay(1); //totals up to a delay of 10 per loop
  }
  int sensorAverage = sensorSum / numReads; //average of sensor readings
  int sensortoBrightness = map(sensorAverage, 900, 0, 0, 255);//for gradual changing of LED brightness as person approaches
  Serial.println(sensorValue);
  Serial.println(sensorAverage); //printing the average to terminal
  Serial.println(sensortoBrightness);
  analogWrite(eyeOne, sensortoBrightness);
  analogWrite(eyeTwo, sensortoBrightness);
  
  //make it so that tail isnt wagging to begin with so motor doesnt overheat
  //make it so that if servoAverage = highValue, delay = 5
  //and if ServoAverage = lowValue. delay = 3 
  //and if ServoAverage = superlowValue, delay = 2
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
       // in steps of 1 degree
    myservo.write(pos);
    if (sensorAverage > 650) {
      delay(5); //neutral speed wagging of tail SHOULD ADJUST TO A VARIABLE THAT CHANGES
    }
    else if ((sensorAverage > 550) && (sensorAverage <= 650)) {
        delay(3); //frantic speed wagging of tail
    }
    else if (sensorAverage <= 550) {
        delay(2); //very frantic wagging of tail   
    }                
  } 
       
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    if (sensorAverage > 650) {
      delay(5); //neutral speed wagging of tail
    }
    else if ((sensorAverage > 550) && (sensorAverage <= 650)) {
        delay(3); //frantic speed wagging of tail
    }
    else if (sensorAverage <= 550) {
        delay(2); //very frantic wagging of tail   
    }                
  } 
    
}
  

//I have used the LDR to interact with all items

//Step One: There is a brightness isue with the LEDS, check all
//resistors are correct, and that there is sufficient power supplied

//Step Two: Convert the code so that for at a certain sensorValue
//the tail moves continuously and the LEDs light up.
//e.g when sensorValue = 800, the eyes start lighting up,
//when sensorValue = 600, the servo starts moving left and right.

//CREATE: One more case for if the person is extremely close, with
//the eyes of the rat flashing.