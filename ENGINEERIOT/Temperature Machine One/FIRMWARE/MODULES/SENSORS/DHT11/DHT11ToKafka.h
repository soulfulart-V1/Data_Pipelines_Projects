#ifndef DHT11TOKAFKA_H
#define DHT11TOKAFKA_H

class DHT11ToKafka{

public:

    //Defining common variables of the class
    dht DHT;
    string temperature;
    string humidity;
    string bootstrap_server;
    string credentials_cluster[2];
    const int analogInPin;

    //Defining public methods
    DHT11ToKafka(const int analogInPin, string bootstrap_server, string credentials_cluster[2]);
    void sendPhysicalDataKafka ();
    string sendPhysicalDataPayload ();
    
private:
    void getPhysicalData()
};

#endif