// Tutorial 1a4. Short or long press

// Main parts: Adafruit Metro Mini, momentary switch, capacitor, LEDs
// resistors

// Variables that remain constant
const byte pinSwitch = 8; // Digital input pin from momentary switch
const byte pinLED1 = 3; // LED pin number
const byte pinLED2 = 6;
const int timeShortPress = 200; // Maximum duration of short button press
const int timeLongPress = 350; // Minimum duration of long button press

// Variables that can change
byte LED1state = LOW; // Tracks if the LED is on/off, off (= LOW) at start
byte LED2state = LOW;
byte lastSwitchState = HIGH; // Tracks the last switch state, open (= HIGH) at start
unsigned long timePressed  = 0; // Timestamp when button is pressed
unsigned long timeReleased = 0; // Timestamp when button is released

void setup ()
{
  // Serial printing only necessary to understand the switch transitions
  // when pressed and released; you will see that a button press causes
  // two events, not just one
  Serial.begin (115200);

  // Initialise momentary switch pin with an internal pull-up resistor
  // so that the momentary switch is read as open (= HIGH) at start
  pinMode (pinSwitch, INPUT_PULLUP);

  // Initialise Metro Mini's digital pins specified above
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
}

void loop ()
{
  // The momentary switch is hardware debounced with a 0.1uF capacitor; no
  // debouncing code is necessary. See http://www.gammon.com.au/switches
  // Read the voltage from the momentary switch pin to see if something
  // has changed (was the button pressed or released?)
  byte switchState = digitalRead (pinSwitch);

  // Has the momentary switch state changed since the last time it was
  // checked?
  if (switchState != lastSwitchState)
  {
    // Then, test if the switch was closed (button pressed)
    if (switchState == LOW)
    {
      // And we take a timestamp of when that happened
      timePressed = millis();

      // Just to see what happened
      Serial.println ("Switch button pressed");
    }

    // Otherwise, the switch must have been open (button released)
    else
    {
      // And we take a timestamp of when that happened
      timeReleased = millis();

      // Just to see what happened
      Serial.println ("Switch button released");

      // How long did it take between pressing and releasing?
      long pressDuration = timeReleased - timePressed;

      // If it took less time than the short press duration
      if (pressDuration < timeShortPress )
      {
        // Here, you can do something on releasing the button. Instead of
        // something useful, we only toggle an LED on and off. Upon release
        // of the button, it is toggled on or off
        Serial.print ("Short press milliseconds "); Serial.println (pressDuration);

        // Invert the current state of the LED
        LED1state = !LED1state;

        // And switch the LED on or off
        digitalWrite(pinLED1, LED1state);
      }

      else if (pressDuration > timeLongPress )
      {
        // Here, you can do something on releasing the button. Instead of
        // something useful, we only toggle an LED on and off. Upon release
        // of the button, it is toggled on or off
        Serial.print ("Long press milliseconds "); Serial.println (pressDuration);

        // Invert the current state of LED two
        LED2state = !LED2state;

        // And switch the LED on or off
        digitalWrite(pinLED2, LED2state);
      }
    }
    // Last, store the current switch state for the next time around
    lastSwitchState =  switchState;
  }
}
