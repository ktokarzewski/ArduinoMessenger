# ArduinoMessenger

Arduino library designed to handle parsing messages in format specified in [ArduinoMessengerClient][amcmf].

## Installation

1. Download [ZIP](https://github.com/ktokarzewski/ArduinoMessenger/archive/master.zip) 
2. Extract zip file
3. Move `ArduinoMessenger` folder to your IDE/libraries directory.

## Quick start
Include `<ArduinoMessenger.h>` header in your project and declare:
```
Messenger messenger;
message msg;
```
For testing purposes we define an example message:

``` 
char * exampleMessage = "GET\n{\"request\":\"requested resource\"};";
```
Library is designed to parse messages from external sources like [EthernetClient](https://www.arduino.cc/en/Reference/EthernetClient) 
where size of incoming message is unknown, so in this example we need to apply dynamic memory allocation:
```
int size = strlen(exampleMessage);
char * messageToParse = (char*)malloc(sizeof(char) * size);
```
And copy original message content:
```
strcpy(messageToParse,exampleMessage);
```
Parsing message:

```
if(messenger.parseMessage(&msg,(byte*)messageToParse, size)){
    Serial.println(msg.type);
    Serial.println(msg.request);
} else
    Serial.println("Invalid message format");
```
Output:
```
GET
requested resource
```
After parsing `messageToParse` is useless because `parseMessage` function modifies passed message string. After parsing we should free reserved memory:
```
free(messageToParse);
```
If you need to clear `msg` content use:
```
messenger.reset(&msg);
```
### Stream integration
Version 0.2.0 supports parsing incoming messages directly from Arduino [streams](https://www.arduino.cc/en/Reference/Stream).
All you have to do is pass reading/writing stream to `Messenger` constructor (by default `Messenger` object is initialized with [Serial](https://www.arduino.cc/en/reference/serial)). For example:
```
#include <ArduinoMessenger.h>
#include <Ethernet.h>

EthernetClient client;
Messenger messenger(client);
message m;
```
To parse message from `client` invoke :
```
if(messenger.parseMessage(&m)){
    // parsing sucessful 
} else {
    // parsig failed
}
```
If there is any valid incoming message method will return `true`.

It is also possible to send messages to `client` by one of these methods:

- `messenger.sendGetMessage("requested resource");`
- `messenger.sendPutMessage("resource_name","resource_value");`
- `messenger.print("raw string");`
- `messenger.printPROGMEM(PROGMEM_STRING);`

Where `PROGMEM_STRING` is `char` array [stored in flash memory](https://www.arduino.cc/en/Reference/PROGMEM).


**Define static message size**

To control your sketch memory usage change `RES`,`VAL`,`REQ` and `M_BUF` constants values in  `ArduinoMessenger.h`.
- `RES` defines maximal expected length of `msg.resource` string,
- `VAL` defines maximal expected length of `msg.value` string,
- `REQ` defines maximal expected length of `msg.request` string,
- `M_BUF` defines maximal size of incoming message.

Parsing will fail if incoming message is bigger then `M_BUF` value or any of message content fields in `messageToParse` is longer then it is defined by these constants.

More examples can be found at [examples directory][examples].
For more complex, real life application of this library checkout [ArduinoMessengerServer repository][ams].
## Issues management
Issues are managed at the GitHub [project issues page][issues].

Everybody is allowed to report bugs or ask for features.

## Getting the code
The latest version of the code can be found at the [GitHub project page][scm].

Feel free to fork it, and share the changes.
## Collaborate

The project is still under ongoing development, and any help will be well received.

There are two ways to help: reporting errors and asking for extensions through the issues management, or forking the repository and extending the project.

## Authors

* **Kamil Tokarzewski** - *Initial work* - [ktokarzewski](https://github.com/ktokarzewski)

See also the list of [contributors](https://github.com/ktokarzewski/ArduinoMessenger/contributors) who participated in this project.
## License
The project is released under the [MIT License][license].

[issues]:https://github.com/ktokarzewski/ArduinoMessenger/issues
[scm]:https://github.com/ktokarzewski/ArduinoMessenger
[license]: http://www.opensource.org/licenses/mit-license.php
[examples]:https://github.com/ktokarzewski/ArduinoMessenger/tree/examples
[amc]:https://github.com/ktokarzewski/ArduinoMessengerClient
[amcmf]:https://github.com/ktokarzewski/ArduinoMessengerClient#message_format
[ams]:https://github.com/ktokarzewski/ArduinoMessengerServer