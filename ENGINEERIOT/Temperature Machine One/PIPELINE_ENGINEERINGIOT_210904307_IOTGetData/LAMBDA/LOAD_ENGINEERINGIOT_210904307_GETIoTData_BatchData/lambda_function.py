import json
import boto3
import urllib
import datetime
import requests

#global objects
PREFIX = 'STREAM/ENGINEERINGIOT/IOT_GET_DATA_210904307/REGION_A/PHYSICAL_VALUES'
s3 = boto3.client('s3', Prefix=PREFIX) #define s3 service
bucket_name = 'soulfulart-data-lake'

def lambda_handler(event, context):
    
    year = int(event['time'][0:4])
    month = int(event['time'][5:7])
    day = int(event['time'][8:10])

    date_to_extract =  datetime.datetime(year, month, day)
    
    #date to extract
    today_date_minus_one = date_to_extract - datetime.timedelta(days=1)
    
    #get year month and day separated
    used_year = str(today_date_minus_one.year)
    
    #avoid use numbers without left zero 
    if (today_date_minus_one.month < 10):
        used_month = '0'+str(today_date_minus_one.month)
        
    else: used_month = str(today_date_minus_one.month)
    
    if (today_date_minus_one.day<10):
        used_day = '0'+str(today_date_minus_one.day)
    else: used_day = str(today_date_minus_one.day)
   
    complete_daily_data = ''

    for item_file in s3.all():
        response = s3.get_object(Bucket=bucket_name, Key=item_file)
        complete_daily_data = complete_daily_data + response['Body'].read().decode('utf-8')
    
    PARTITION = used_year+used_month+used_day
    object_path = 'BRONZE/ENGINEERINGIOT/IOT_GET_DATA_210904307/REGION_A/PHYSICAL_VALUES/yearmonthday='+PARTITION
    objetct_key = object_path+'.csv'
    
    s3.put_object(Body=complete_daily_data, Bucket=bucket_name, Key=objetct_key)
    
    return {
        
        'message' : 'Request: refine.metadata_time='+str(today_date_minus_one)+' stored at '+objetct_key,
        'time' : str(date_to_extract)
        
    }