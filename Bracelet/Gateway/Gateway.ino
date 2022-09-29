//ESP8266
#include "config.h"

RF24 radio(2,4);

void setup(){
  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  //making sure we are connected to the network
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  radio.begin();
  radio.openReadingPipe(0, address); //openning the chosen channel for listenning to any incoming data 
  radio.setPALevel(RF24_PA_MIN); // setting the Power Amplifier to its min level 
  radio.startListening();
  Serial.println("Start Listening !!");
}

void loop(){

    //reading the received data
    
  if (radio.available()) {
    radio.read(&Coordinates, sizeof(Coordinates));
    Serial.print("Lat: ");
    Serial.println(Coordinates.Lat);
    Serial.print("Lon: ");
    Serial.println(Coordinates.Lon);
  }
  else{
    char Lat[25]="not available";
    char Lon[25]="not available";
    }
    
    //Storing coordinate's lat and lon in firebase RTDB Node(Coordinates) 
    //&&& Checking at the same time whether the data has been successfully transferred or not
    
    if (Firebase.RTDB.setString(&fbdo, "Coordinates/Latitude", Coordinates.Lat)){
        Serial.println("---------------PASSED---------------");
        Serial.println("Recaived Data(Latitude): ");
        Serial.println(Coordinates.Lat);
     }
     else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
     }

     if (Firebase.RTDB.setString(&fbdo, "Coordinates/Longitude", Coordinates.Lon)){
        Serial.println("---------------PASSED---------------");
        Serial.println("Recaived Data(Longitude): ");
        Serial.println(Coordinates.Lon);
     }
     else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
     }
  
}
