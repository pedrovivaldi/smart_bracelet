void setup() {
  // put your setup code here, to run once:
 if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
if (client.connect(serverIp, 80)) {
      client.println("GET HTTP/1.1");
      client.println("Content-Type: text/html");
      client.println("Connection: close");  // the connection will be closed after completion of the response
      client.println("Refresh: 5");  // refresh the page automatically every 5 sec
      client.println();
          
      client.println("Deu merda");
      client.println();
      // give the web browser time to receive the data
      delay(1);
      // close the connection:
      client.stop();
      Serial.println("client disconnected");
    } else {
      Serial.println("Connection Failed");
    }
}
