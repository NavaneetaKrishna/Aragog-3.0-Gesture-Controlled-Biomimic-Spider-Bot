#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "sri";
const char* password = "hsk@0205";
const char* mqttServer = "192.168.207.7";
const int mqttPort = 1883;
const char* mqttTopic = "prithyush";

WiFiClient espClient;
PubSubClient client(espClient);

const int ledPin = LED_BUILTIN;

void setup() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP8266Client")) {  // Changed client name
            Serial.println("Connected to MQTT");
            client.subscribe(mqttTopic);
        } else {
            Serial.print("Failed, rc="); Serial.print(client.state());
            Serial.println(" Trying again in 5 seconds");
            delay(5000);
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message received: ");
    
    String message = "";  // Use String for proper handling
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    message.trim();  // Remove spaces and newlines

    Serial.print("[");
    Serial.print(message);
    Serial.println("]");

    if (message[0] == 'a') {  // Corrected string comparison
        Serial.println("Blinking LED 5 times");
        for (int i = 0; i < 5; i++) {
            digitalWrite(ledPin, HIGH);
            delay(500);
            digitalWrite(ledPin, LOW);
            delay(500);
        }
    } else {
        digitalWrite(ledPin, HIGH);
    }
}

void loop() {
    client.loop();
}
