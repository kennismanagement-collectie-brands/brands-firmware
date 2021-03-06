// ========================================================================
// File:    main.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================

#include <Arduino.h>
#include "Header/Core.h"
#include "Header/MqttController.h"

Core* core; 

/*
 *  The default setup method gets executed once, when the ESP32 boots
 */
void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("Executing setup...");
  pinMode(LED_BUILTIN, OUTPUT);

  delay(100);
  core = new Core();
}

/*
 *  The default loop method gets called after the setup method and loops consecutively
 */
void loop() {
  core->loop();
}

//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
Core::Core ()
{
  Serial.println("Initialized Serial monitor!");
  m_mqtt = new MqttController();
}

Core::~Core() { /* Not implemented */ }

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void Core::setup () { /* Not implemented */ }

void Core::loop ()
{
  // Loop the MQTT logic which handles internet connection and recieving of messages
  //Serial.printf("Heap Usage: %d/%d (%d%%)\n", (ESP.getHeapSize() - ESP.getFreeHeap()), ESP.getHeapSize()
  //  , (int)round(100.0 - (((float)ESP.getFreeHeap() / (float)ESP.getHeapSize()) * 100.0)));
  m_mqtt->loop();
}