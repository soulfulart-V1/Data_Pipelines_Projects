#ifndef DHT11TOKAFKA_H
#define DHT11TOKAFKA_H

class DHT11ToKafka{

public:

    //Defining common variables of the class
    
    uint8_t numberAlarms;

    //Defining public methods
    DHT11ToKafka(const int analogInPin, string bootstrap_server);
    
private:
    
};

#endif