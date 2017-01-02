
#define AM_GLOBAL
#include "ArduinoMessenger.h"
#undef AM_GLOBAL


Messenger::Messenger() {
}

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
	else if (compare(type, SEND)) {
		return true;
	}
	else if (compare(type, HELLO)) {
		return true;
	}

	return false;
}

bool Messenger::validateContent(message * result) {
	return true;
}


void Messenger::save(char * dest, char * source) {
	strcpy(dest, source);
}
