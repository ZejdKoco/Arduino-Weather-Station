/*
 WiFiEsp example: WebClient

 This sketch connects to google website using an ESP8266 module to
 perform a simple web search.

 For more details see: http://yaab-arduino.blogspot.com/p/wifiesp-example-client.html
*/

#include "WiFiEsp.h"
#include "DHT.h"
#include <ArduinoJson.h>
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#define DHTPIN 10
#define DHTTYPE DHT11
#endif

const unsigned char PROGMEM bitmap01d[] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xf8, 0x0, 0x0, 
0x0, 0x0, 0x7, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 
0x7f, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xf8, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
 };
const unsigned char PROGMEM bitmap02d[] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xc0, 0x0, 0x0, 0x0, 0x0, 
0x3, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
 };

const unsigned char PROGMEM bitmap03d[] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
 };

 const unsigned char PROGMEM bitmap04d[] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xec, 
0x0, 0x0, 0x0, 0x0, 0x13, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x1, 0xff, 0xf8, 0x0, 0x0, 
0x0, 0x0, 0x1f, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 
0x7f, 0xff, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xf0, 
0x0, 0x0, 0x0, 0x0, 0x9f, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x1, 0xfe, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  
 };

 const unsigned char PROGMEM bitmap09d[] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x88, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 
0x80, 0x0, 0x0, 0x0, 0x3, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xfc, 0x0, 0x0, 
0x0, 0x0, 0x7, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0, 
0x3f, 0xff, 0x80, 0x0, 0x0, 0x0, 0xf, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xf8, 
0x0, 0x0, 0x0, 0x30, 0x7, 0xfc, 0x0, 0x0, 0x0, 0xe, 0x0, 0xfe, 0x0, 0x0, 0x0, 
0x47, 0x80, 0x0, 0x0, 0x0, 0x0, 0x39, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x30, 0x0, 
0x0, 0x0, 0x0, 0xf, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf8, 0x40, 0x0, 0x0, 0x0, 
0x0, 0xfe, 0x18, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x1, 0xcf, 0xc3, 
0xc0, 0x0, 0x0, 0x0, 0x70, 0xe1, 0xf8, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x7c, 0x0, 0x0, 
0x0, 0xf, 0x80, 0xf, 0x0, 0x0, 0x0, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  
 };

 const unsigned char PROGMEM bitmap10d[] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x3, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x1f, 0x0, 0x0, 0x0, 0x0, 0x1, 0x4, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x1, 0x8f, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x63, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x60, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x80, 0x0, 
0x0, 0x0, 0x0, 0x7, 0xe0, 0x80, 0x0, 0x0, 0x0, 0x13, 0xfc, 0x70, 0x0, 0x0, 0x0, 
0x3f, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x3, 0x9f, 0x8f, 0x80, 0x0, 0x0, 0x0, 0xe3, 0x83, 
0xe0, 0x0, 0x0, 0x0, 0x7c, 0x0, 0xf8, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x1c, 0x0, 0x0, 
0x0, 0x7, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
 };

 const unsigned char PROGMEM bitmap11d[] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xc0, 0x0, 0x0, 0x0, 0x0, 
0x1, 0xfe, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xfc, 0x0, 0x0, 0x0, 0x1, 0x1f, 0xff, 
0x80, 0x0, 0x0, 0x0, 0x1, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0x80, 0x0, 
0x0, 0x0, 0x7, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x1, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0, 
0x7f, 0xff, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xe0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 
0x80, 0x0, 0x0, 0x0, 0x0, 0x7, 0xc0, 0xf0, 0x0, 0x0, 0x0, 0x1, 0xe0, 0x38, 0x0, 
0x0, 0x0, 0x0, 0xf0, 0x1e, 0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0xbe, 0x0, 0x0, 0x0, 
0x1c, 0x3, 0x80, 0x0, 0x0, 0x0, 0x7, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x3, 0xf8, 0x72, 
0x0, 0x0, 0x0, 0x0, 0x6, 0x1, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 };

 const unsigned char PROGMEM bitmap13d[] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xd8, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 
0x80, 0x0, 0x0, 0x0, 0x23, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xfc, 0x0, 0x0, 
0x0, 0x0, 0x7, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0, 
0x3f, 0xff, 0x80, 0x0, 0x0, 0x0, 0xf, 0xff, 0xe0, 0x0, 0x0, 0x2, 0x0, 0x3f, 0xf8, 
0x0, 0x0, 0x2, 0x40, 0x7, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x2a, 0x0, 0x0, 0x0, 0x0, 0x2, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 
0x0, 0x0, 0x6, 0x23, 0x1, 0x80, 0x0, 0x0, 0x1, 0xeb, 0xc1, 0x68, 0x0, 0x0, 0x0, 
0xff, 0xff, 0xff, 0x80, 0x0, 0x0, 0x1, 0xd0, 0x6, 0x0, 0x0, 0x0, 0x1, 0x8c, 0x6, 
0x40, 0x0, 0x0, 0x1, 0xc9, 0xc1, 0x48, 0x0, 0x0, 0x0, 0x2, 0x0, 0x10, 0x0, 0x0, 
0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 };

 const unsigned char PROGMEM bitmap50d[] = {
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x60, 0x1, 0xf0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xe0, 0xf, 0xe0, 0x0, 0x0, 0x3f, 0xff, 0x1f, 
0xff, 0x80, 0x0, 0x1f, 0x1, 0xff, 0x1, 0xf0, 0x0, 0x4, 0x0, 0xe, 0x0, 0x4, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 0x0, 0xe0, 0x0, 0x0, 0x3, 0xff, 
0x1, 0xff, 0x80, 0x0, 0x7, 0xf1, 0xff, 0xf1, 0xfc, 0x0, 0x1, 0xc0, 0xf, 0xe0, 0x7, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x3f, 0x80, 0x3f, 0x80, 0x0, 0x1, 0xff, 0xfe, 0xff, 0xff, 0x0, 0x0, 0x7c, 0xf, 0xfe, 
0x7, 0xc0, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
 };




char ssid[] = "Rezidencija Skenderija";            // your network SSID (name)
char pass[] = "ajhzeddk";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
DHT dht(DHTPIN, DHTTYPE);
String prognoza="def";
String deksripcija="def";
String temperatura="def";
String vlaznost="def";
String datumVrijeme="def";
String kucnaTemp="def";
String kucnaVlaznost="def";
String kucnaFeels="def";
// Initialize the Ethernet client object
WiFiEspClient client;

void startConnection(){
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  printWifiStatus();
}

void makeHTTPrequest(){
    //Serial.println("Starting connection to server...");
    // if you get a connection, report back via serial
    if (client.connect("api.openweathermap.org", 80)) {
    //Serial.println("Connected to server");
    // Make a HTTP request
    client.print("GET /data/2.5/weather?q=Sarajevo&appid=31216b94e440cef83fbcc0d47e60d0e0&units=metric HTTP/1.1\r\n");
    client.print("Host: api.openweathermap.org\r\n");
    client.print("Connection: close\r\n\r\n");
  }
  else{
    return;
  }
}
void getStringHTTP(){
  char endOfHeaders[] = "\r\n\r\n";
  client.find(endOfHeaders);
  String httpString = "default";
  if(!client.available()){
    return;
  }
  while (client.available()) {
    char c = client.read();
    httpString+=c;
  }
  Serial.println(httpString);
  int pozicija;
  String Sdeskripcija;
  String Stemperatura;
  pozicija = httpString.indexOf("\"main");
  while(httpString[pozicija] != ','){
    Sdeskripcija+=httpString[pozicija];
    pozicija++;
  }
  pozicija = httpString.indexOf("\"temp");
  while(httpString[pozicija] != ','){
    Stemperatura+=httpString[pozicija];
    pozicija++;
  }
  Stemperatura+="°C";
  String trenutnaVlaznost;
  pozicija = httpString.indexOf("\"humidity");
  while(httpString[pozicija] != ','){
    trenutnaVlaznost+=httpString[pozicija];
    pozicija++;
  }
  trenutnaVlaznost+="%";
  String moreInfo;
  pozicija = httpString.indexOf("\"description");
  while(httpString[pozicija] != ','){
    moreInfo+=httpString[pozicija];
    pozicija++;
  }
  String bitmapa;
  pozicija = httpString.indexOf("\"icon");
  pozicija+=8;
  while(httpString[pozicija] != '"'){
    bitmapa+=httpString[pozicija];
    pozicija++;
  }
  Serial.println(Stemperatura);
  prognoza = Sdeskripcija;
  deksripcija = moreInfo;
  temperatura = Stemperatura;
  Serial.println(temperatura);
  vlaznost = trenutnaVlaznost;
}
void makeHTTPTimeRequest(){
  if (client.connect("convert-unix-time.com", 80)) {
    //Serial.println("Connected to server");
    // Make a HTTP request
    client.print("GET /api?timestamp=now HTTP/1.1\r\n");
    client.print("Host: convert-unix-time.com\r\n");
    client.print("Connection: close\r\n\r\n");
  }
  else{
    return;
  }
}
void getTime(){
  char endOfHeaders[] = "\r\n\r\n";
  client.find(endOfHeaders);
  String httpString;
  if(!client.available()){
    makeHTTPTimeRequest();
    delay(2000);
  }
  while (client.available()) {
    char c = client.read();
    httpString+=c;
  }
  String datum;
  int pozicija = 13; 
  while(httpString[pozicija] != ','){
    datum+=httpString[pozicija];
    pozicija++;
  }
  datumVrijeme = datum;
  
}
void ispisiTemperaturuSobe(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);
  kucnaTemp = "Room temperature: " + String(t) + "°C";
  kucnaVlaznost = "Room humidity: " + String(h) + "%";
  kucnaFeels = "Room feels like: " + String(hic);
  
}
void setup()
{
  // initialize serial for debugging
  Serial.begin(115200);
  dht.begin();
  // initialize serial for ESP module
  startConnection();
  Serial.println();
}
void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them
  
  makeHTTPrequest();
  getStringHTTP();
  makeHTTPTimeRequest();
  getTime();
  //ispisiTemperaturuSobe();

  Serial.println(prognoza);
  Serial.println(deksripcija);
  Serial.println(temperatura);
  Serial.println(vlaznost);
  Serial.println(datumVrijeme);
  Serial.println(kucnaTemp);
  Serial.println(kucnaVlaznost);
  Serial.println(kucnaFeels);
  if(status != WL_CONNECTED){
    Serial.println("Pukla konekcija");
    startConnection();
  }
  Serial.println();
  delay(25000);
  delay(4000);
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
