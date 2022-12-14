#ifndef DHT11MODULE_H
#define DHT11MODULE_H

#include "DHT.h"

class DHT11ToKafka{

public:

    //Defining common variables of the class
    DHT dht;
    String humidity;
    const int dhtPin;
    String temperature;

    //Public methods
    void getPhysicalData();

};

#endif