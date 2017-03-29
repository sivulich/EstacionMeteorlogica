#include "DS1820.h"
#include <dirent.h>	//format of directory entries

#define ONEWIRE_PATH "/sys/bus/w1/devices"

bs18b20::bs18b20(unsigned int adapter_nr, int addr)
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
		while((dirent = readdir (dir))) //check all devices
		{
			//DT_LNK: Symbolic link
			if(dirent->d_type == DT_LNK && strstr(dirent->d_name, "28-") != nullptr)
			{
				device_path += '/';
				device_path += dirent->d_name;
				device_path += "w1_slave";
				init_succ = true;
				break;
			}
		}
		closedir(oneWire_dir);
	}
	//Do not open file. Reading is done when file is open.
}

float bs18b20::getDataC()
{
	int temp_file;
	float number = NAN;
	if(init_succ && (temp_file = open(device_path.c_str(), O_RDONLY)) )
	{
		char buffer[256];
		size_t d_size;
		string data;
		while((d_size = read(temp_file, buffer, 256)) > 0) 
			string += string(buffer,d_size);
		//TO-DO: Check if working and parse string to return temp.
		close(fd);
	}
	return number;
}

float bs18b20::getDataF()
{
	return temp_C2F(getDataC());
}

float bs18b20::temp_C2F(float tempC)
{
	return 1.8*tempC+32;
}
