/*
 * Thermostat.h
 *
 *  Created on: 15 Oct 2017
 *      Author: David
 */

#pragma once

#include <HomieNode.hpp>
#include <Bounce2.h>

class ThermostatNode: public HomieNode
{
  public:
    ThermostatNode();
    void init();   // Called in setup()
    void update(); // Called in loopHandler()
    virtual ~ThermostatNode();

  private:
    static constexpr uint8_t pin = 14;
    static constexpr uint8_t interval = 100; // debounce interval in ms

    Bounce debouncer;
};

