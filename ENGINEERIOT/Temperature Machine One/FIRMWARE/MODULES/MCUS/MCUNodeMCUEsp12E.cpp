#include "MCUNodeMCUEsp12E.h"

//Public methods

MCUNodeMCUEsp12E::MCUNodeMCUEsp12E(){

    this->device_class = "sensors";
    this->recorded_time_device = this->getCurrentDateTime();
    this->updatePhysicalData();
    this->updatePhysicalDataJson();
    
}

string MCUNodeMCUEsp12E::urlKafkaDataProducer(string kafka_parameters[4]){

    this->recorded_time_device = this->getCurrentDateTime();
    this->updatePhysicalData();
    this->updatePhysicalDataJson();
    this->kafka_parameters.boostrap_server = kafka_parameters[0];
    this->kafka_parameters.user_name = kafka_parameters[1];
    this->kafka_parameters.pass_value = kafka_parameters[2];
    this->kafka_parameters.topic = kafka_parameters[3];

    string url_request=this->urlKafkaProducerModel;

    url_request.replace(url_request.find("BOOTSRAP_SERVER"), sizeof("BOOTSRAP_SERVER")-1, this->kafka_parameters.boostrap_server);
    url_request.replace(url_request.find("KAFKA_TOPIC"), sizeof("KAFKA_TOPIC")-1, this->kafka_parameters.topic);
    url_request.replace(url_request.find("USER_NAME"), sizeof("USER_NAME")-1, this->kafka_parameters.user_name);
    url_request.replace(url_request.find("PASS_VALUE"), sizeof("PASS_VALUE")-1, this->kafka_parameters.pass_value);
    url_request.replace(url_request.find("MESSAGE"), sizeof("MESSAGE")-1, this->physical_data_json);

    return url_request;

}

//Private methods

void MCUNodeMCUEsp12E::updatePhysicalDataJson(){

    string payload_json = this->payloadModel;

    payload_json.replace(payload_json.find("<device_id>"), sizeof("<device_id>")-1, this->device_id);
    payload_json.replace(payload_json.find("<device_class>"), sizeof("<device_class>")-1, this->device_class);
    payload_json.replace(payload_json.find("<temp>"), sizeof("<temp>")-1, this->temp);
    payload_json.replace(payload_json.find("<humidity>"), sizeof("<humidity>")-1, this->humidity);
    payload_json.replace(payload_json.find("<sound_intensity>"), sizeof("<sound_intensity>")-1, this->sound_intensity);
    payload_json.replace(payload_json.find("<recorded_time_device>"), sizeof("<recorded_time_device>")-1, this->recorded_time_device);

    this->physical_data_json = payload_json;
    
}

void MCUNodeMCUEsp12E::updatePhysicalData(){
    //modules
    //DHT11Module dht_local(DHT11PIN, DHTTYPE);

    this->humidity = "75";
    this->temp = "28.5";

    //read sound intensity data
    this->sound_intensity = analogRead(SOUNDSENSOR_IN);

}

string MCUNodeMCUEsp12E::getCurrentDateTime(){

    int i;
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, "pool.ntp.org");

    timeClient.begin();
    timeClient.update();
    String current_time_String = timeClient.getFormattedTime();
    string current_time_date="YYYY-MM-DDTHH:MM:SS";

    time_t epochTime = timeClient.getEpochTime();
    
    struct tm *ptm = gmtime ((time_t *)&epochTime);
    int current_year = ptm->tm_year+1900;
    int current_month = ptm->tm_mon+1;
    int month_day = ptm->tm_mday;
    int hour_now = ptm->tm_hour;
    int minute_now = ptm->tm_min;
    int second_now = ptm->tm_sec;
    String hour_now_string = "00";
    String minute_now_string = "00";
    String second_now_string = "00";


    hour_now = hour_now - GMT_BRL;
    if (hour_now<0){
        hour_now = hour_now + 24;
    }

    hour_now_string = String(hour_now);

    if (hour_now<10){
        hour_now_string = "0"+ String(hour_now);
    }

    minute_now_string = String(minute_now);
    if (minute_now<10){
        minute_now_string = "0"+ String(minute_now);
    }

    second_now_string = String(second_now);
    if (second_now<10){
        second_now_string = "0"+ String(second_now);
    }

    String current_date_String = String(current_year)+"-"+String(current_month)+"-"+String(month_day);
    current_date_String = current_date_String + "T" + hour_now_string;
    current_date_String = current_date_String + ":" + minute_now_string;
    current_date_String = current_date_String + ":" + second_now_string;
    
    for (i=0; i<current_date_String.length(); i++){
        current_time_date[i] = current_date_String[i];
    }

    return current_time_date;

}
