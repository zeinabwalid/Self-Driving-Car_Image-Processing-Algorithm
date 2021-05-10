#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <iostream>   
#include <string.h>
#include <ArduinoJson.h> 

SoftwareSerial NodeMCU(D2,D3);
int RST_PIN = 5;
int SS_PIN = 2;
MFRC522 mfrc522(SS_PIN, RST_PIN); 
void setup(){
	Serial.begin(9600);
	NodeMCU.begin(4800);
	pinMode(D2,INPUT);
	pinMode(D3,OUTPUT);
 //RFID
   SPI.begin();       
   mfrc522.PCD_Init(); 
   //local server   
   WiFi.begin("Galal Hossam", "255199825");
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.println("Wait");
    }
    WiFi.mode(WIFI_STA);
}

void loop(){
	String dir ;
  //RFID
  if ( mfrc522.PICC_IsNewCardPresent())
    {
        if ( mfrc522.PICC_ReadCardSerial())
        {
           Serial.print("Tag UID:");
           String content= "";
           byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin("http://192.168.43.187:80/sendRFID");  
    http.addHeader("Content-Type","application/json" ); 
    Serial.println("in");
    String data = "{\"RFID\":\"" + String(mfrc522.uid.uidByte[0], HEX)+' '+String(mfrc522.uid.uidByte[1], HEX)+' '+String(mfrc522.uid.uidByte[2], HEX)+' '+String(mfrc522.uid.uidByte[3], HEX)+"\"}";
   Serial.println(data);
   http.POST(data);
  }
  Serial.println();  
        } 
        }
        //local server
        if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin("http://192.168.43.187:80/getDirection"); 
    http.addHeader("Content-Type","application/json" );
    int httpreq = http.GET();
    if (httpreq> 0){
      dir = http.getString();
     Serial.println(dir[14]);
      NodeMCU.print(dir[14]);
      NodeMCU.println("\n");
      }
   
    http.end();}
    else{Serial.println("Error in WiFi connection");}
}
