#include "Arduino_LED_Matrix.h"
#include "L298NX2.h"
#include <IRremote.h>



ArduinoLEDMatrix matrix;
int IRrecPin = 12;



byte frame[8][12] = {  //This is an array of 8x12, 1 is pixel on, 0 is pixel off. I drew a angry face to show the fierceness of the car. 

  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },

  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },

  { 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0 },

  { 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0 },

  { 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0 },

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

  { 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0 },

  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 }

};

//9/6 are the analog pins of the left motor and 10/11 are the analog pins of the right motor.
L298NX2 motor(9, 6, 10, 11); //Creates our motor controller object

void setup() {
  Serial.begin(9600); //Opens serial for debug
  frame[2][1] = 1; //This is for the cool LED screen we use for debugging
  matrix.renderBitmap(frame, 8, 12); //Renders the screen
  motor.setSpeed(255); //Sets motor speeds to max
  //Motor speeds for the motor controller are given between 0-255. 
  IrReceiver.begin(IRrecPin, true); 
  matrix.begin(); //Starts the display once setup is done
}

void loop() {
    if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data

      //the values we are comparing to are recieved from the code above when I typed buttons on the remoet
      //Each button has it sown HEX value that we compare to.

      if(IrReceiver.decodedIRData.decodedRawData == 0xE718FF00)   
      {
        Serial.println("FORWARD");
        driveForward();
      }
      if(IrReceiver.decodedIRData.decodedRawData == 0xAD52FF00)
      {
        Serial.println("BACKWARD");
        driveBackward();
      }
      if(IrReceiver.decodedIRData.decodedRawData == 0xF708FF00)
      {
        Serial.println("LEFT");
        driveLeft();
      }
      if(IrReceiver.decodedIRData.decodedRawData == 0xA55AFF00)
      {
        Serial.println("RIGHT");
        driveRight();
      }
      if(IrReceiver.decodedIRData.decodedRawData == 0xE31CFF00)
      {
        Serial.println("STOP");
        driveStop();
      }
      IrReceiver.resume(); // Enable receiving of the next value
      //delay(10);
    }

  

}


void driveLeft(){
  motor.setSpeed(100); //Slowing down the motors
  motor.backwardB();
  motor.forwardA() ;
}

void driveRight(){
  motor.setSpeed(100); //Slowing down the motors
  motor.backwardA();
  motor.forwardB() ;
}
void driveForward(){
  motor.setSpeed(255);
  motor.forward();
}
void driveBackward(){
  motor.setSpeed(255);
  motor.backward();
}
void driveStop()
{
  motor.stop();
}


