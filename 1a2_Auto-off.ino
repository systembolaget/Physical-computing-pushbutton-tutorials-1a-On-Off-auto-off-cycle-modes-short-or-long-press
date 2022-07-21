// Tutorial 1a2. Auto-off

// Main parts: Adafruit Metro Mini, momentary switch, capacitor, LED,
// resistor

// Variables that remain constant
const byte pinSwitch = 8; // Digital input pin from momentary switch
const byte pinLED = 3; // LED pin number
int onInterval = 4000; // LED on-time until auto-off

void setup()
{
  // Initialise momentary switch pin with an internal pull-up resistor
  // so that the momentary switch is read as open (= HIGH) at start
  pinMode (pinSwitch, INPUT_PULLUP);

  // Initialise Metro Mini's digital pin specified above
  pinMode(pinLED, OUTPUT);
}

void loop()
{
  // Timestamp that updates every loop() iteration. The keyword static
  // means the variable is not created and destroyed with every function
  // call, but lives on and so retains its value between function calls
  static unsigned long timeNow = 0;

  // The momentary switch is hardware debounced with a 0.1uF capacitor; no
  // debouncing code is necessary. See http://www.gammon.com.au/switches
  // Read the voltage from the momentary switch pin to see if something
  // has changed (was the button pressed or released?)
  byte switchState = digitalRead (pinSwitch);

  // If the button was not pressed, meaning if the momentary switch is
  // read as open ( = HIGH)
  if (switchState == HIGH)
  {
    // Then check if it is already time to turn off the LED. We subtract
    // the timestamp taken every loop() iteration from the current time,
    // taken with millis(), and then compare to the duration onInterval.
    // When it is equal or larger
    if (millis() - timeNow >= onInterval)

      // We turn the LED off
      digitalWrite(pinLED, LOW);
  }

  // Otherwise, if switchState was not HIGH, it must be LOW, and that
  // means that it was closed and button was pressed
  else
  {
    // And therefore, the LED is turned on
    digitalWrite(pinLED, HIGH);

    // And we take a timestamp of when that happened
    timeNow = millis();
  }
}
