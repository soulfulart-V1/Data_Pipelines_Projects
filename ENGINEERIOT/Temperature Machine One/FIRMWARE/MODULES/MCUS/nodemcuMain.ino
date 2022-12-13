#include <MCUNodeMCUEsp12E.h>

mcu_instance MCUNodeMCUEsp12E();

//credentials
string kafka_parameters_local[3];

kafka_parameters_local[0] = "INSERT_BOOTSTRAPSERVER_VALUE_DURING_COMPILE_PHASE";
kafka_parameters_local[1] = "INSERT_USER_VALUE_DURING_COMPILE_PHASE";
kafka_parameters_local[2] = "INSERT_PASS_VALUE_DURING_COMPILE_PHASE";

void loop (){

    mcu_instance.sendKafkaPhysicalData(kafka_parameters_local);

}