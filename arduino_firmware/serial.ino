#include "serial.h"


void serial_setup()
{

    Serial.begin(_serial.baud_rate);
    Serial.print(c1.name);
    Serial.print(" ");
    Serial.print(c1.version);
    Serial.print("\n");
}

void serial_loop()
{
	;
}
