#include "CoogleIOT.h"
#include "GarageDoor-Opener.h"

CoogleIOT *iot;
PubSubClient *mqtt;

GarageDoorState _currentState = GD_UNKNOWN;

String getDoorStateAsString(GarageDoorState state)
{
	switch(state) {
		case GD_OPEN:
			return String("open");
		case GD_CLOSED:
			return String("closed");
		case GD_OPENING:
			return String("opening");
		case GD_CLOSING:
			return String("closing");
		case GD_UNKNOWN:
			return String("unknown");
	}

	if(iot->serialEnabled()) {
		Serial.println("Warning: Garage Door State value unknown");
	}

	return String("unknown");
}

GarageDoorState getGarageDoorState()
{
	bool isClosed, isOpen;
	GarageDoorState retval = GD_UNKNOWN;

	isOpen = digitalRead(OPEN_SENSOR_PIN) == LOW;
	isClosed = digitalRead(CLOSE_SENSOR_PIN) == LOW;

	if(isOpen && isClosed) {
		if(iot->serialEnabled()) {
			Serial.println("ERROR: Can't be both open and closed at the same time! Sensor failure!");
		}
		retval = GD_UNKNOWN;
		return retval;
	}

	if(!isOpen && isClosed) {
		retval = GD_CLOSED;
		return retval;
	}

	if(isOpen && !isClosed) {
		retval = GD_OPEN;
		return retval;
	}

	if(!isOpen && !isClosed) {

		if((_currentState == GD_OPEN) || (_currentState == GD_CLOSING)) {
			retval = GD_CLOSING;
			return retval;
		}

		if((_currentState == GD_CLOSED) || (_currentState == GD_OPENING)) {
			retval = GD_OPENING;
			return retval;
		}
	}

	retval = GD_UNKNOWN;
	return retval;
}

void toggleActionPin(unsigned int delayMS, unsigned int repeat)
{
	for(int i = 0; i < repeat; i++) {
		digitalWrite(OPEN_SWTICH_PIN, HIGH);
		delay(delayMS);
		digitalWrite(OPEN_SWTICH_PIN, LOW);
		delay(delayMS);
	}
}

void setup()
{
	iot = new CoogleIOT(LED_BUILTIN);

	iot->enableSerial(iot->getBaudrate());
	iot->initialize();

	pinMode(OPEN_SWTICH_PIN, OUTPUT);
	pinMode(OPEN_SENSOR_PIN, INPUT_PULLUP);
	pinMode(CLOSE_SENSOR_PIN, INPUT_PULLUP);

	digitalWrite(OPEN_SWTICH_PIN, LOW);

}

void loop()
{
	GarageDoorState liveState;

	iot->loop();

}