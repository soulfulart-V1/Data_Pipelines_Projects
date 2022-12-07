#include "Arduino.h"
#include "DHT11Module.h"

MCUNodeMCUEsp12E::MCUNodeMCUEsp12E(int pinout_map, string kafka_parameters[3]){

    this->pinout_map = pinout_map;
    this->kafka_parameters.boostrap_server = kafka_parameters[0];
    this->kafka_parameters.user_name = kafka_parameters[1];
    this->kafka_parameters.pass_value = kafka_parameters[2];

    this->getPhysicalData();
    this->getPinoutMap();
}

DHT11ToKafka::getPhysicalData(){

    this->DHT.read11(this->dhtPin);
    this->temperature = this->DHT.temperature;
    this->humidity = this->DHT.humidity;

}