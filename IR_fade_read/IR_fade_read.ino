
//Problems. 
// 1- The IR Sensor keeps sending High signal, or 0 when I use a remote.



//IR LED fades on PIN 9
//IR sensor reads the signal
//bar graph shows intensity.

//FADE IR LED
int IRled = 9;           // the pin that the LED is attached to
int IRbrightness = 0;    // how bright the LED is
int IRfadeAmount = 5;    // how many points to fade the LED by
//BAR
const int analogPin = A0;   // the pin that the potentiometer is attached to
const int ledCount = 3;    // the number of LEDs in the bar graph

int ledPins[] = { 
  11,12,13 };   // an array of pin numbers to which LEDs are attached

int filter=0;

// the setup routine runs once when you press reset:
void setup()  { 
  //IR LED
  // declare pin 9 to be an output:
  pinMode(IRled, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //BAR
   // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  }
} 
// the loop routine runs over and over again forever:
void loop()  { 
  //IR LED
  
  // set the brightness of pin 9:
  analogWrite(IRled, IRbrightness);    
  // change the brightness for next time through the loop:
  IRbrightness = IRbrightness + IRfadeAmount;
  // reverse the direction of the fading at the ends of the fade: 
  if (IRbrightness == 0 || IRbrightness == 255) {
    IRfadeAmount = -IRfadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);   

  // read the input on analog pin 0:
  int IRsensorValue = analogRead(analogPin);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float IRvoltage = IRsensorValue * (5.0 / 1023.0);
  // print out the value you read:
  if (filter == 10) {
    Serial.println(IRvoltage);
    filter=0;
  }else{
    filter=filter+1;
  }
  //BAR
  // map the result to a range from 0 to the number of LEDs:
  int ledLevel = map(IRsensorValue, 0, 1023, 0, ledCount);

  // loop over the LED array:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    } 
    // turn off all pins higher than the ledLevel:
    else {
      digitalWrite(ledPins[thisLed], LOW); 
    }
  }
}

