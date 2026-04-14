from paho.mqtt import client as mqtt
import time

def on_connect(client, userdata, flags, rc):
    print("Connected with result code:", rc)

def on_publish(client, userdata, mid):
    print("Message published, mid:", mid)

client = mqtt.Client()
client.on_connect = on_connect
client.on_publish = on_publish

print("Connecting...")
client.connect("192.168.1.3", 1883, 60)

client.loop_start()

time.sleep(2)  

while True:
    msg = input("enter: ")
    result = client.publish("vecros/commands", msg)
    print("Publish status:", result[0])