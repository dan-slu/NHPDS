/*
  Send message to Discrod Server through a HTTP POST request webhook
*/

#include <MKRNB.h>
NB nbAccess;        // NB access: include a 'true' parameter for debug enabled
GPRS gprsAccess;  // GPRS access
NBSSLClient client;  // Client service for TCP connection

int inPin = 7;
int res_connect;
int inPin_read;

char server[] = "discord.com";
char path[] = "/api/webhooks/1101519454728355941/bMi_f_XtPG1o6qZpy3CVg45sBV11eM7F81IqgUhZ0OYa5YhSGHyYLPfCdQ-wbyDlYjhA";

String pay_load = "{\"content\": \"Monkey at field 1\"}";
int pay_load_length = pay_load.length();

void error_blink_led() {
  while (true) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000 * 0.5);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000 * 0.5);
  }
}

void setup() {
  pinMode(inPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);

  if (nbAccess.begin(" ", "hologram", " ", " ") != NB_READY) {
    error_blink_led();
  }

  if (gprsAccess.attachGPRS() != GPRS_READY) {
    error_blink_led();
  }

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  inPin_read = digitalRead(inPin);
  if (inPin_read == 1) {
    digitalWrite(LED_BUILTIN, LOW);

    res_connect = client.connect(server, 443);

    if (res_connect) {
      // make a POST request
      client.println(String("POST ") + path + " HTTP/1.1");

      client.println(String("Host: ") + server);

      client.println("Content-Type:application/json");

      client.println(String("Content-Length: ") + pay_load_length);

      client.println();

      client.println(pay_load);

      client.println();
    } else {
      error_blink_led();
    }
    client.stop();
    delay(60 * 1000);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
