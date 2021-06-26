#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
const char* ssid     = "SSID";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "PASS";     // The password of the Wi-Fi network

const char* websockets_server_host = "serv.squatnet.co.uk"; //Enter server adress 
const uint16_t websockets_server_port = 2323; // Enter server port
SoftwareSerial sofSer(0,2); // Soft serial on pins 0,2
using namespace websockets;
bool doTweet(String user,String text){
    // send the tweet to mega
    String theTweet = "@";
    Serial.println(user);
    Serial.println(text);
    theTweet.concat(user);
    theTweet.concat("+&+");
    theTweet.concat(text);
    theTweet.concat("$+");
    Serial.println(theTweet.length());
    String theUnChopped = theTweet;
    if (theTweet.length() > 32){ // sending just 32 bytes at a time
        while (theTweet.length() > 32){
            String thisPart = "$>$";
            thisPart += theTweet.substring(0,32);
            theTweet.remove(0,32);
            Serial.print("string length = ");
            Serial.println(theTweet.length());
            thisPart += "$<$";
            
            char c = '0';
            int tries = 0;
            while (c != '%' && tries < 5){ // try 5 times or until % is received
                tries += 1;
                sofSer.write(thisPart.c_str());
                delay(40); // give mega chance to respond
                c = sofSer.read();
            }
            if(c == '%'){
                Serial.print("part sent success");
            }
            if(tries == 5){
                
                Serial.print("too many tries ");
                Serial.println(c);
                return false;
            }
        }
        return true;
    } else {
        sofSer.write(theTweet.c_str());
        return true;
    }
}
WebsocketsClient client;
void setup() {
    Serial.begin(9600);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    // Check if connected to wifi
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("No Wifi!");
        return;
    }
    sofSer.begin(9600);
    Serial.println("Connected to Wifi, Connecting to server.");
    // try to connect to Websockets server
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
    if(connected) {
        Serial.println("Connecetd!");
    } else {
        Serial.println("Not Connected!");
    }
    
    // run callback when messages are received
    client.onMessage([&](WebsocketsMessage message) {
        Serial.print("Got Message: ");
        Serial.println(message.data());
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, message.data());
        String cmd = doc["command"];
        Serial.println(cmd);
        if(cmd == "ping"){
          DynamicJsonDocument rep(1024);
          rep["command"] = "pong";
          String toSend = "";
          serializeJson(rep, toSend);
          client.send(toSend.c_str());
        }
        else if (cmd=="tweet"){
          String user = doc["user"];
          String text = doc["text"];
          doTweet(user,text);
        }
    });
}

void loop() {
    // let the websockets client check for incoming messages
    if(client.available()) {
        client.poll();
    }
    delay(500);
}
