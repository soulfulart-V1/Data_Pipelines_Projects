#ifndef DHT11MODULE_H
#define DHT11MODULE_H

#include "DHT.h"
#include <string>

using namespace std;

class DHT11Module{

public:

    //Defining common variables of the class
    string humidity;
    string temperature;
    int dht_pin;
    int dht_type;

    //Public methods
    DHT11Module(int dht_pin, int dh_type);
    void getPhysicalData();

};

#endif
