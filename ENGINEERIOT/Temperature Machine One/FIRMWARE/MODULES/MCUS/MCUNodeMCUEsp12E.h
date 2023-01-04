#ifndef MCUNODEMCUESP12E_H
#define MCUNODEMCUESP12E_H

#include <string>
#include <dht11.h>
#include <fstream>
#include <istream>
#include <iostream>
#include "Arduino.h"
#include "WiFiUdp.h"
#include <NTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

using namespace std;

//Hardware defined variables check schematics
#define DHT11PIN 16
#define SOUNDSENSOR_IN A0
#define GMT_BRL 3 //BRL GMT time
#define DELAY_WAIT_GET_TIME 100

class MCUNodeMCUEsp12E{

public:

    //kafka variables
    struct{
    string boostrap_server;
    string user_name;
    string pass_value;
    string topic;
    } kafka_parameters;

    //psysical_data
    string device_id;
    string device_class;
    string heart_pulse;
    string speed;
    string calories;
    string pressure_body;
    string temp;
    string humidity;
    string pressure_air;
    string recorded_time_device;
    string sound_intensity;
    
    //json_message
    string physical_data_json;

    //Public methods
    MCUNodeMCUEsp12E();
    string urlKafkaDataProducer(string kafka_parameters[4]);

private:

    //constants
    string urlKafkaProducerModel = "https://BOOTSRAP_SERVER/produce/KAFKA_TOPIC/MESSAGE";
    string payloadModel="{\"physical_data\":{\"device_id\":\"<device_id>\",\"device_class\":\"<device_class>\",\"heart_pulse\":\"NULL\",\"speed\":\"NULL\",\"calories\":\"NULL\",\"pressure_body\":\"NULL\",\"temp\":\"<temp>\",\"humidity\":\"<humidity>\",\"pressure_air\":\"NULL\",\"recorded_time_device\":\"<recorded_time_device>\",\"sound_intensity\":\"<sound_intensity>\"}}";

    void updatePhysicalData();
    void updatePhysicalDataJson();
    string getCurrentDateTime();

};

#endif