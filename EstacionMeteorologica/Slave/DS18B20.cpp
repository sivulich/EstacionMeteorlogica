/*#include "DS18B20.hpp"
#include <dirent.h>	//format of directory entries
#include <fcntl.h>
#include <math.h>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include <string>

#define ONEWIRE_PATH "/sys/bus/w1/devices"

using namespace std;

DS18B20::DS18B20()
{
	DIR *oneWire_dir = opendir(ONEWIRE_PATH);
	struct dirent *dirent;
	init_succ = false;
	//From http://owfs.sourceforge.net/family.html
	//Family ID 28: programmable resolution digital thermometer
	//So, Look for device
	device_path = ONEWIRE_PATH;
	if(oneWire_dir != nullptr)
	{
		while((dirent = readdir (oneWire_dir))) //check all devices
		{
			//DT_LNK: Symbolic link
			if(dirent->d_type == DT_LNK && strstr(dirent->d_name, "28-") != nullptr)
			{
				device_path += '/';
				device_path += dirent->d_name;
				device_path += '/';
				device_path += "w1_slave";
				init_succ = true;
				break;
			}
		}
		closedir(oneWire_dir);
	}
	//Do not open file. Reading is done when file is open.
}

double DS18B20::getDataC()
{
	int temp_file;
	double number = NAN;
	if(init_succ && (temp_file = open(device_path.c_str(), O_RDONLY)) >=0 )
	{
		char buffer[256];
		size_t d_size;
		string data;
		while((d_size = read(temp_file, buffer, 256)) > 0) 
			data += string(buffer,d_size);
		//TO-DO: Check if working and parse string to return temp.
		char read_ok[10];
		int temp;
		int read_count = sscanf(data.c_str(),
			"%*x %*x %*x %*x %*x %*x %*x %*x %*x : crc=%*x %s\n%*x %*x %*x %*x %*x %*x %*x %*x %*x t=%d",
			read_ok,
			&temp
		);
		if (read_count == 2 && (strcmp(read_ok,"YES") == 0))
			number = (double) temp;
		close(temp_file);
	}
	return number/1000;
}

double DS18B20::getDataF()
{
	return temp_C2F(getDataC());
}

bool DS18B20::init_ok()
{
	return init_succ;
}

double DS18B20::temp_C2F(double tempC)
{
	return 1.8*tempC+32;
}*/
