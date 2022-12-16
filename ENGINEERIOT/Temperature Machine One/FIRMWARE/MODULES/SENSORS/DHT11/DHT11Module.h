#ifndef DHT11MODULE_H
#define DHT11MODULE_H

#include "DHT.h"
#include <string>

class DHT11Module{

public:

    //Defining common variables of the class
    DHT dht;
    string humidity;
    const int dhtPin;
    string temperature;

    //Public methods
    DHT11Module(const int dhtPin);
    void getPhysicalData();

};

#endif