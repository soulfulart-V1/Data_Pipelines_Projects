#include "DHT11Module.h"

DHT11Module::DHT11Module(const int dhtPin){

    this->dhtPin = dhtPin;
    this->getPhysicalData();

}

DHT11ToKafka::getPhysicalData(){

    this->dht.read11(this->dhtPin);
    this->temperature = this->DHT.temperature;
    this->humidity = this->DHT.humidity;

}