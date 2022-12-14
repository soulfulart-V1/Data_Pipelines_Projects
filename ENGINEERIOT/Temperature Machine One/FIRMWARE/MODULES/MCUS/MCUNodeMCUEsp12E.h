#ifndef MCUNODEMCUESP12E_H
#define MCUNODEMCUESP12E_H

#include <ctime>
#include <WiFi.h>
#include <fstream>
#include <iostream>
#include "Arduino.h"
#include "DHT11Module.h"
#include <ESP8266HTTPClient.h>

class MCUNodeMCUEsp12E{

public:

    //kafka variables
    struct{
    String boostrap_server;
    String user_name;
    String pass_value;
    String topic;
    } kafka_parameters;

    //psysical_data
    String device_id;
    String device_class;
    String heart_pulse;
    String speed;
    String calories;
    String pressure_body;
    String temp;
    String humidity;
    String pressure_air;
    String recorded_time_device;
    String stream_time;
    String sound_intensity;
    
    //json_message
    String physical_data_json;
    
    //Public methods
    void sendKafkaPhysicalData(String kafka_parameters[4]);

private:

    void updatePhysicalData();
    void updatePhysicalDataJson();

};


#endif