#include "MCUNodeMCUEsp12E.h"

//Public methods

MCUNodeMCUEsp12E::MCUNodeMCUEsp12E(){

    this->device_class = "sensors";
    this->updatePhysicalData();
    this->updatePhysicalDataJson();
    
}

void MCUNodeMCUEsp12E::sendKafkaPhysicalData(string kafka_parameters[4]){

    string current_line="";
    
    this->updatePhysicalData();
    this->updatePhysicalDataJson();

    this->kafka_parameters.boostrap_server = kafka_parameters[0];
    this->kafka_parameters.user_name = kafka_parameters[1];
    this->kafka_parameters.pass_value = kafka_parameters[2];
    this->kafka_parameters.topic = kafka_parameters[3];

    HTTPClient http;

    string url_request="";

    ifstream url_request_file("urlKafkaProducer.txt");

    while (getline(url_request_file, current_line)) {

        url_request = url_request + current_line + "\n";

    }

    url_request.replace(url_request.find("BOOTSRAP_SERVER"), sizeof("BOOTSRAP_SERVER")-1, this->kafka_parameters.boostrap_server);
    url_request.replace(url_request.find("KAFKA_TOPIC"), sizeof("KAFKA_TOPIC")-1, this->kafka_parameters.topic);
    url_request.replace(url_request.find("USER_NAME"), sizeof("USER_NAME")-1, this->kafka_parameters.user_name);
    url_request.replace(url_request.find("PASS_VALUE"), sizeof("PASS_VALUE")-1, this->kafka_parameters.pass_value);

    //get stream time
    this->recorded_time_device = time(0);

    this->physical_data_json.replace(this->physical_data_json.find("<stream_time>"), sizeof("<stream_time>")-1, this->stream_time);

    url_request.replace(url_request.find("MESSAGE"), sizeof("MESSAGE")-1, this->physical_data_json);

    int http_code = http.POST(url_request);

}

//Private methods

void MCUNodeMCUEsp12E::updatePhysicalDataJson(){
    
    string payload_json="";
    string current_line="";

    ifstream payload_file("payloadModel.json");

    while (getline (payload_file, current_line)) {

        payload_json = payload_json + current_line + "\n";

    }

    payload_json.replace(payload_json.find("<device_id>"), sizeof("<device_id>")-1, this->device_id);
    payload_json.replace(payload_json.find("<device_class>"), sizeof("<device_class>")-1, this->device_class);
    payload_json.replace(payload_json.find("<temp>"), sizeof("<temp>")-1, this->temp);
    payload_json.replace(payload_json.find("<humidity>"), sizeof("<humidity>")-1, this->humidity);
    payload_json.replace(payload_json.find("<recorded_time_device>"), sizeof("<recorded_time_device>")-1, this->recorded_time_device);
    payload_json.replace(payload_json.find("<sound_intensity>"), sizeof("<sound_intensity>")-1, this->sound_intensity);

    payload_file.close();

    this->physical_data_json = payload_json;
    
}

void MCUNodeMCUEsp12E::updatePhysicalData(){

    this->recorded_time_device = time(0);

    DHT11Module dht_local(DHT11PIN, DHTTYPE);
    this->humidity = dht_local.humidity;
    this->temp = dht_local.temperature;

    //read sound intensity data
    this->sound_intensity = analogRead(SOUNDSENSOR_IN);

}