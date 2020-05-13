#include <WiFi.h>

#include "Adafruit_MQTT.h"

#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "INFINITUM0B2BC5"

#define WLAN_PASS       "XY78KL55FH3"

#define AIO_SERVER      "io.adafruit.com"

#define AIO_SERVERPORT  1883                  

#define AIO_USERNAME    "Luis_Uriel"

#define AIO_KEY         "aio_AnkA78WO3CH1r4XTV9Eh2je5v42Y"

int output=2; 
//int output2=15; 
int output2=4; 

WiFiClient client;     // Create an ESP8266 WiFiClient class to connect to the MQTT server.

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);        // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.

Adafruit_MQTT_Subscribe LED_Control = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED_Control");
Adafruit_MQTT_Subscribe LED_Control2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED_Control2");



void MQTT_connect();

void setup() {

  Serial.begin(115200);

  delay(10);

pinMode(2,OUTPUT);
//pinMode(15,OUTPUT);
pinMode(4,OUTPUT);


 // Connect to WiFi access point.

  Serial.println(); Serial.println();

  Serial.print("Connecting to ");

  Serial.println(WLAN_SSID);

 

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println();

 Serial.println("WiFi connected");

  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  
  
  
  
  mqtt.subscribe(&LED_Control);
  
  mqtt.subscribe(&LED_Control2);




}

uint32_t x=0;

void loop() {

   MQTT_connect();

Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(5000)))
  {

    if (subscription == &LED_Control) {

      Serial.print(F("Got: "));

      Serial.println((char *)LED_Control.lastread);

       if (!strcmp((char*) LED_Control.lastread, "ON"))

      {

        digitalWrite(2, HIGH);

      }

      else

      {

        digitalWrite(2, LOW);

      }

    }


///////////////////////////////////////7

 if (subscription == &LED_Control2) {

      Serial.print(F("Got: "));

      Serial.println((char *)LED_Control2.lastread);

       if (!strcmp((char*) LED_Control2.lastread, "ON2"))

      {

        digitalWrite(4, HIGH);

      }

      else

      {

        digitalWrite(4, LOW);

      }

    }

////////////////////////////////////////////////////

  }

 

 

}

void MQTT_connect() {

  int8_t ret;

  // Stop if already connected.

  if (mqtt.connected()) {

    return;

  }

 Serial.print("Connecting to MQTT... ");

uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected

       Serial.println(mqtt.connectErrorString(ret));

       Serial.println("Retrying MQTT connection in 5 seconds...");

       mqtt.disconnect();

       delay(5000);  // wait 5 seconds

       retries--;

       if (retries == 0) {

         // basically die and wait for WDT to reset me

         while (1);

       }

  }

  Serial.println("MQTT Connected!");

}
