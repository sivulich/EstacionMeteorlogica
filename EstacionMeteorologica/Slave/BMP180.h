#pragma once
#include "Sensor.h"
class BMP180 :Sensor {
public:
	BMP180();
	BMP180(BMP180& s);
private:
	bool readTemp,read
};