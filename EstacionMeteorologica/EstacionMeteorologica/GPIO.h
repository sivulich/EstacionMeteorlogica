#pragma once
#include <string>
using namespace std;

typedef enum { IN, OUT }direction_t;
typedef enum { ZERO, ONE, ERROR }value_t;

class GPIO
{
public:
	GPIO(string pin);		//Recibe el numero del pin a utilizar
	~GPIO();
	bool setDirection(direction_t);		//IN para setear el pin como entrada; OUT para salida
	bool writeValue(value_t);			//ZERO para escribir un 0 en el pin; ONE para escribir un 1
	value_t readValue(void);			//devuelve ZERO, ONE o ERROR si no se pudo leer
	string getPinNumber(void);			//getter para la variable pinNumber
private:
	bool exportPin(void);		//devuelve true si se pudo exportar, o false si no se pudo
	bool unexportPin(void);		//devuelve true si se pudo hacer, o false si no se pudo
	string pinNumber;
};