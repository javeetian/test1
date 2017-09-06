
#ifndef GARAGEDOOR_OPENER_H
#define OPEN_SWTICH_PIN

typedef enum {
	GD_UNKNOWN,
	GD_OPEN,
	GD_CLOSED,
	GD_OPENING,
	GD_CLOSING
} GarageDoorState;


#define GARAGE_DOOR_ACTION_TOPIC "action"
#define GARAGE_DOOR_STATUS_TOPIC "status"

#define OPEN_SENSOR_PIN 1
#define CLOSE_SENSOR_PIN 2
#define OPEN_SWTICH_PIN 3
#define SERIAL_BAUD 115200

#endif