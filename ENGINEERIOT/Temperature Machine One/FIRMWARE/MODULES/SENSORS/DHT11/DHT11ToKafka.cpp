#include "DHT.h"
#include "Arduino.h"
#include "DHT11ToKafka.h"

DHT11ToKafka::DHT11ToKafka(const int analogInPin, string bootstrap_server, string credentials_cluster[2]){

    this->analogInPin = analogInPin;
    this->bootstrap_server = bootstrap_server;
    this->credentials_cluster = credentials_cluster;

}

DHT11ToKafka::sendPhysicalDataKafka(){

    this->analogInPin = analogInPin;
    this->bootstrap_server = bootstrap_server;
    this->credentials_cluster = credentials_cluster;

}

DHT11ToKafka::sendPhysicalDataPayload(){

    string temperature;
    string humidity;

    this->DHT.read11(this->analogInPin);
    temperature = this->DHT.temperature;
    humidity = this->DHT.humidity;

}