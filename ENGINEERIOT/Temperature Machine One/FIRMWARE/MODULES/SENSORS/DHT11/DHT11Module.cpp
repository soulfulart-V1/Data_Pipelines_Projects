#include "DHT11Module.h"

DHT11Module::DHT11Module(const int dht_pin, const int dht_type){

    this->dht_pin = dht_pin;
    this->dht_pin = dht_type;
    this->getPhysicalData();

}

void DHT11Module::getPhysicalData(){

    DHT dht_instance(this->dht_pin, this->dht_type);
    this->temperature = dht_instance.readTemperature();
    this->humidity = dht_instance.readHumidity();

}

