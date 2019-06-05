// ========================================================================
// File:    OTAController.cpp
// Date:    05-06-2019
// By:      Mark Meerlo
// ========================================================================
#include <Arduino.h>
#include <HTTPUpdate.h>
#include "Header/OTAController.h"

//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
OTAController::OTAController () {/*No implementation */ }
OTAController::~OTAController () {/*No implementation */ }

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************

void OTAController::updateOTA(const char* URL)
{
    Serial.println("OTA Updater invoked!");
    Serial.println(ca_cert);

    //TODO: Implement URL not empty check
    if (1 == 0) {
        Serial.println("Invalid URL format... aborted OTA Update.");
        return; 
    }

    // Prepare config struct
    esp_http_client_config_t m_config = 
  {
        .url = URL,
        .host = nullptr,
        .port = 0,
        .username = nullptr,
        .password = nullptr,
        .auth_type = esp_http_client_auth_type_t::HTTP_AUTH_TYPE_BASIC,
        .path = nullptr,
        .query = nullptr,
        .cert_pem = ca_cert,
  };

  // Attempt OTA update
  Serial.println("Attempting OTA Update... [Might take a few seconds]");
  espStatus res = esp_https_ota(&m_config);

  switch (res) {
      case ESP_FAIL :
        Serial.println("OTA Update failed... Aborted.");
        break;
    case ESP_OK :
        Serial.println("OTA Update succeeded! Rebooting in two seconds.");
        delay(2000);
        esp_restart();
        break;
    default :
        Serial.println("Unknown ESP code. Aborted...");
        break;
  };



}