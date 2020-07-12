/*
 * RelayNode.cpp
 *
 *      Author: David
 */

#include <Homie.hpp>
#include "RelayNode.h"

RelayNode::RelayNode()
    : HomieNode("relay", "switch")
{
}

void RelayNode::init()
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW); // Relay off.

  std::function<bool(const HomieRange&, const String&)> f = std::bind(&RelayNode::handler, this,
      std::placeholders::_1, std::placeholders::_2);

  advertise("state").settable(f);
}

void RelayNode::set(bool on, const String& source)
{
  digitalWrite(pin, on);
  setProperty("state").send(on ? "ON" : "OFF");
  Homie.getLogger() << "Relay is " << (on ? "on " : "off ") << source << endl;
}

void RelayNode::toggle()
{
  bool on = digitalRead(pin) == HIGH;
  set(!on, "(button)");
}

// Homie handler for Sonoff switch over MQTT
bool RelayNode::handler(const HomieRange &range, const String &value)
{
  if (value != "ON" && value != "OFF") return false;

  bool on = (value == "ON");
  set(on, "(MQTT)");
  return true;
}

RelayNode::~RelayNode()
{
}

