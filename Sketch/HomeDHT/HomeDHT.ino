// Arduino Yún sketch to provide the DHT22 sensor readings
// via HTTP GET on /arduino/readsensor as JSON body.
//
// You must install the DHT sensor library by Adafruit,
// if it's not installed already to be able to use this sketch.
//
// (c) Imre Horvath 2017

#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>
#include <DHT.h>

BridgeServer server;
DHT dht(2, DHT22);         // DHT22 is connected to Pin 2

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();          // Start Bridge
  digitalWrite(13, HIGH);  // Visually indicate when
                           // Bridge has started

  server.listenOnLocalhost();
  server.begin();

  dht.begin();
}

void loop() {
  BridgeClient client = server.accept();

  if (client) {
    process(client);
    client.stop();
  }

  delay(50);               // Poll every 50ms
}

void process(const BridgeClient& client) {

  String command = client.readStringUntil('\r');

  if (command == "readsensor") {

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    boolean success = !isnan(h) && !isnan(t) && !isnan(f);

    // Send HTTP headers

    client.println(F("Status: 200"));
    client.println(F("Content-Type: application/json"));
    client.println();

    // Construct the JSON response

    String data = "{\"success\":" +
                  String(success ? "true" : "false");

    if (success) {

      float hif = dht.computeHeatIndex(f, h);
      float hic = dht.computeHeatIndex(t, h, false);

      data += ", \"humidity\":" + String(h) +
              ", \"celsius\":" + String(t) +
              ", \"farenheit\":" + String(f) +
              ", \"hic\":" + String(hic) +
              ", \"hif\":" + String(hif);
    }

    data += "}";

    // Send JSON body

    client.println(data);

  } else {

    // unknown command, reply with error

    client.println(F("Status: 400"));
    client.println(F("Content-Type: text/plain"));
    client.println();
    client.print(F("Unknown command: "));
    client.println(command);
  }

}
