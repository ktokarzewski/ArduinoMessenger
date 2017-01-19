#define AM_GLOBAL
#include "ArduinoMessenger.h"
#undef AM_GLOBAL
Messenger::Messenger(Stream& s):stream(s) {}
Messenger::Messenger():stream(Serial){}


void Messenger::reset(message *result) {
	result->value = message_size.value;
	result->value[0] = '\0';
	result->resource = message_size.resource;
	result->resource[0] = '\0';
	result->request = message_size.request;
	result->request[0] = '\0';
	result->type = message_size.type;
	result->type[0] = '\0';

}

bool compare(char * a, const char * b) {
	int l = strlen_P(b);
	if ((strncmp_P(a, b, l) == 0))
		return true;
	return false;
}

bool Messenger::readFromStream(message * result){
	int size = 0;
	bool parseResult = false;

	if(size = stream.available()){
		if(size < M_BUF){

			buffer = (byte*)malloc(size);
			size = stream.readBytes(buffer,size);

			if(buffer != NULL){
				parseResult = parseMessage(result,buffer,size);
			}

			free(buffer);
		} else {
			stream.flush();
		}
	}
	return parseResult;
}

bool Messenger::parseMessage(message * result){
	return readFromStream(result);
}
void Messenger::printPROGMEM(const char* mem){
	strcpy_P(mem_buf, mem);
	print(mem_buf);
}
void Messenger::print(const char* mem){
	stream.print(mem);
}
void Messenger::print(int value){
	stream.print(value);
}

void Messenger::sendGetMessage(char * request){
	printPROGMEM(GET);
	print("\n");
	printPROGMEM(request_prefix);
	print(request);
	printPROGMEM(suffix);
}

void Messenger::sendPutMessage(char * resource,char * value){
	printPROGMEM(PUT);
	print("\n");
	printPROGMEM(resource_prefix);
	print(resource);
	printPROGMEM(value_prefix);
	print(value);
	printPROGMEM(suffix);
}
bool Messenger::parseMessage(message * result, byte * msg, int size) {
	reset(result);
	if (!validateSize(size)) {
		return false;
	}
	if (!validateFormat(msg, size)) {
		return false;
	}

	char * temp = strtok((char*)msg, separators);

	if (validateType(temp)) {
		save(result->type, temp);
	}
	else {
		return false;
	}

	while (temp != NULL) {
		if (compare(temp, RES_STR)) {
			temp = strtok(NULL, separators);
			if (strlen(temp) < RES) {
				save(result->resource, temp);
			}
			else {
				return false;
			}
		}
		else
			if (compare(temp, REQ_STR)) {
				temp = strtok(NULL, separators);
				if (strlen(temp) < REQ) {
					save(result->request, temp);
				}
				else {
					return false;
				}
			}
			else
				if (compare(temp, VAL_STR)) {
					temp = strtok(NULL, separators);
					if (strlen(temp) < VAL) {
						save(result->value, temp);
					}
					else {
						return false;
					}

				}
				else {
					temp = strtok(NULL, separators);
				}
	}
	return validateContent(result);
}

bool Messenger::validateFormat(byte * msg, int size) {
	bool eol = false;
	for (byte i = 3; i < 6; i++) {
		if (msg[i] == '\n') {
			eol = true;
		}
	}
	return eol && (msg[size - 1] == ';');
}

bool Messenger::validateSize(int s) {
	return BUFF_SIZE > s;
}

bool Messenger::validateType(char * type) {
	if (compare(type, GET)) {
		return true;
	}
	else if (compare(type, PUT)) {
		return true;
	}
	else if (compare(type, HELLO)) {
		return true;
	}

	return false;
}

bool Messenger::validateContent(message * result) {
	return true; //TODO
}


void Messenger::save(char * dest, char * source) {
	strcpy(dest, source);
}
