#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino.h>


#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int TXPin = 4, RXPin = 3;
static const uint32_t GPSBaud = 9600;

RF24 radio(7, 8);

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

int LED = 5;//usign a led as an indicator

void toString();
void Coordinates();

volatile boolean ledState = false;

String Latitude,Longitude;

//structure to be sent over NRF24 module to the gateway
struct coordinates{
  char Lat[10] = " "; //required characters for lat and lon is 12, but in our case(region) 8 chars are far enough to determine a specific location 
  char Lon[10] = " ";
};

struct coordinates Coord;

const byte address[6] = "00002"; //defining the radio channel, that modules(NRF24) will use to communicate between them
  
