#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

char Lat[14]="not available";
char Lon[14]="not available";

struct coordinates{
  char Lat[10] = " ";
  char Lon[10] = " ";
};
struct coordinates Coordinates;


//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

/*********************************************************************************************************
 * ***********************************JZT: JSON Web Token*************************************************
**********************************************************************************************************/
//======================Authentication Stage======================/

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"


/*********************************************************************************************************
 * ****************************************WIFI Config****************************************************
**********************************************************************************************************/
// Insert your network credentials
#define WIFI_SSID "ORANGE-DIGITAL-CENTER"
#define WIFI_PASSWORD "Welcome@2021"


/*********************************************************************************************************
 * ******************************************API KEY******************************************************
**********************************************************************************************************/
// Insert Firebase project API Key
#define API_KEY "AIzaSyC-ETbuhgoLkIXLKNWgv4rUcrwQkdtlh3g"

/*********************************************************************************************************
 * ******************************************DB URL*******************************************************
**********************************************************************************************************/
// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://esp32-test-c053c-default-rtdb.europe-west1.firebasedatabase.app/" 

const byte address[6]="00002"; //setting up the same channel for the gateway(receiver) as i did for the sender
