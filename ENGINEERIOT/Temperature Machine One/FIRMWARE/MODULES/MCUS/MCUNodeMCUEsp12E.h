#ifndef MCUNODEMCUESP12E_H
#define MCUNODEMCUESP12E_H

#include <ctime>
#include <string>
#include <fstream>
#include <istream>
#include <iostream>
#include "Arduino.h"
#include "DHT11Module.h"
#include <ESP8266HTTPClient.h>

using namespace std;

//Hardware defined variables check schematics
#define DHT11PIN 16
#define DHTTYPE DHT11
#define SOUNDSENSOR_IN A0

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
    string stream_time;
    string sound_intensity;
    
    //json_message
    string physical_data_json;

    //Public methods
    MCUNodeMCUEsp12E();
    void sendKafkaPhysicalData(string kafka_parameters[4]);

private:

    void updatePhysicalData();
    void updatePhysicalDataJson();

};

#endif