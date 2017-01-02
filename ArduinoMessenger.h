#ifndef ArduinoMessenger_h
#define ArduinoMessenger_h
#define TYPE_SIZE 6
#define VAL 5
#define RES 200
#define REQ 6
#define M_BUF 250
#include <Arduino.h>

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

EXTERN const PROGMEM char SEND[] = "SEND";
EXTERN const PROGMEM char GET[] = "GET";
EXTERN const PROGMEM char HELLO[] = "HELLO";


EXTERN const PROGMEM char REQ_STR[] = "request";
EXTERN const PROGMEM char RES_STR[] = "resource";
EXTERN const PROGMEM char VAL_STR[] = "value";

EXTERN const char separators[] = "\":{}\n;";


class message{
public:
     char * type;
     char * value;
     char * resource;
     char * request;
};


 class Messenger{
public:
  Messenger();
  bool parseMessage(message *,byte * msg, int size);
  void reset(message*);
private:
  bool validateFormat(byte * msg, int size);
  bool validateType(char * type);
  bool validateContent(message *);
  bool validateSize(int);
  void save( char *,char *);
  const int BUFF_SIZE = M_BUF;
};

#endif
