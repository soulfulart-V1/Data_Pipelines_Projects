import os
import json
import boto3
import requests
import datetime

from io import StringIO
from pandas import DataFrame

#global itens
s3 = boto3.client('s3')
bucket_name = 'soulfulart-data-lake'

def lambda_handler(event, context):

    headers = {
        'Kafka-Auto-Offset-Reset': 'earliest'   
    }
    
    response = requests.get(
        'https://bright-piranha-5383-us1-rest-kafka.upstash.io/consume/GROUP_NAME/GROUP_INSTANCE_NAME/iot_sensors_real_time',
        headers=headers,
        auth=(os.environ['SASL_PLAIN_USERNAME'], os.environ['SASL_PLAIN_PASSWORD'])
        )
        
    messages = json.loads(response.text.replace("'", '"'))

    device_data_field = 'physical_data'
    messages_physical_data = []

    for message in messages:
        message_values = message["value"].replace("'", '"')
        message_values = message_values.replace("\\t", '')
        message_values = message_values.replace("\\n", '')
        message_values = json.loads(message_values)
        messages_physical_data.append(message_values[device_data_field])

    final_dataframe = DataFrame.from_records(messages_physical_data)

    object_key = 'STREAM/ENGINEERINGIOT/IOT_GET_DATA_210904307/REGION_A/PHYSICAL_VALUES'
    file_name = str(datetime.datetime.now())
    object_key = object_key + file_name +'.csv'
    
    csv_buffer = StringIO()
    final_dataframe.to_csv(csv_buffer)
    
    if not final_dataframe.empty:
        s3.put_object(Body=csv_buffer.getvalue(), Bucket=bucket_name, Key=object_key, ContentType='text/csv')
        log_message = 'File '+object_key+' write succesfully!'
    
    else:        
        log_message = 'No new messages!'
    
    return {

        'message' : log_message
        
    }