#ifndef DS18B20__H_
#define DS18B20__H_

#include <string>

using namespace std;

class DS18B20
{
public:
	DS18B20(unsigned int adapter_nr, int addr);
	float getDataC();
	float getDataF();
protected:
	float temp_C2F(float c);
	string device_path;
	bool init_succ;
};

	

#endif //DS18B20__H_
