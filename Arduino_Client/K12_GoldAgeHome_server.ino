#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
            
#include <ESP8266HTTPClient.h>
            
const char* ssid = "HOTBOX-3A6C";
const char* pswd = "0544933268";
            
WiFiClient client;
int server_port = 80;//http
            
void wifi_Setup() {
  Serial.println("wifiSetup");
  //WiFi.begin(ssid);
    WiFi.begin(ssid, pswd);
            
  while (WiFi.status() != WL_CONNECTED) 
  {
     Serial.println("trying ...");
     digitalWrite(pinLedY,HIGH);
     delay(200);
     digitalWrite(pinLedY,LOW);
     delay(200);
  }
   digitalWrite(pinLedY,HIGH);
   Serial.println("Connected to network");
}
            
void SendData(int val) {
   HTTPClient http;
   String dataURL = "";
   dataURL += "ACT=SET&DEV="+String(DEV);
   dataURL += "&CH="+String(CH);
   dataURL += "&VAL="+String(val);
   http.begin(client,"http://api.kits4.me/GEN/api.php?" + dataURL);
   int httpCode = http.GET();
   Serial.println(httpCode);
   http.end();
}
            
int GetData() {
   int ret = -1;
   HTTPClient http;
   String dataURL = "";
   dataURL += "ACT=GET&DEV="+String(DEV);
   dataURL += "&CH="+String(CH);
   http.begin(client, "http://api.kits4.me/GEN/api.php?" + dataURL);
   int httpCode = http.GET();
   Serial.println(httpCode);
   if (httpCode == HTTP_CODE_OK) {
       Serial.print("HTTP response code ");
       Serial.println(httpCode);
       String Res = http.getString();
       Serial.println(Res);
       ret = Res.toInt();
     }
       http.end();
            
    return ret;
}
            
