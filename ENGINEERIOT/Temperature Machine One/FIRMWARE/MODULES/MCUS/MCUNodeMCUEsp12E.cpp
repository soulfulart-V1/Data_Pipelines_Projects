#include <ctime>
#include <WiFi.h>
#include <fstream>
#include <iostream>
#include "Arduino.h"
#include "DHT11Module.h"
#include <ESP8266HTTPClient.h>

using namespace std;

//Hardware defined variables check schematics
#define DHT11PIN 16
#define SOUNDSENSOR_IN A0

//Public methods

MCUNodeMCUEsp12E::MCUNodeMCUEsp12E(){

    this->device_id = WiFi.macAddress();
    this->device_class = "sensors";
    this->updatePhysicalData();
    this->updatePhysicalDataJson();
    
}

MCUNodeMCUEsp12E::sendKafkaPhysicalData(string kafka_parameters[3]){

    this->kafka_parameters.boostrap_server = kafka_parameters[0];
    this->kafka_parameters.user_name = kafka_parameters[1];
    this->kafka_parameters.pass_value = kafka_parameters[2];

    HTTPClient http;

    string url_request="";

    ifstream url_request_file("payloadModel.json");

    while (getline (url_request_file, current_line)) {

        url_request = url_request + current_line + "\n";

    }

    this->recorded_time_device = time(0);

    this->physical_data_json.replace(this->physical_data_json.find("<stream_time>"), sizeof("<stream_time>")-1, this->stream_time);

    url_request.replace(url_request.find("MESSAGE"), sizeof("MESSAGE")-1, this->physical_data_json);

    http.post(url_request);

}

MCUNodeMCUEsp12E::updatePhysicalDataJson(){
    
    string payload_json="";

    ifstream payload_file("payloadModel.json");

    while (getline (payload_file, current_line)) {

        payload_json = payload_json + current_line + "\n";

    }

    payload_json.replace(payload_json.find("<device_id>"), sizeof("<device_id>")-1, this->device_id);
    payload_json.replace(payload_json.find("<device_class>"), sizeof("<device_class>")-1, this->device_class);
    payload_json.replace(payload_json.find("<temp>"), sizeof("<temp>")-1, this->temp);
    payload_json.replace(payload_json.find("<humidity>"), sizeof("<humidity>")-1, this->humidity);
    payload_json.replace(payload_json.find("<recorded_time_device>"), sizeof("<recorded_time_device>")-1, this->recorded_time_device);
    payload_json.replace(payload_json.find("<sound_intensity>"), sizeof("<sound_intensity>")-1, this->sound_intensity);

    payload_file.close();

    this->physical_data_json = payload_json;
    
}

//Private methods

MCUNodeMCUEsp12E::updatePhysicalData(){

    this->recorded_time_device = time(0);
    this->DHT.read11(DHT11PIN);
    this->humidity = this->DHT.humidity;
    this->temperature = this->DHT.temperature;
    this->sound_intensity = analogRead(SOUNDSENSOR_IN);

}