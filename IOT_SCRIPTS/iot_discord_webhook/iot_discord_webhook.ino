/*
  Send message to Discrod Server through a HTTP POST request webhook
*/

// libraries
#include <MKRNB.h>

// initialize the library instance
NB nbAccess;        // NB access: include a 'true' parameter for debug enabled
GPRS gprsAccess;  // GPRS access
NBSSLClient client;  // Client service for TCP connection

// messages for serial monitor response
int inPin = 6;
int res_connect;
int inPin_read;

char server[] = "discord.com";
char path[] = "/api/webhooks/1101519454728355941/bMi_f_XtPG1o6qZpy3CVg45sBV11eM7F81IqgUhZ0OYa5YhSGHyYLPfCdQ-wbyDlYjhA";

void setup() {
  pinMode(inPin, INPUT);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("Connecting NB IoT / LTE Cat M1 network...");
  if (nbAccess.begin(" ", "hologram", " ", " ") != NB_READY) {
    while (true);
  }
  Serial.println("Connected");

  // attach GPRS
  if (gprsAccess.attachGPRS() == GPRS_READY) {
    Serial.println("GPRS Connected");
  }

}

void loop() {
  inPin_read =  digitalRead(inPin);
  if (inPin_read == 1) {
    res_connect = client.connect(server, 443);

    String pay_load = "{\"content\": \"Monkey at field 1\"}";
    int pay_load_length = pay_load.length();

    Serial.println(pay_load);
    Serial.println(pay_load_length);

    if (res_connect) {
      Serial.println("Sending POST");

      // make a HTTP 1.0 GET request (client sends the request)
      client.print("POST ");
      client.print(path);
      client.println(" HTTP/1.1");

      client.print("Host: ");
      client.println(server);

      client.println("Content-Type:application/json");

      client.print("Content-Length: ");
      client.println(pay_load_length);

      //client.println("Connection: close");

      client.println();

      client.println(pay_load);
      client.println();

      Serial.print("POST sent");
    } else {
      Serial.print("error");
    }
    client.stop();
    delay(60*1000);
  }
}
