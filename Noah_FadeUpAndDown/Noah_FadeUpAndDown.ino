

//Initialize some basic variables. 
int LEDFadePin = 0;
bool goDown = true;
//Constants 
int pins[] = {1, 3, 5, 6, 9, 10, 11};
int maxLEDPin = 11; 
double timeDelay = 0;

void setup() { //Setup function
  Serial.begin(9600); // open the serial port at 9600 bps: (debug)

  setUpPins(); //This is a custom function, it just allows us to have more portable custom code. Plz check bottom to view the code
}
void loop() { //Loop function
  //Following is a loop that runs once every cycle, to slowly turn off one row of leds
  timeDelay = -1;
  if(goDown == true)
    {
    LEDFadePin++;
    for(int i = 0; i < 15; i++)
    {
      if(pins[i] == LEDFadePin)
      {
        //This area of code makes it so we can skip this delay if our pin is not in the pins[] array
        timeDelay = 100;
      }
    }
    digitalWrite(LEDFadePin, LOW);
  }
  if(goDown == false)
    {
    LEDFadePin--;
    for(int i = 0; i < 15; i++)
    {
      if(pins[i] == LEDFadePin)
      {
        
        timeDelay = 100;
      }
    }
    digitalWrite(LEDFadePin, HIGH);
  }
    Serial.println(timeDelay); //debug
    Serial.println(LEDFadePin);
  if(timeDelay > 0) //Just in case delay(0); delays even the most minor of amounts
  {
    delay(timeDelay);
  }
  

  if(LEDFadePin > 20) //if we should go up or down depending on how many lights are on/off
  {
    goDown = false;
  }
  if(LEDFadePin < 0)
  {
    goDown = true;
  }
}
void setUpPins() {  //sets up all of our pins to output and on
    int LEDPin = 0;
    while(LEDPin < 14) 
    {
      pinMode(LEDPin, OUTPUT); 
      digitalWrite(LEDPin, HIGH); 
      LEDPin++; 

    }
}

