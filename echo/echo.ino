//modified from http://nakubu.com/post/25

//Read 5 seconds when red button
//replay when black button


// set pin numbers:
  const int buttonPin = 7;     // the number of the pushbutton pin
  const int ledPin =  11;      // the number of the LED pin
  
  // Variables will change:
  int buttonState;             // the current reading from the input pin
  int lastButtonState = LOW;   // the previous reading from the input pin
  
  // the following variables are long's because the time, measured in miliseconds,
  // will quickly become a bigger number than can be stored in an int.
  long lastDebounceTime = 0;  // the last time the output pin was toggled
  long debounceDelay = 50;    // the debounce time; increase if the output flickers
  int hold = 0; //keeps state of the button
  int beeps = 0; //number of button pushes
  int start = 0; // are we starting a new pattern?
  long startTime = 0;
  long duration = 3000; //duration of the recording
  long delayArray[200]; //no dynamic arrays! randomly large number. shut up.
  
  void setup() {
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
  }
  
  void loop() {
    // read the state of the switch into a local variable:
    int reading = digitalRead(buttonPin);
  
    // check to see if you just pressed the button 
    // (i.e. the input went from LOW to HIGH),  and you've waited 
    // long enough since the last press to ignore any noise:  
  
    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    } 
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:
      buttonState = reading;
      if (reading == LOW){
         hold = 0; //otherwise, we're still holding the button!
      }   
      if(hold == 0){ //if the button was let go
        if( (start == 1))
        {
          long time = millis();
          if  ((time - startTime) < duration ){
            if (buttonState == HIGH){
                 beeps++;
                 delayArray[beeps] = time;
                 reading = LOW;
                 hold = 1;
              }
          }
          else{
            
            //replay the signals on the led
            int i = 0;
            long lastTime = delayArray[0];
            long now, next, span;
            digitalWrite(ledPin, HIGH);
            delay(150);
            digitalWrite(ledPin, LOW);
            for(i=1; i<=beeps; ++i){
              next = delayArray[i];
              now = millis();
              span = now + (next-lastTime);
              while( (span - now) > 0){
                now = millis();
              }
              digitalWrite(ledPin, HIGH);
              delay(150);
              digitalWrite(ledPin, LOW);
              lastTime = next;
            }
            start = 0;
          beeps = 0;
          }
        }
        else{
          beeps = 0;
          if(buttonState == HIGH){
             start = 1;
             startTime = millis();
             delayArray[0] = startTime;
             reading = LOW;
             hold = 1;
          }
        }
      }
    }
    
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState = reading;
  }

