#pragma once
#include "configs.h"

class Sensor
{
public:
	Sensor();
	virtual ~Sensor();

	virtual bool getData(vector<char>&) = 0;
	uint8_t getType();
	void setNumber(uint8_t number);
	uint8_t getNumber();
protected:
	uint8_t sensor_number;
	uint8_t data_type;
	union data
	{	
		int dataI;
		long dataL;
		long long dataLL;
		unsigned int dataU;
		long unsigned dataUL;
		long long unsigned dataULL;
		float dataF;
		double dataD;
	};
};

