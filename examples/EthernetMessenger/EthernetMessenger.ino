#include <UIPEthernet.h>
#include <ArduinoMessenger.h>

EthernetServer server = EthernetServer(5544);
EthernetClient client;
Messenger messenger(client);
message m;

bool compareType(const char* type) {
  if (strcmp_P(m.type, type) == 0) {
    return true;
  }
  else {
    return false;
  }
}

void setup() {
  uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  IPAddress myIP(192, 168, 1, 10);
  Ethernet.begin(mac, myIP);
  Serial.begin(9600);
  server.begin();
}

void loop() {
  if (client = server.available()) {
    Serial.println(F("New client connected"));
  }
  if(client.connected()){
    if(messenger.parseMessage(&m)){
      if(compareType(GET)){
        messenger.sendPutMessage(m.request, "new value");
      } else if(compareType(PUT){
        messenger.sendGetMessage("new request");
      }
      messenger.reset(&m);
    }

  }

}
