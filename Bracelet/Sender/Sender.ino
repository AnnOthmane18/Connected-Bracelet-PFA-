#include "NRF24_TX.h"


boolean Send_Coord = false;

void setup() {
  Serial.begin(115200);
  
  pinMode(LED,OUTPUT);
  pinMode(2,INPUT);
  
  ss.begin(GPSBaud);
  Serial.println("Start Locating...");
  
  //setting up the interruption pin to pin2 on ATmega328p
  attachInterrupt(0,buttonPressed,CHANGE);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  digitalWrite(LED,LOW);
}

void loop() {
  
  while (ss.available() > 0){
    if (gps.encode(ss.read())){
        //Reading and updating data wherever the gps signal is Available
      toString();
      Coordinates();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
  
  if(Send_Coord){ 
    radio.write(&Coord, sizeof(Coord));//Sending the structure that contains the 2 needed variables LATITUDE + LONGTITUDE
  
    Serial.print("Lat: ");
    Serial.println(Coord.Lat);
    Serial.print("Lon: ");
    Serial.println(Coord.Lon);

  }
}

void buttonPressed()
{
  digitalWrite(LED,HIGH);//as an indicator
  Send_Coord = true; // i used a bool variable to send each time an updated data, for each button pressed
}

void toString(){
  /*Getting the GPS Location(Lat && Lon) converting them into strings*/
  Latitude  = String(gps.location.lat(),6); //I used STRING fct tocontrol the float precision
  Longitude = String(gps.location.lng(),6);  

  //COnverting the string into Char Array + storing the values in the structure variables, to be able to send it over the NRF Module
  Latitude.toCharArray(Coord.Lat,Latitude.length() + 1 ); 
  Longitude.toCharArray(Coord.Lon,Longitude.length() + 1 );

}


void Coordinates()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
 Serial.println();
}
