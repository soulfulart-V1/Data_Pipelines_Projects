#ifndef MCUNODEMCUESP12E_H
#define MCUNODEMCUESP12E_H

class MCUNodeMCUEsp12E{

public:

    //Defining common variables of the class

    //kafka variables
    struct{
    srting boostrap_server;
    string user_name;
    string pass_value;
    string topic;
    } kafka_parameters;

    //psysical_data
    string device_id;
    string device_class;
    string heart_pulse;
    string speed;
    string calories;
    string pressure_body;
    string temp;
    string humidity;
    string pressure_air;
    string recorded_time_device;
    string stream_time;
    string sound_intensity;
    
    //json_message
    string physical_data_json;
    
    //Public methods
    string getPhysicalDataJson();
    void sendKafkaPhysicalData();

};

private:

    void updatePhysicalData();
    void updatePhysicalDataJson();

#endif