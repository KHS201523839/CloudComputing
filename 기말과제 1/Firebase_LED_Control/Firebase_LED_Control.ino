// DB key : a7wZoun661zssTXpWVDWlyjguqJNH1UWytH40Rnd
// Project name : led-on-off-2020-c1453

#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>      
#define FIREBASE_HOST "fir-led-control-901bf"     
#define FIREBASE_AUTH "EiheITeY9xBl76ryuwNG8U34qKs703HiT73j3ycl" 
#define WIFI_SSID "201523839"                                          
#define WIFI_PASSWORD "01091335027"  

String red_fireStatus = ""; 
String blue_fireStatus = ""; 
   
int red_led = D3;          
int blue_led = D4;
                                                              
void setup() 
{
  Serial.begin(9600);
  delay(1000);    
  pinMode(red_led, OUTPUT);  
  pinMode(blue_led, OUTPUT);
                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to firebase
  Firebase.setString("RED_LED_STATUS", "OFF"); //send initial string of led status
  Firebase.setString("BLUE_LED_STATUS", "OFF");
}
 
void loop() 
{
  red_fireStatus = Firebase.getString("RED_LED_STATUS");     // get ld status input from firebase
  if (red_fireStatus == "ON")   { // compare the input of led status received from firebase
    Serial.println("RED LED Turned ON");                                                        
    digitalWrite(red_led, HIGH);          // make external led ON
  } 
  else if (red_fireStatus == "OFF") {    // compare the input of led status received from firebase
    Serial.println("RED LED Turned OFF");
    digitalWrite(red_led, LOW);      // make external led OFF
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }

  delay(2000);

  blue_fireStatus = Firebase.getString("BLUE_LED_STATUS");     // get ld status input from firebase
  if (blue_fireStatus == "ON")   { // compare the input of led status received from firebase
    Serial.println("BLUE LED Turned ON");                                                        
    digitalWrite(blue_led, HIGH);          // make external led ON
  } 
  else if (blue_fireStatus == "OFF") {    // compare the input of led status received from firebase
    Serial.println("BlUE LED Turned OFF");
    digitalWrite(blue_led, LOW);      // make external led OFF
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }

  delay(2000);
}
