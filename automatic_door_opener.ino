
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>

#include"index.h"

//---------------------------------------------------------------
//Our HTML webpage contents in program memory

const char* ssid     = "Computer_Block";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "";     // The password of the Wi-Fi network

//Motor A
const int inputPin1  = 5;    // Pin 15 of L293D IC
const int inputPin2  = 16;    // Pin 10 of L293D IC
//Motor B
const int inputPin3  = 4;   // Pin  7 of L293D IC
const int inputPin4  = 0;   // Pin  2 of L293D IC

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
 
}

void handledoorOpen() { 
 Serial.println("Door Open");

 digitalWrite(inputPin1, LOW);
 digitalWrite(inputPin2, HIGH);
 digitalWrite(inputPin3, LOW);
 digitalWrite(inputPin4, HIGH); 

 delay(700);
 
 digitalWrite(inputPin1, LOW);
 digitalWrite(inputPin2, LOW);
 digitalWrite(inputPin3, LOW);
 digitalWrite(inputPin4, LOW); 

 server.send(200, "text/html", "Door is open"); //Send ADC value only to client ajax request
}

void handledoorClose() { 
 Serial.println("Door Closed");
 digitalWrite(inputPin1, HIGH);
 digitalWrite(inputPin2, LOW);   
 digitalWrite(inputPin3, HIGH);
 digitalWrite(inputPin4, LOW);  

 delay(700);
 
 digitalWrite(inputPin1, LOW);
 digitalWrite(inputPin2, LOW);   
 digitalWrite(inputPin3, LOW);
 digitalWrite(inputPin4, LOW);
   
 server.send(200, "text/html", "Door is Closed"); //Send ADC value only to client ajax request
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  pinMode(inputPin3, OUTPUT);
  pinMode(inputPin4, OUTPUT);  
 
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/doorOpen", handledoorOpen); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/doorClose", handledoorClose);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
