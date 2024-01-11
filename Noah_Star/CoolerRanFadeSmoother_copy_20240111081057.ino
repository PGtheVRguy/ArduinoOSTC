

#include <AsyncDelay.h>

int pins[] =   {1, 3, 5, 6, 9, 10, 11}; //pins to write to
double bright[] = {0, 0, 0, 0, 0, 0}; //brightness levels of pins (make sure its the same size as pins[] as they directly correlate)
double targetBright[] = {0,0,0,0,0,0,0}; //the target brightness of pins
double maxBright = 75;



AsyncDelay delay_ranBright; //These delays are part of a library I found to give me delays that dont pause ALL my code
AsyncDelay delay_lowBright;
AsyncDelay delay_start;

/*
Runs a sorta "starry" ambient effect 
It randomly chooses a pin, sets a "target brightness" for its true "brightness" to follow.
All pins, true brightness, and target brightness are stored in 3 arrays.
*/
void setup() {
  randomSeed(analogRead(0)); //Randomizes the seed
  Serial.begin(9600); //Sets up a serial bus thingy for debugging (I was having many problems)
  setUpPins(); //Runs function "setUpPins" that loops through all pins to be an "OUTPUT" and brightens them. Half utility, half debug.
  delay_ranBright.start(1000, AsyncDelay::MILLIS); //Sets up timers to randomly choose LED
  delay_lowBright.start(0, AsyncDelay::MILLIS); //Sets up how fast the LED dim code run (Prefer 0)
  delay_start.start(1000, AsyncDelay::MILLIS); //A delay on how long it takes the main code to run (Also mainly debug so I can see if all my lights are running)


}

void loop() {
  
  
  if((delay_lowBright.isExpired()) && (delay_start.isExpired())) //Checks if both timer to start and time to dim is done
  {
    for(int i = 0; i < 8; i++)
    { //i is the pin in the array we write to.
      targetBright[i] = targetBright[i]- 0.4; //subtracts target
      targetBright[i] = constrain(targetBright[i], 0, 255); //constrains it


      bright[i] = lerp(bright[i], targetBright[i], 0.05); //cool linear interpretation of bright->target by 5%
      analogWrite(pins[i], bright[i]); //sets brightness
      

      
    }
    delay_lowBright.repeat(); //Resets timer to dim
  }

  Serial.println(bright[3]); //debug

  if(delay_ranBright.isExpired()) //Code for randomly choosing an LED to brighten
  {
    randomBright();
    
  }
}


void randomBright()
{
  
  
  int chooseLight = random(0,6); 
  targetBright[chooseLight] = maxBright; //Sets our target brightness to the max
  delay_ranBright.repeat();
}

float lerp(float a, float b, float f) //Lerp code I stole online
{
    return (a * (1.0 - f)) + (b * f);
}

void setUpPins() { 
    int LEDPin = 0;
    while(LEDPin < 14) //Loops through all pins to make them outputs and on
    {
      pinMode(LEDPin, OUTPUT); 
      analogWrite(LEDPin, maxBright);
      LEDPin++; 

    }
}