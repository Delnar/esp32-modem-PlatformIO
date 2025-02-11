#pragma once

#include <Arduino.h>

#undef R_OK
#define R_OK 0
#define R_CONNECT 1
#define R_RING 2
#define R_NOCARRIER 3
#define R_ERROR 4
#define R_NONE 5
#define R_NODIALTONE 6
#define R_BUSY 7
#define R_NOANSWER 8

extern const int bauds[];
extern const int baud_option_count;
extern String resultCodes[];


void sendResult(int resultCode);
void sendString(String msg);
void setBaudRate(int inSpeed);
