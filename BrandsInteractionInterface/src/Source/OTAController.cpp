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

void OTAController::updateOTA(const char* path)
{
    Serial.println("OTA Updater invoked!");

    if (strlen(path) == 0) {
        Serial.println("Invalid path format... aborted OTA Update.");
        return; 
    }
    // Construct URL with domain and path
    char buffer[strlen(path) + strlen(domain) + 12];
    sprintf(buffer, "https://%s%s.bin", domain, path);
    const char* URL = buffer;
    Serial.print("Fetching Firmware from: ");
    Serial.println(URL);

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