/*
 * RelayNode.h
 *
 *  RelayNode is a HomieNode
 *  nodeID: relay
 *  $type: switch
 *  $property: state, settable with "ON" and "OFF"
 *
 *      Author: David
 */

#pragma once

#include <HomieNode.hpp>

class RelayNode: public HomieNode
{
   public:
      RelayNode();
      void init();
      void set(bool on, const String& source);
      void toggle();
      bool handler(const HomieRange &range, const String &value);
      virtual ~RelayNode();

   private:
      static constexpr uint8_t pin = 12;
};

