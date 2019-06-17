#ifndef MQTTCONTROLLER_H
#define MQTTCONRTOLLER_H

// *** Forward Declarations ***********************
class WiFiClientSecure;
class PubSubClient;
class RelayController;

// *** Dependencies *******************************
#include <Arduino.h>
#include <WiFi.h>

// *** Command Set Enumeration*********************
enum CommandSet
{
    PROJECT,
    IDENTIFIER,
    COMMAND
};

class MqttController {

public:
//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
MqttController                                  ();
~MqttController                                 ();

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void callback                                   (char* topic, 
                                                 byte* payload, 
                                                 unsigned int length);
void loop                                       ();

private:
//* ***********************************************
//          PRIVATE METHODS
//* ***********************************************
bool connect                                    ();
bool publish                                    (const char* topic, 
                                                 const char* payload);
WiFiClientSecure& getClient()                    { return *m_client; }
void wifiEvent                                  (WiFiEvent_t event);

//* ***********************************************
//          PRIVATE ATTRIBUTES
//* ***********************************************
// Connection variables
const char*                             m_NET_SSID      = "SSID";
const char*                             m_NET_PASS      = "PASSWORD";
const char*                             m_NET_ROOT_CA;
const char*                             m_MQTT_SERVER   = "95.217.9.30";
const int                               m_MQTT_PORT     = 8883;
const char*                             m_MQTT_USER     = "MCBC";           // Museum Collectie Brands Controller
const char*                             m_MQTT_PASS     = "h48dPdnK6aGM";
const char*                             m_CA_CERT       = "-----BEGIN CERTIFICATE-----\n" \
"MIIDvzCCAqegAwIBAgIUBRpUNsJT3YVa1atqNVGuYPGW2tkwDQYJKoZIhvcNAQEL\n" \
"BQAwbzELMAkGA1UEBhMCTkwxEzARBgNVBAgMClNvbWUtU3RhdGUxEDAOBgNVBAoM\n" \
"B0VtaXQgSVQxGDAWBgNVBAMMD2xhcmF2ZWwtYmFja2VuZDEfMB0GCSqGSIb3DQEJ\n" \
"ARYQaW5mb0BlbWl0LWl0LmNvbTAeFw0xOTA2MDYxMjAyMDNaFw0yNDA2MDUxMjAy\n" \
"MDNaMG8xCzAJBgNVBAYTAk5MMRMwEQYDVQQIDApTb21lLVN0YXRlMRAwDgYDVQQK\n" \
"DAdFbWl0IElUMRgwFgYDVQQDDA9sYXJhdmVsLWJhY2tlbmQxHzAdBgkqhkiG9w0B\n" \
"CQEWEGluZm9AZW1pdC1pdC5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n" \
"AoIBAQC+vYBOGxKEZaQKViHzxmwU4tyRA1TXnZlOM1oqakfvVFih5jT+2nGaKtvU\n" \
"31jwhjWj8OciCsY6+3lF+hdZxYlNKIDJSfv3beziIkJTKWMzYaHCczxpowrby3hE\n" \
"QNfFy/gcKzD2niFWE7qW1WjOsT4VpxLF+GK6WUISXHgxZ81Dv2dS16HP5oP6eaaF\n" \
"uJ3gkNiKz0xKneMQSTrkOEsG2/5VfpQk/8dW+KfUuFEYD5L5NNsxicaXXUbP2UEH\n" \
"7+ICRjhnJSoZJHvA50g0glUGZnG3wsFNOC+gYghlGZe1Fd9mUJT2g/RG7thWe6nW\n" \
"/5v3EKdGC54ReA2XryPCog10FF3fAgMBAAGjUzBRMB0GA1UdDgQWBBToqQidzeih\n" \
"/nAOEo4d2Jxoc64B+DAfBgNVHSMEGDAWgBToqQidzeih/nAOEo4d2Jxoc64B+DAP\n" \
"BgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQAfKb0cIfQ96J+J+N9s\n" \
"2nzv6zfgCgp4+5CvwaJvIoHVB4mkn0cGBl4I0LhATN4XQIS2Lmovu0pfDpCkVIgs\n" \
"q6mvSwKturZR4vY7B4R28/2i3Yn3vj6oIoVOh3fwTOsHSkyLWK49CZrqYSdCAUVi\n" \
"ch8oSXjdVmKgG5QJuZVm8E9Nz/ReLSW3lfR+cew/SzskSPnVqpQ/bvtvbVHpoDtq\n" \
"b2zPb7HxfP21P+YOIHHfJuwvQUthic3CHAkYa/EAxXzL1yg9G3QOB5WntmEwm8hB\n" \
"ZFMB6HGBdS/cmaFuC9pfwB6UFZBjjgnGZsgxjShbi6/rWGfyu0U9/6H8B5UvvJ6B\n" \
"J/ly\n" \
"-----END CERTIFICATE-----";

// Variables to keep track of elapsed time without blocking the core
unsigned long                           m_startMillis = millis();
unsigned long                           m_currentMillis;
const unsigned long                     m_delay = 5000;

// Print identifier
const char*                             m_PCB_ID;

// Objects
WiFiClientSecure*                       m_client;
PubSubClient*                           m_mqtt;
RelayController*                        m_relayCtrl;

};
#endif