//-------------------------------------------------------------------------------------------------
// Built for Sonoff "Switch" based on Homie sample sketch
// https://www.itead.cc/sonoff-wifi-wireless-switch.html
// https://github.com/marvinroger/homie-esp8266/blob/develop/examples/IteadSonoffButton/IteadSonoffButton.ino
//-------------------------------------------------------------------------------------------------
#include <Homie.h>
#include "RelayNode.h"
#include "ThermostatNode.h"

//-------------------------------------------------------------------------------------------------
// Hardware specs
const uint8_t PIN_BUTTON = 0;
const uint8_t PIN_LED = 13;

// Button state
uint32_t buttonDownTime = 0;
uint8_t lastButtonState = HIGH;
bool buttonPressHandled = 0;

RelayNode relay;            // On GPIO 12
ThermostatNode thermostat;  // On GPIO 14.

//-------------------------------------------------------------------------------------------------
// Homie loop Handler : Checks button state to have hardware button to set relay state (on/off)
void loopHandler()
{
  uint8_t buttonState = digitalRead(PIN_BUTTON);

  if (buttonState != lastButtonState)
  {
    if (buttonState == LOW)
    {
      buttonDownTime = millis();
      buttonPressHandled = false;
    }
    else
    {
      uint32_t dt = millis() - buttonDownTime;
      if (dt >= 90 && dt <= 900 && buttonPressHandled == false)
      {
        relay.toggle();
        buttonPressHandled = true;
      }
    }

    lastButtonState = buttonState;
  }

  thermostat.update();
}

//-------------------------------------------------------------------------------------------------
// Arduino Setup Handler
void setup()
{
  Serial.begin(115200); // Required to enable serial output
  Serial << endl << endl;

  Homie_setFirmware("SonoffThermostat", "0.18");
  Homie.setLedPin(PIN_LED, LOW).setResetTrigger(PIN_BUTTON, LOW, 5000);
  Homie.setLoopFunction(loopHandler);

  relay.init();
  thermostat.init();

  Homie.setup();
}

//-------------------------------------------------------------------------------------------------
// Arduino Loop Handler
void loop()
{
  Homie.loop();
}
