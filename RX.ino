#include <LoRa.h>
#define SS D8
#define RST D0
#define DIO0 D1
#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
#define FIREBASE_HOST "smartparking-c7905-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "L1DW3GhEVAI4gOQDbFFWNCFFkvXdSKku4iU2YAvE"    
#define WIFI_SSID "gayatri" // Change the name of your WIFI
#define WIFI_PASSWORD "01071971" // Change the password of your WIFI
void setup() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Receiver Host");
//  LoRa.setPins(SS, RST, DIO0);
     WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  LoRa.setPins(SS, RST, DIO0);

  Serial.println ("WiFi Connected!");
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Error");
    while (1);
  }else {
    Serial.println("LoRA Connected");
    }

}
 
void loop() {
//int packetSize = LoRa.parsePacket();
//  Serial.print(packetSize);

   LoRa.onReceive(onReceive);
   LoRa.receive();
   String alldata = "";
   if (1) {
    Serial.println("Receiving Data: ");
//    Serial.println("Is LoRa available? "+LoRa.available());
    
    while (LoRa.available()) {
//  String alldata = LoRa.readString();
    alldata += (char)LoRa.read();
    Serial.println(alldata);
}}else{
  Serial.println("package not found!");
}

  Serial.println(alldata);    
  delay(1000);
  String data="0";
  String data1="0";
  if (alldata == "00")
    {
       data="0";
       data1="0";
      }
    else if (alldata == "01")
    { data="0";
       data1="1";
      }
  else if (alldata == "10")
    { data="1";
       data1="0";
      }
    else if (alldata == "11")
    { data="1";
      data1="1";
      }      
    else
    {
      Serial.println("Error");
      }
String dataa = data;
int om = dataa.toInt();
String data11 = data1;
int om1 = data11.toInt();     
Firebase.setInt("Parking/Slot 1/",om);//Parking/
Firebase.setInt("Parking/Slot 2/",om1);//
Serial.print("om");
Serial.println(om);
Serial.print("om1");
Serial.println(om1);

delay(200);
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");
 
  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
}
