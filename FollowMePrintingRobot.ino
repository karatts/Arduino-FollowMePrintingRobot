/* Follow Me Printing Robot
   Created by Kara Tong in May 2016
   
   Please use this code for your personal use ONLY.
   Running off of an Arduino Uno R3 with SMD.
   Hardware includes Zumo v1.2, pair of IR Beacons, Thermal Printer
   Other parts necessary are 2 9v batteries.
   
   Pins make use of the front expansion, excluding LED_PIN 13
 */

#include "Adafruit_Thermal.h"
#include <ZumoMotors.h>
#include <SoftwareSerial.h>

#define LED_PIN 13 //ZumoPinConfirmation
#define irSensorPinNorth A4 //IR Sensor - North
#define irSensorPinEast A5 //IR Sensor - East RIGHT
#define irSensorPinSouth A1 //IR Sensor - South
#define irSensorPinWest A2 //IR Sensor - West LEFT

#define printerInput 5 //GREEN
#define printerOutput 11 //YELLOW

//TURNS 0 WHEN SENSING IR BEACON
//1 IF NOT SENSING IR BEACON

ZumoMotors motors;
SoftwareSerial portOne(0, 1); //RX to TX
SoftwareSerial thermalPrinter(printerOutput, printerInput); //RX to TX
int distance = 0;
int previousPick = -1;
Adafruit_Thermal printer(&thermalPrinter);

void setup() {
  pinMode (LED_PIN, OUTPUT);
  pinMode(irSensorPinNorth, INPUT);
  pinMode(irSensorPinEast, INPUT);
  pinMode(irSensorPinSouth, INPUT);
  pinMode(irSensorPinWest, INPUT);

  portOne.begin(9600); //Zumo readings
  // prints title with ending line break 
  //portOne.println("Program Starting"); 
  // wait for the long string to be sent 
  
  thermalPrinter.begin(9600); //Printer output
  printer.begin();
  printer.justify('C');
  printer.boldOn();
  printer.setSize('S');
  printer.println(F("Ready...set...GO!\n"));
  printer.feed(2);
  printer.sleep();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  portOne.listen();
  if((digitalRead(irSensorPinNorth)) == 0){
    goForward();
    distance++;
      message();
  }

 
  else if((digitalRead(irSensorPinSouth)) == 0){
    goBackward();
    distance++;
      message();
  }

  
  else if((digitalRead(irSensorPinWest)) == 0){
    goLeft();
    distance++;
      message();
  }


  else if((digitalRead(irSensorPinEast)) == 0){
    goRight();
    distance++;
    message();
  }

}

void message(){
  thermalPrinter.listen();
  if(distance % 10 == 0){
    int pickOne = random(1,11);
    printer.wake();
    while (pickOne == previousPick){
      pickOne = random(1,11);
    }
    if(pickOne == 1){
      printer.println(F("Having so much\n fun exploring!\n"));
    }
    else if(pickOne == 2){
      printer.println(F("Are we there\n yet?\n"));
    }
    else if(pickOne == 3){
      printer.println(F("Rolling this\n way!\n"));
    }
    else if(pickOne == 4){
      printer.println(F("Getting tired!\n")); 
    }
    else if(pickOne == 5){
      printer.println(F("Let's take\n a break!\n")); 
    }
    else if(pickOne == 6){
      printer.println(F("This is boring!\n"));
    }
    else if(pickOne == 7){
      printer.println(F("Let's go\n over there!\n"));
    }
    else if(pickOne == 8){
      printer.println(F("Can we stop\n moving now?\n"));
    }
    else if(pickOne == 9){
      printer.println(F("I'm hungry...\n"));
    }
    else if(pickOne == 10){
      printer.println(F("I need to go\n to the bathroom!\n"));
    }
    printer.feed(1);
    printer.sleep();      // Tell printer to sleep   
    previousPick = pickOne;
  }
}

void goForward(){
 for (int speed = 0; speed <= 250; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = 250; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
}

void goBackward(){
for (int speed = 0; speed >= -250; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  
  for (int speed = -250; speed <= 0; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
}

void goLeft(){
  for (int speed = 0; speed <= 250; speed++)
  {
    motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = 250; speed >= 0; speed--)
  {
    motors.setRightSpeed(speed);
    delay(2);
  }
}

void goRight(){
  for (int speed = 0; speed <= 250; speed++)
  {
    motors.setLeftSpeed(speed);
    delay(2);
  }

  for (int speed = 250; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed);
    delay(2);
  }
}
