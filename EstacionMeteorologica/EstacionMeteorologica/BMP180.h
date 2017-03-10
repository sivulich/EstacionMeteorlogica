#pragma once

class bmp180
{
public:
	bmp180();
	virtual ~bmp180();

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