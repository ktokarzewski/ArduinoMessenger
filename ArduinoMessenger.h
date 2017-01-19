#ifndef ArduinoMessenger_h
#define ArduinoMessenger_h
#define TYPE_SIZE 6
#define VAL 5
#define RES 200
#define REQ 6
#define M_BUF 250
#include <Arduino.h>

#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.println (x)
#else
 #define DEBUG_PRINT(x)
#endif

#ifdef AM_GLOBAL
#	define EXTERN
#else
#	define EXTERN extern
#endif

typedef
struct {
   char type[TYPE_SIZE];
   char value[VAL];
   char resource[RES];
   char request[REQ];
	} message_size_t;

EXTERN  message_size_t  message_size;

EXTERN const PROGMEM char PUT[] = "PUT";
EXTERN const PROGMEM char GET[] = "GET";
EXTERN const PROGMEM char HELLO[] = "HELLO";


EXTERN const PROGMEM char REQ_STR[] = "request";
EXTERN const PROGMEM char RES_STR[] = "resource";
EXTERN const PROGMEM char VAL_STR[] = "value";

EXTERN const char separators[] = "\":{}\n;";

const PROGMEM char resource_prefix[] = "{\"resource\":\"";
const PROGMEM char request_prefix[] = "{\"request\":\"";
const PROGMEM char value_prefix[] = "\",\"value\":\"";
const PROGMEM char suffix[] = "\",\"id\":\"prototype\"};";



class message {
public:
     char * type;
     char * value;
     char * resource;
     char * request;
};


class Messenger {
public:
  Messenger(Stream&);
  Messenger();
  bool parseMessage(message *,byte * msg, int size);
  bool parseMessage(message *);
  void sendGetMessage(char * request);
  void sendPutMessage(char * resource_name, char * resource_value);
  void reset(message*);
  void printPROGMEM(const char* mem);
  void print(const char* mem);
  void print(int value);

private:
  bool validateFormat(byte * msg, int size);
  bool validateType(char * type);
  bool validateContent(message *);
  bool validateSize(int);
  bool readFromStream(message *);
  void printFromPROGMEM(const char* mem);
  char mem_buf[25];
  Stream& stream;
  void save( char *,char *);
  byte * buffer;
  const int BUFF_SIZE = M_BUF;
};

#endif
