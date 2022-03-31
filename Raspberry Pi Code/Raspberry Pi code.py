import serial
import time
from pubnub.pubnub import PubNub
from pubnub.pubnub import SubscribeListener
from pubnub.pnconfiguration import PNConfiguration
from pubnub.exceptions import PubNubException
import pubnub
pnconf = PNConfiguration()
pnconf.publish_key = 'pub-c-3dd4d929-0243-4c13-a11f-d8076bbcfc0c'
pnconf.subscribe_key = 'sub-c-278756ba-8923-11ec-9f2b-a2cedba671e8'
pnconf.uuid = 'karan1199'
pubnub = PubNub(pnconf)
channel='karan1199' 
arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1)
my_listener = SubscribeListener()
pubnub.add_listener(my_listener)
pubnub.subscribe().channels(channel).execute()
my_listener.wait_for_connect()
print('connected')


def write_read(x):
    arduino.write(str.encode(x))
    time.sleep(0.05)
    data = arduino.readline()
    data=int_val = int.from_bytes(data, "big", signed="True")
    return data


while True:
    result = my_listener.wait_for_message_on(channel)
    
    print(result.message)
    robotstart = result.message[0]['robotstart']
    light  = result.message[0]['light']
    r = result.message[0]['color']['r']
    g = result.message[0]['color']['g']
    b = result.message[0]['color']['b']
    data = [robotstart, light , r,g,b] 
    print(robotstart , light , r,g,b)
    data =  str(robotstart) + " " + str(light) + " " + str(r) + " " + str(g) + " " + str(b)
    value = write_read(data)
    print(value)
