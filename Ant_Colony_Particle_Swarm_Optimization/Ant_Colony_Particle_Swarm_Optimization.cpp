/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Title: Ant Colony Particle Swarm Optimizaton
 * Author: Anil Harish
 * Version: 1.4
 * Copyright (C) 2018  Anil Harish
 * For further details see: https://drive.google.com/open?id=1N0xl4SRGilIsdHIX5g87I15XixuB7TVs
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                                      INCLUDE PREEXISITING AND NEW LIBRARIES
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include<Servo.h>                                             //include servo.h library
#include <IRremote.h>                                         //include modifed Ken Sherrif Library for 4 Infrared Receivers for omnidirectional sensors available at github.com/anilharish/Arduino/IRremote
#define trigPin 10                                            //define universal configuration for the triggering ultrasonic pluses at PIN 10
#define echoPin 9                                             //define universal configuration for the receiving ultrasonic pluses at PIN 9

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                                  PREDEFINED AURDINO FUNCTIONS FOR MOTOR CONTROL
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

Servo sweepservo;                                             //use predifined Arduino Servo library components and predefined objects for ultrasonic sweep wheel
Servo rightwheel;                                             //use predifined Arduino Servo library components and predefined objects for right wheel
Servo leftwheel;                                              //use predifined Arduino Servo library components and predefined objects for right wheel

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                                DEFINE VARIABLES FOR ULTRASNOIC RANGEFINDER SENSOR
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int pos,distance;                                             //define varibles position and distance for the ultrasonic rangefinder sensor

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                         DEFINE INPUT/OUTPUT PINS AND VARIABLES FOR OMNIDIRECTIONAL SENSOR
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int RECV_PIN1 = 4;                                            //set pin 4 to receive infrared signals in quadrant 1 (135 deg to 45 deg)
int RECV_PIN2 = 5;                                            //set pin 5 to receive infrared signals in quadrant 2 (45 deg to 315 deg)
int RECV_PIN3 = 6;                                            //set pin 6 to receive infrared signals in quadrant 3 (315 deg to 225 deg)
int RECV_PIN4 = 7;                                            //set pin 4 to receive infrared signals in quadrant 4 (225 deg to 135 deg)

IRsend irsend;                                                //define varible for decoding received IR signals
IRrecv irrecv1(RECV_PIN1);                                    //define varible for storing recived IR signal in quadrant 1 (135 deg to 45 deg)
IRrecv irrecv2(RECV_PIN2);                                    //define varible for storing recived IR signal in quadrant 2 (45 deg to 315 deg)
IRrecv irrecv3(RECV_PIN3);                                    //define varible for storing recived IR signal in quadrant 3 (315 deg to 225 deg)
IRrecv irrecv4(RECV_PIN4);                                    //define varible for storing recived IR signal in quadrant 4 (225 deg to 135 deg)

decode_results results1;                                      //define varible to decode the signal received at quadrant 1 (135 deg to 45 deg)
decode_results results2;                                      //define varible to decode the signal received at quadrant 2 (45 deg to 315 deg)
decode_results results3;                                      //define varible to decode the signal received at quadrant 3 (315 deg to 225 deg)
decode_results results4;                                      //define varible to decode the signal received at quadrant 4 (225 deg to 135 deg)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                       SETUP FOR TRIGGERING ULTRASONIC RANGERFINDER, IR RECEIVERS AND SERVOS
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup()
{
  Serial.begin (9600);                                        //start serial communication at 9600 baud rate
  Serial.println("Enabling ultrasonic rangefinder sensor");   //print information over the serial channel to enable ultrasonic rangerfinder
  pinMode(trigPin, OUTPUT);                                   //define trigger pin (pin 10) as output pin
  pinMode(echoPin, INPUT);                                    //define echo pin (pin 9) as input pin
  Serial.println("Ultrasonic rangefinder sensor functional"); //print information over the serial channel showing that ultrasonic rangefinder is enabled
  sweepservo.attach(13);                                      //attach pin 13 to sweepservo previously linked with servo arduino library
  Serial.println("Enabling IR sensors");                      //print information over the serial channel to enable IR sensors
  irrecv1.enableIRIn();                                       //start the receivers 1 to 4 (can be used upto 6 IR sensors)
  irrecv2.enableIRIn();
  irrecv3.enableIRIn();
  irrecv4.enableIRIn();
  Serial.println("IR sensors functional");                    //print information over the serial channel showing that the IR sensors are operational
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                            MAIN OPERATIONAL LOOP ANT COLONY PARTICLE SWARM OPTIMIZATION
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void loop()
{
  long leftarea,centerarea,rightarea;                         //initialize the variables leftarea, centerarea and right area
  
 if (irrecv1.decode(&results1))                               //decode the signal and write the decoded data to results1
  {
    if (results1.value==0xa90)                                //if the value of result1 is HEX code a90 then execute the following statements.
    {
      Serial.print("Signal received at sensor 1: ");          //let the user know that sensor 1 has received the required signal and contains A90 as decoded data
      Serial.println(results1.value, HEX);                    //print the value of the decoded signal
      centralizescanner();                                    //centralise the ultrosonic rangefinder sensor
      obstacle();                                             //acquire the distance to the end point of the source.
      while (distance>=4)                                     //when distance to the source is greater than 4 execute the following statements
      {
        forward();                                            //move forward for 0.5 seconds
        delay (500);
        obstacle();                                           //rescan distance to the source
      }
      while (distance<4)                                      //when distance to the source is less than 4 execute the following statements
      {
        irsend.sendSony(0xa90, 12);                           //send the similar broadcasting signature signal in onmidirectional IR sensor
        Serial.println("Source found: Broadcasting signal");  //use the user know that robot has found the source and is broadcasting signal with repeated pluses at 25 Hz.
        delay(40);
      }
      irrecv1.resume();                                       //resume receiving singal at sensor 1
    }
  }
/*###################################################################################
 #                  REPEAT OPERATION FOR SENSORS 2 TO 4                             #
 ####################################################################################*/
 if (irrecv2.decode(&results2))
  {
    if (results2.value==0xa90)
    {
      turnright();
      delay (250);
      turnright();
      Serial.print("Signal received at sensor 2: ");
      Serial.println(results2.value, HEX);
      centralizescanner();
      obstacle();
      while (distance>=4)
      {
        forward();
        delay (300);
        obstacle();
      }
      while (distance<4)
      {
        irsend.sendSony(0xa90, 12);
        Serial.println("Broadcasting Signal");
        delay(40);
      }
      irrecv2.resume();
    }
  }
 if (irrecv3.decode(&results3))
  {
    if (results3.value==0xa90)
    {
      uturn();
      delay (700);
      Serial.print("Signal received at sensor 3: ");
      Serial.println(results3.value, HEX);
      centralizescanner();
      obstacle();
      while (distance>=4)
      {
        forward();
        delay (500);
        obstacle();
      }
      while (distance<4)
      {
        irsend.sendSony(0xa90, 12);
        Serial.println("Broadcasting Signal");
        delay(40);
      }
      irrecv3.resume();
    }
  }
 if (irrecv4.decode(&results4))
  {
    if (results4.value==0xa90)
    {
      turnleft();
      delay (500);
      turnleft();
      Serial.print("Signal received at sensor 4: ");
      Serial.println(results4.value, HEX);
      centralizescanner();
      obstacle();
      while (distance>=4)
      {
        forward();
        delay (500);
        obstacle();
      }
      while (distance<4)
      {
        irsend.sendSony(0xa90, 12);
        Serial.println("Broadcasting Signal");
        delay(40);
      }
      irrecv4.resume();
    }
  }
/*###################################################################################
 #                        END SENSOR SIGNAL ACQUISITION                             #
 ####################################################################################*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                                        SUB LOOP FOR OBSTACLE AVOIDANCE
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
 
  centralizescanner();                                        //crentralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
  delay(500);                                                 //wait for 0.5 seconds for servo to reposition
  lookright();                                                //turn the sensor head to 20 degrees in the 1st quadrant
  delay (500);                                                //wait for 0.5 seconds
  obstacle();                                                 //aquire the distance to the right vertice
  rightarea=distance;                                         //store the value of the distance in variable named rightarea
  Serial.print(distance);                                     //print the distance for user and append cm measuring scale to the output.
  Serial.println(" cm");
  align();                                                    //turn the sensor head from 20 degrees to 90 degrees
  delay (500);                                                //wait for 0.5 seconds for servo to reposition
  obstacle();                                                 //aquire the distance along the line of the robot body
  centerarea=distance;                                        //store the value of the distance in variable named centerarea
  Serial.print(distance);                                     //print the distance for user and append cm measuring scale to the output.
  Serial.println(" cm");
  lookleft();                                                 //turn the sensor head from 90 degrees to 160 degrees
  delay (500);                                                //wait for 0.5 seconds for servo to reposition
  obstacle();                                                 //aquire the distance along the line of the robot body
  leftarea=distance;                                          //store the value of the distance in variable named leftarea
  Serial.print(distance);                                     //print the distance for user and append cm measuring scale to the output.
  Serial.println(" cm");

/*###################################################################################
 #                   DECISION TREE BASED ON VERTICES DATA                           #
 ####################################################################################*/

    if ((leftarea<10) && (rightarea<10))                      //compare left area and right area vertice scans to check if their distance is less than 10 cms
    {
      if (centerarea<10)                                      //provided the centre area is also less than 10 cms continue with the below statements
      {
        centralizescanner();                                  //crentralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
        uturn();                                              //avoid corners and perform u-turn
      }
      else if (centerarea>=10)                                //provided there is no obstacle in the centre vertice and distance is greater than 10 cms
      {
        centralizescanner();                                  //crentralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
        forward();                                            //move forward and continue optimization
      }
    }
    else if (leftarea<10 && (rightarea>10))                   //compare left area and right area vertice scans
    {                                                         //if left area is less than 10 cms and right area is greater than 10 cms execute following statements
      centralizescanner();                                    //centralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
      turnright();                                            //turn right and continue optimization
    }
    else if (rightarea<10 && (leftarea>10))                   //compare right area and left area vertice scans
    {                                                         //if right area is less than 10 cms and left area is greater than 10 cms execute following statements
      centralizescanner();                                    //centralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
      turnleft();                                             //turn left and continue optimization
    }
    else if (centerarea<10)                                   //if centre area vertice scan is less than 10 cms
    {
      if (leftarea>=10)                                       //provided left area is greater than 10 cms
      {
        centralizescanner();                                  //centralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
        turnleft();                                           //turn left and continue optimization
      }
      else if (rightarea>=10)                                 //provided right area is greater than 10 cms
      {
        centralizescanner();                                  //centralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
        turnright();                                          //turn right and continue optimization
      }
      else if ((leftarea<10) && (rightarea<10))               //provided both left and right area is less than 10 cms
      {
        centralizescanner();                                  //centralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
        uturn();                                              //perform u-turn and continue optimization
      }
    }
   else
    {
      centralizescanner();                                    //centralize the ultrasnoic rangefinder sensor at 90 degrees instantaniously
      forward();                                              //more forward and continue optimization
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                              FUNCTION CALL OF ULTRASONIC RANGEFINDER DISTANCE AQUISITION
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void obstacle()                                               //name the function obstacle
{
  long duration;                                              //create a variable named duration
  digitalWrite(trigPin, LOW);                                 //turn off ultrasonic signal at trigger pin for 2 milliseconds
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);                                //turn on ultrasonic signal at trigger pin for 10 milliseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);                                 //turn off ultrasonic signal at trigger pin
  duration = pulseIn(echoPin, HIGH);                          //write the time duration until the ultrasonic signal is received at echo pin to duration variable keep the pin at on
  distance = (duration) / 20;                                 //calculate the distance and write it to variable distance
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                                    FUNCTION CALLS OF ULTRASONIC RANGEFINDER HEAD
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*###################################################################################
 #                            CRENTRALIZE SENSOR HEAD                               #
 ####################################################################################*/
void centralizescanner()                                      //name the function centralize scanner
{
  pos=90;                                                     // write integer 90 to global variable pos
  sweepservo.write(pos);                                      // tell servo to go to position in variable 'pos'
  delay(15);                                                  // waits 15ms for the servo to reach the position
}
/*###################################################################################
 #                    PIVOT SENSOR HEAD FROM 20 DEG TO 90 DEG                       #
 ####################################################################################*/
void align()                                                  //name the function align
{
  for (pos = 20; pos <= 90; pos +=5 )                         //the rate of change of servo position to reduce mechanical strain - 5 degree/15 milliseconds
  {
    sweepservo.write(pos);                                    //tell servo to go to position in variable 'pos'
    delay(15);                                                //waits 15ms for the servo to reach the position
  }
}
/*###################################################################################
 #                    PIVOT SENSOR HEAD FROM 20 DEG TO 90 DEG                       #
 ####################################################################################*/
void lookright()                                              //name the function lookright
{
  for (pos = 90; pos >= 20; pos -= 5)                         //the rate of change of servo position to reduce mechanical strain - 5 degree/15 milliseconds
  {
    sweepservo.write(pos);                                    //tell servo to go to position in variable 'pos'
    delay(15);                                                //waits 15ms for the servo to reach the position
  }
}
/*###################################################################################
 #                    PIVOT SENSOR HEAD FROM 90 DEG TO 160 DEG                       #
 ####################################################################################*/
void lookleft()                                               //name the function lookright
{
  for (pos = 90; pos <= 160; pos += 5)                        //the rate of change of servo position to reduce mechanical strain - 5 degree/15 milliseconds
  {
    sweepservo.write(pos);                                    //tell servo to go to position in variable 'pos'
    delay(15);                                                //waits 15ms for the servo to reach the position
  }
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *                                                                        FUNCTION CALLS OF WHEEL SERVOS
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*###################################################################################
 #                                   MOVE FORWARD                                   #
 ####################################################################################*/
void forward()
{
  leftwheel.attach(12);                                       //assign pin 12 to left wheel
  rightwheel.attach(11);                                      //assign pin 11 to right wheel
  leftwheel.writeMicroseconds(1700);                          //send 17 microsecond period PWM signals to left wheel (calibrate for your surface and wheel)
  rightwheel.writeMicroseconds(1300);                         //send 13 microsecond period PWM signals to right wheel (calibrate for your surface and wheel)
  delay(200);                                                 //send PWM signals for 0.2 seconds
  leftwheel.detach();                                         //remove leftwheel pin assignment to have no stray signals inducing movement
  rightwheel.detach();                                        //remove rightwheel pin assignment to have no stray signals inducing movement
}
/*###################################################################################
 #                                    TURN RIGHT                                    #
 ####################################################################################*/
void turnright()
{
  leftwheel.attach(12);                                       //assign pin 12 to left wheel
  rightwheel.attach(11);                                      //assign pin 11 to right wheel
  leftwheel.writeMicroseconds(1700);                          //send 17 microsecond period PWM signals to left wheel (calibrate for your surface and wheel)
  rightwheel.writeMicroseconds(1700);                         //send 17 microsecond period PWM signals to right wheel (calibrate for your surface and wheel)
  delay(200);                                                 //send PWM signals for 0.2 seconds
  leftwheel.detach();                                         //remove leftwheel pin assignment to have no stray signals inducing movement
  rightwheel.detach();                                        //remove rightwheel pin assignment to have no stray signals inducing movement
}
/*###################################################################################
 #                                     TURN LEFT                                    #
 ####################################################################################*/
void turnleft()
{
  leftwheel.attach(12);                                       //assign pin 12 to left wheel
  rightwheel.attach(11);                                      //assign pin 11 to right wheel
  leftwheel.writeMicroseconds(1300);                          //send 13 microsecond period PWM signals to left wheel (calibrate for your surface and wheel)
  rightwheel.writeMicroseconds(1300);                         //send 13 microsecond period PWM signals to right wheel (calibrate for your surface and wheel)
  delay(300);                                                 //send PWM signals for 0.2 seconds
  leftwheel.detach();                                         //remove leftwheel pin assignment to have no stray signals inducing movement
  rightwheel.detach();                                        //remove rightwheel pin assignment to have no stray signals inducing movement
}
/*###################################################################################
 #                                      U - TURN                                    #
 ####################################################################################*/
void uturn()
{
  leftwheel.attach(12);                                       //assign pin 12 to left wheel
  rightwheel.attach(11);                                      //assign pin 11 to right wheel
  leftwheel.writeMicroseconds(1700);                          //send 17 microsecond period PWM signals to left wheel (calibrate for your surface and wheel)
  rightwheel.writeMicroseconds(1700);                         //send 17 microsecond period PWM signals to right wheel (calibrate for your surface and wheel) 
  delay(500);                                                 //send PWM signals for 0.2 seconds
  leftwheel.detach();                                         //remove leftwheel pin assignment to have no stray signals inducing movement
  rightwheel.detach();                                        //remove rightwheel pin assignment to have no stray signals inducing movement
}
