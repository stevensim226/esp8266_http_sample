from paho.mqtt import client as mqtt_client

broker = '0.0.0.0'
port = 1883
topic = "python/esp8266"
client_id = "python-steven-1"

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    # Set Connecting Client ID
    client = mqtt_client.Client(client_id)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client

def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

    client.subscribe(topic)
    client.on_message = on_message

if __name__ == "__main__":
    client = connect_mqtt()
    
    print("Sending message...")
    client.publish(topic, "Hello from Python!")

    print("Waiting for message from 'python/receive' ...")
    subscribe(client)
    client.loop_forever()
