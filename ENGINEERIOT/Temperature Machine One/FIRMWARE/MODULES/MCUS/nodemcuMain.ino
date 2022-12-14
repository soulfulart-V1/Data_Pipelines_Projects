#include <ESP8266WiFi.h>
#include <MCUNodeMCUEsp12E.h>

//Objects
WiFiClient client;
MCUNodeMCUEsp12E mcu_instance;

//kafka credentials
String kafka_parameters_local[4]={
  "INSERT_BOOTSTRAPSERVER_DURING_COMPILE_PHASE",
  "INSERT_USER_DURING_COMPILE_PHASE",
  "INSERT_PASS_DURING_COMPILE_PHASE",
  "INSERT_KAFKA_TOPIC_DURING_COMPILE_PHASE"
  };

//wifi credentials
const char *ssid =  "INSERT_WIFI_SSID";
const char *pass =  "INSERT_WIFI_PASS";
 
void setup() 
{

       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }

      Serial.println("");
      Serial.println("WiFi connected"); 
}
 

void loop (){

    mcu_instance.sendKafkaPhysicalData(kafka_parameters_local);

    //try to reconnect if connection goes down
    while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }

}