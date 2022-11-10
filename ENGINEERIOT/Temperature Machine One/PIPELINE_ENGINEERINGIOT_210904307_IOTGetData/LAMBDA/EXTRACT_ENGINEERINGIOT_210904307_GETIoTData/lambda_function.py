import os
import json
import requests


def lambda_handler(event, context):

    headers = {
        'Kafka-Auto-Offset-Reset': 'earliest',
        
    }
    
    response = requests.get(
        'https://bright-piranha-5383-us1-rest-kafka.upstash.io/consume/GROUP_NAME/GROUP_INSTANCE_NAME/iot_sensors_real_time',
        headers=headers,
        auth=(os.environ['SASL_PLAIN_USERNAME'], os.environ['SASL_PLAIN_PASSWORD'])
        )
        
    messages = response.text
    
    return {

        'message' : str(messages)
        
    }