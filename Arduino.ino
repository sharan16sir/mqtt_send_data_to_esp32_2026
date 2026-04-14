#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *wifi_ssid = "Meena-2.4G";
const char *wifi_password = "9845196672";

const char *mqtt_server = "192.168.1.8";

WiFiClient espClient;
PubSubClient client(espClient);

// 🔹 MQTT Callback
void callback(char* topic, byte* payload, unsigned int length)
{
  String msg = "";

  for (int i = 0; i < length; i++)
  {
    msg += (char)payload[i];
  }

  Serial.print("MQTT Received: ");
  Serial.println(msg);

  // 🔴 SEND TO STM32 via UART (TX only)
  Serial1.println(msg);
}

// 🔹 Reconnect MQTT
void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266Client"))
    {
      Serial.println("connected");
      client.subscribe("vecros/commands");
      Serial.println("Subscribed to vecros/commands");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(2000);
    }
  }
}

// 🔹 WiFi Setup
void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// 🔹 Setup
void setup()
{
  Serial.begin(115200);   // Debug UART (USB)
  Serial1.begin(115200);  // TX only (GPIO2)

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

// 🔹 Loop
void loop()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  Serial1.println("TEST");
  delay(1000);

  Serial1.println("TEST");
  delay(1000);
}
