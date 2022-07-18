// Tutorial 1a1. On-off

// Main parts: Adafruit Metro Mini, momentary switch, capacitor, LED,
// resistor

// Variables that remain constant
const byte pinSwitch = 8; // Digital input pin from momentary switch
const byte pinLED = 3; // LED pin number

// Variables that can change
byte LEDstate = LOW; // Tracks if the LED is on/off, off (= LOW) at start
byte lastSwitchState = HIGH; // Tracks the last switch state, open (= HIGH) at start

void setup ()
{
  // Serial printing only necessary to understand the switch transitions
  // when pressed and released; you will see that a button press causes
  // two events, not just one
  Serial.begin (115200);

  // Initialise momentary switch pin with an internal pull-up resistor
  // so that the momentary switch is read as open (= HIGH) at start
  pinMode (pinSwitch, INPUT_PULLUP);

  // Initialise Metro Mini's digital pin specified above
  pinMode(pinLED, OUTPUT);
}

void loop ()
{
  // The momentary switch is hardware debounced with a 1uF capacitor; no
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
      // Here, you can do something on pressing the button
      Serial.println ("Switch button pressed");
    }

    else
    {
      // Here, you can do something on releasing the button. Instead of
      // something useful, we only toggle an LED on and off. Upon release
      // of the button, it is toggled on or off. To see it clearly, hold
      // the button down for a while before releasing it
      Serial.println ("Switch button released");

      // Invert the current state of the LED
      LEDstate = !LEDstate;

      // And switch the LED on or off
      digitalWrite(pinLED, LEDstate);
    }
    // Last, store the current switch state for the next time around
    lastSwitchState =  switchState;
  }
}
