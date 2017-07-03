#ifndef DS18B20__H_
#define DS18B20__H_

#include <string>

using namespace std;

class DS18B20
{
public:
	DS18B20();
	double getDataC();
	double getDataF();
	bool init_ok();
protected:
	double temp_C2F(double c);
	string device_path;
	bool init_succ;
};

	

#endif //DS18B20__H_
