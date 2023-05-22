#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
const char* ssid = "SRAVANI"; //Your Network SSID
const char* password = "aruna123"; //Your Network Password
WiFiClient client;
unsigned long myChannelNumber = 1676925; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "GZ157EFOHW4HXRKD"; //Your Write API Key
#define out 4//D2
#define in 5//D1
#define led 13//D7
int count=0;
void setup()
{
    Serial.begin(115200);
  Serial.println("Visitor Counter");
  delay(2000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(led, OUTPUT);
  Serial.println("Person in room");
  Serial.println(count);
WiFi.begin(ssid, password);
ThingSpeak.begin(client);
}
void loop()
{  
  int in_value = digitalRead(in);
  int out_value = digitalRead(out);
  if(in_value == LOW)
  {
    count++;
    Serial.println("Person In Room:");
    Serial.println(count);
    delay(1000);
  }

  if(out_value == LOW)
  {
    count--;

    Serial.println("Person In Room:");
    Serial.println(count);
    delay(1000);
  }


  if(count==0)
  {
    digitalWrite(led, LOW);
    Serial.println("Nobody In Room:");

    Serial.println("led is Off");
   delay(200);
  }

  else
  {
    digitalWrite(led, HIGH);
  }
  ThingSpeak.writeField(myChannelNumber, 1,count, myWriteAPIKey); //Update in ThingSpeak
}
