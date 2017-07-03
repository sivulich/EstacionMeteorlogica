#include "GPIO.h"
#include <fstream>



GPIO::GPIO(string pin)
{
	this->pinNumber = pin;
	exportPin();		//export dentro del constructor o como metodo publico?
						//setear input o output dentro del constructor??

}


GPIO::~GPIO()
{
	unexportPin();		//unexport dentro del destructor o como metodo publico?
}

bool GPIO::setDirection(direction_t direction)
{
	bool status;
	string path = "/sys/class/gpio/gpio" + this->pinNumber + "/direction";
	ofstream file(path.c_str());			//abrimos el archivo (c_str() porque file() recibe un puntero a char)
	if (file.is_open() == true)				//si se pudo leer el archivo...
	{
		status = true;
		if (direction == IN)				//escribimos out o in
			file << "in";
		else if (direction == OUT)
			file << "out";

		file.close();
	}
	else
		status = false;

	return status;
}

bool GPIO::writeValue(value_t value)
{
	bool status;
	string path = "/sys/class/gpio/gpio" + this->pinNumber + "/value";
	ofstream file(path.c_str());					//abrimos el archivo (c_str() porque file() recibe un puntero a char)
	if (file.is_open() == true)
	{
		status = true;								//escribimos en el archivo lo que se envio como parametro
		if (value == ZERO)
			file << "0";
		else if (value == ONE)						//escribimos 1 o 0
			file << "1";

		file.close();
	}
	else
		status = false;

	return status;
}

value_t GPIO::readValue(void)
{
	value_t value;
	string path = "/sys/class/gpio/gpio" + this->pinNumber + "/value";
	ifstream file(path.c_str());						//abrimos el archivo (c_str() porque file() recibe un puntero a char)
	if (file.is_open() == true)
	{
		string testValue;
		file >> testValue;
		if (testValue == "1")							//leemos 1 o 0
			value = ONE;
		else if (testValue == "0")
			value = ZERO;

		file.close();
	}
	else
		value = ERROR;

	return value;
}

string GPIO::getPinNumber(void)
{
	return this->pinNumber;
}

bool GPIO::exportPin(void)
{
	bool status;
	string path = "/sys/class/gpio/export";
	ofstream file(path.c_str());				//abrimos el archivo (c_str() porque file() recibe un puntero a char)
	if (file.is_open() == true)
	{
		status = true;
		file << this->pinNumber;				//escribimos el numero del pin
		file.close();
	}
	else
		status = false;

	return status;
}

bool GPIO::unexportPin(void)
{
	bool status;
	string path = "/sys/class/gpio/unexport";
	ofstream file(path.c_str());				//abrimos el archivo (c_str() porque file() recibe un puntero a char)
	if (file.is_open() == true)
	{
		status = true;
		file << this->pinNumber;				//escribimos el numero del pin
		file.close();
	}
	else
		status = false;

	return status;
}
