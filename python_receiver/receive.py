# vim: expandtab tabstop=4 shiftwidth=4

from datetime import datetime
from json import dumps
from os import environ
from time import sleep
from typing import Dict, Tuple

#from azure.iot.device import IoTHubDeviceClient, Message

import serial

#def iothub_client_init():
#    return IoTHubDeviceClient.create_from_connection_string(environ['CONNECTIONSTRING'])

def parse_key_value(key_value: str) -> Tuple[str, float]:
    key, value = key_value.split(':')
    value, _ = value.split('|')
    return key.strip(), float(value)

def parse_telemetry(telemetry: str) -> Dict[str, float]:
    key_values = telemetry.split(';')
    results = {}

    for key_value in key_values:
        key, value = parse_key_value(key_value)
        results[key] = float(value) / 100.0

    return results

def main():
    arduino = serial.Serial(port='/dev/cu.usbmodem22101', baudrate=115200, timeout=.1)
    #client = iothub_client_init()

    while True:
        data = arduino.readline()

        if len(data) > 0:
            print(datetime.now())
            print(data)

            if data.startswith(b'Got: '):
                telemetry = parse_telemetry(str(data, encoding='utf8')[5:].strip())
                message_str = dumps(telemetry)
                print(message_str)
                #client.send_message(Message(message_str))

        sleep(1)

if __name__ == "__main__":
    main()
