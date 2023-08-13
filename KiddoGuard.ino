#include <ESP32WiFi.h>
#include <PubSubClient.h>
#include "room.hpp"

static SensorIR bottom_sensor_1(GPIO_BOTTOM_SENSOR_1);
static SensorIR bottom_sensor_2(GPIO_BOTTOM_SENSOR_2);
static SensorIR top_sensor(GPIO_TOP_SENSOR);

static Buzzer buzzer(GPIO_BUZZER);

static EntranceDetector sala_cozinha(bottom_sensor_1, bottom_sensor_2, top_sensor);
static EntranceDetector cozinha_sala(bottom_sensor_2, bottom_sensor_1, top_sensor);

static EntranceDetector* sala_entrances[] = {&cozinha_sala};
static EntranceDetector* conzinha_entrances[] = {&sala_cozinha};

static Room sala(sala_entrances, 1, buzzer, 0);
static Room cozinha(conzinha_entrances, 1, buzzer, 1);

static int sala_child_count = 0;
static int sala_adult_count = 0;
static int cozinha_child_count = 0;
static int cozinha_adult_count = 0;

String user = "usuario mqtt";
String passwd = "senha mqtt";

const char* ssid = "nome rede";
const char* password = "senha rede";
const char* mqtt_server = "ip mqtt";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

        // Create a random client ID
        String clientId = user;
        clientId += String(random(0xffff), HEX);

        // Attempt to connect
        if (client.connect(clientId.c_str(), user.c_str(), passwd.c_str())) {
            Serial.println("connected");

            // Once connected, publish an announcement...
            client.publish((user + "/homehello").c_str(), "hello world");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");

            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }

    Serial.println();
}

void setup() {
    Serial.begin(9600);
    setup_wifi();
    client.setServer(mqtt_server, 80);
    client.setCallback(callback);
}

void loop() {
    // Checks if client is connected
    if (!client.connected()) {
        reconnect();
    }

    client.loop();

    sala.update();
    cozinha.update();

    sala_child_count = sala.get_child_count();
    sala_adult_count = sala.get_adult_count();
    cozinha_child_count = cozinha.get_child_count();
    cozinha_adult_count = cozinha.get_adult_count();

    client.publish(("/comodo/sala/child_count").c_str(), sala_child_count);
    client.publish(("/comodo/sala/adult_count").c_str(), sala_adult_count);
    client.publish(("/comodo/cozinha/child_count").c_str(), cozinha_child_count);
    client.publish(("/comodo/cozinha/adult_count").c_str(), cozinha_adult_count);
}
