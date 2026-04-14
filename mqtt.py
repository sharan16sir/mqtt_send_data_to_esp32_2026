from paho.mqtt import client as mqtt

client=mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.connect("192.168.1.8", 1883, 60)


client.loop_start()

while True:
   msg=input("enter command:")
   client.publish("vecros/commands",msg)
    

