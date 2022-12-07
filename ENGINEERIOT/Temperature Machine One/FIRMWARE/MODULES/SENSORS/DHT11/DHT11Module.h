#ifndef DHT11MODULE_H
#define DHT11MODULE_H

class DHT11ToKafka{

public:

    //Defining common variables of the class
    dht DHT;
    string humidity;
    const int dhtPin;
    string temperature;

    //Public methods
    void getPhysicalData();

};

#endif