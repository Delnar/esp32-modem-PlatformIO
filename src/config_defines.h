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

