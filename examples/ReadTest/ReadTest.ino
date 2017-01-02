
#include <ArduinoMessenger.h>
#include <Arduino.h>


Messenger messenger;
message m;
byte mes[] = "SEND\n{\"resource\":\"2000 2800 500 1500 100 3000 150 350 350 400 850 2500 2350 2550 600 1300 150 2850 1050 350 750 2700 250 400 950 450 100 2700 250 1900 150 3000 700 \",\"value\":\"38\",\"id\":\"root\"};";
//byte mes[] = "GET\n{\"id\":\"user\",\"request\":\"get_data\"};";
int size = strlen((char*)mes);
int i = 0;



void setup(){
  Serial.begin(9600);
  delay(7000);
}


void loop(){
  delay(1000);
  i++;
  Serial.print(F("i: "));
  Serial.println(i);

  byte * msg= (byte*)malloc(strlen((char*)mes));
  strcpy((char*)msg, (char*)mes);

  messenger.parseMessage(&m,msg,size);

  free(msg);

  Serial.println(F("Type: "));
  Serial.println(m.type);

  Serial.println(F("Request: "));
  Serial.println(m.request);

  Serial.println(F("Resource: "));
  Serial.println(m.resource);
  
  Serial.println(F("Value: "));
  Serial.println(m.value);
}
