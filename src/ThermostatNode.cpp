/*
 * ThermostatNode.cpp
 *
 *  Created on: 15 Oct 2017
 *      Author: David
 */

#include <Homie.hpp>
#include "ThermostatNode.h"

ThermostatNode::ThermostatNode()
    : HomieNode("thermostat", "sensor")
{
}

void ThermostatNode::init()
{
  debouncer.attach(pin, INPUT_PULLUP);
  debouncer.interval(interval); // interval in ms
  advertise("state");
}

void ThermostatNode::update()
{
  if (debouncer.update())
  {
    setProperty("state").send(debouncer.read() ? "OPEN" : "CLOSED"); // A low at the pin is 'on'
    Homie.getLogger() << "Thermostat is " << (debouncer.read() ? "OPEN" : "CLOSED") << endl;
  }
}

ThermostatNode::~ThermostatNode()
{
}

