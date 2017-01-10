
#include <ArduinoMessenger.h>
Messenger messenger;
message m;
byte mes[] = "SEND\n{\"resource\":\"2000 2800 500 1500 100 3000 150 350 350 400 850 2500 2350 2550 600 1300 150 2850 1050 350 750 2700 250 400 950 450 100 2700 250 1900 150 3000 700 \",\"value\":\"38\"};";
//byte mes[] = "GET\n{\"request\":\"get_data\"};";
int size = strlen((char*)mes);
int i = 0;

void setup(){
  Serial.begin(9600);
}

void serialPrint(const char * msg, char * content){
  Serial.print(msg);
  if(strlen(content) > 0){
    Serial.println(content);
  } else {
    Serial.println(F("<empty>"));
  }
}


void loop(){
  delay(1000);
  i++;
  Serial.print(F("=================\nIteration nr: "));
  Serial.println(i,DEC);

  byte * msg= (byte*)malloc(size * sizeof(byte));
  strcpy((char*)msg, (char*)mes);

  messenger.parseMessage(&m,msg,size);
  free(msg);

  serialPrint("Type: ", m.type);
  serialPrint("Request: ", m.request);
  serialPrint("Resource: ", m.resource);
  serialPrint("Value: ", m.value);

  messenger.reset(&m);

}