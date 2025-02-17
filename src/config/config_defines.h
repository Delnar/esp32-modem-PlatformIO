#pragma once

#include <Arduino.h>

#define IP_TYPE_ADDRESS 97   // for future use
#define STATIC_IP_ADDRESS 98 // length 4, for future use
#define STATIC_GW       102  // length 4, for future use
#define STATIC_DNS      106  // length 4, for future use
#define STATIC_MASK     110  // length 4, for future use

#define LISTEN_PORT 6400   // Listen to this if not connected. Set to zero to disable.
#define RING_INTERVAL 3000 // How often to print RING when having a new incoming connection (ms)
#define MAX_CMD_LENGTH 256 // Maximum length for AT command

#define LED_TIME 15        // How many ms to keep LED on at activity
#define TX_BUF_SIZE 256    // Buffer where to read from serial before writing to TCP

// Telnet codes
#define DO 0xfd
#define WONT 0xfc
#define WILL 0xfb
#define DONT 0xfe

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;

#define SWITCH_PIN D3       // GPIO0 (programmind mode pin)
#define LED_PIN D5          // Status LED
#define DCD_PIN D6          // DCD Carrier Status
#define RTS_PIN D7         // RTS Request to Send, connect to host's CTS pin
#define CTS_PIN D4         // CTS Clear to Send, connect to host's RTS pin

#define VERSIONA 1
#define VERSIONB 2
#define VERSION_ADDRESS 0 // EEPROM address
#define VERSION_LEN 2	  // Length in bytes

#define SSID_ADDRESS 2
#define SSID_LEN 32
#define PASS_ADDRESS 34
#define PASS_LEN 63
#define BUSY_MSG_ADDRESS 700
#define BUSY_MSG_LEN 80

#define BAUD_ADDRESS 111
#define ECHO_ADDRESS 112
#define SERVER_PORT_ADDRESS 113 // 2 bytes
#define AUTO_ANSWER_ADDRESS 115 // 1 byte
#define TELNET_ADDRESS 116		// 1 byte
#define VERBOSE_ADDRESS 117
#define PET_TRANSLATE_ADDRESS 118
#define FLOW_CONTROL_ADDRESS 119
#define PIN_POLARITY_ADDRESS 120

#define DIAL0_ADDRESS 200
#define DIAL1_ADDRESS 250
#define DIAL2_ADDRESS 300
#define DIAL3_ADDRESS 350
#define DIAL4_ADDRESS 400
#define DIAL5_ADDRESS 450
#define DIAL6_ADDRESS 500
#define DIAL7_ADDRESS 550
#define DIAL8_ADDRESS 600
#define DIAL9_ADDRESS 650

#define LAST_ADDRESS 780
