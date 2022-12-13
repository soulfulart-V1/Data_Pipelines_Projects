#include <ESP8266WiFi.h>
#include <MCUNodeMCUEsp12E.h>

//Objects
WiFiClient client;
mcu_instance MCUNodeMCUEsp12E();

//kafka credentials
string kafka_parameters_local[3];

kafka_parameters_local[0] = "INSERT_BOOTSTRAPSERVER_DURING_COMPILE_PHASE";
kafka_parameters_local[1] = "INSERT_USER_DURING_COMPILE_PHASE";
kafka_parameters_local[2] = "INSERT_PASS_DURING_COMPILE_PHASE";
kafka_parameters_local[3] = "INSERT_KAFKA_TOPIC_DURING_COMPILE_PHASE";

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