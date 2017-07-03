#include "temp_sensor.h"

temp_sensor::temp_sensor()
{
	setName("DS18B20");
	active = t_sensor.init_ok();
	this->data_type = DOUBLE;
}
vector<uint8_t> temp_sensor::getData()
{
	double temp = t_sensor.getDataC();
	vector<uint8_t> data(sizeof(temp));
	*((double*)data.data()) = temp;
	return data;
}
temp_sensor::~temp_sensor()
{
}