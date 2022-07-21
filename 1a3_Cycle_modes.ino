// Tutorial 1a3. Cycle modes

// Main parts: Adafruit Metro Mini, momentary switch, capacitor, LEDs,
// resistors

// Variables that remain constant
const byte pinSwitch = 8; // Digital input pin from momentary switch
const byte pinsLeds[] = {3, 4, 5, 6}; // Array to store the LED pin numbers
const size_t LEDcount = sizeof pinsLeds / sizeof pinsLeds[0]; // Find out and store size of the array

// Variables that can change
byte lastSwitchState = HIGH; // Tracks the last switch state, open (= HIGH) at start

void setup ()
{
  // Serial printing only necessary to understand the cycling through the
  // switch case cascade
  Serial.begin (115200);

  // Initialise momentary switch pin with an internal pull-up resistor
  // so that the momentary switch is read as open (= HIGH) at start
  pinMode (pinSwitch, INPUT_PULLUP);

  // Loop through the array with the LED pin numbers
  for (int i = 0; i < LEDcount; i++)
  {
    // Initialise Metro Mini's digital pins specified above
    pinMode(pinsLeds[i], OUTPUT);
  }
}

void loop ()
{
  // Counter that updates every loop() iteration. The keyword static
  // means the variable is not created and destroyed with every function
  // call, but lives on and so retains its value between function calls
  static byte cycleCounter = 0;

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
      // If it was, increment the counter
      cycleCounter++;

      // Loop through the array with the LED pin numbers
      for (int i = 0; i < LEDcount; i++)
      {
        // And switch all LEDs off
        digitalWrite(pinsLeds[i], LOW);
      }
      // Then switch on only the LED that matches the counter
      digitalWrite(pinsLeds[cycleCounter - 1], HIGH);
    }
    // Last, store the current switch state for the next time around
    lastSwitchState =  switchState;
  }

  // Depending on the value of cycleCounter, each case in a switch case
  // statement allows for convenient setting of variables, flags or the
  // calling of functions that do something. If a case matches, code
  // execution continues behind the switch cascade
  switch (cycleCounter)
  {
    case 1:
      Serial.print("Blue LED on; cycleCounter on "); Serial.println(cycleCounter);
      break;
    case 2:
      Serial.print("Green LED on; cycleCounter on "); Serial.println(cycleCounter);
      break;
    case 3:
      Serial.print("Yellow LED on; cycleCounter on "); Serial.println(cycleCounter);
      break;
    case 4:
      Serial.print("Red LED on; cycleCounter on "); Serial.println(cycleCounter);
      break;
  }
  
  // If the cycleCounter reached the highest value
  if (cycleCounter > LEDcount)
  {
    // reset it to 0, so the cycle can start again
    cycleCounter = 0;
  }
}
