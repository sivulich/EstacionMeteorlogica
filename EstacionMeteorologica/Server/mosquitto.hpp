/**
* Mosquitto C++ Wrapper
* (C) 2017, Felix Niederwanger
* MIT License
*/

#ifndef _MOSQUITTO_HPP_
#define _MOSQUITTO_HPP_

#include <string>
#include <sstream>
#include <mosquitto.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>

using namespace std;
#define QOS 1
class Mosquitto {
private:
	struct mosquitto *mosq;

	volatile bool running;

public:
	Mosquitto();
	virtual ~Mosquitto();

	/** Enable tls
	* @param cacert CaCert file
	* @param certfile Client certificate file. usually a .crt file
	* @param keyfile Client key file, usually a .key file
	*/
	void set_tls(const char* cacert, const char* certfile, const char* keyfile);
	/** Enable or disable insecure TLS connections (No certificate check) */
	void set_tls_insecure(bool enabled);

	/** Set username and password for login */
	void set_username_password(const char* username, const char* password);

	/* Set will*/
	void setWill(const string& topic, const vector<uint8_t>& message, bool retain = false);

	/*Clear will*/
	void clearWIll();

	/** Disconnects the client */
	void close();

	/** Subscribe to the given topic */
	void subscribe(const std::string &topic);

	void publish(const std::string &topic, const vector<uint8_t>&message, bool persitence);

	/**
	* Connects to the given remote host
	* @param remote Remote host where to connect to
	* @param port Remote port. 1883 for unencrypted, 8883 usually for encrypted traffic
	* @param aliveDelay Delay in seconds for pings for the connection to stay alive
	*/
	void connect(const char* remote, const int port = 1883, const int aliveDelay = 30);

	/** Method called when the client is connected */
	void onConnected() {}
	/** Method called then an error occurred */
	virtual void onError(const char* msg) { (void)msg; }
	/** Method called when a new message arrives */
	void onMessage(std::string top, vector<uint8_t>& mes);

	/** Loop through messages. This call usually blocks until the connection is closed
	*@param tryReconnect if true, the client tries to reconnect if an error occurs */
	void loop(const bool tryReconnect = true);

	/*Unsuscribe from topic*/
	void unsubscribe(const string topic);

	/*Returns true if new message arrived*/
	bool newEvent();

	/*Returns the message*/
	vector<uint8_t> getMessage();

	/*Returns the topic of the message*/
	string getTopic();
	/** Cleanup mosquitto library. This call should be called before program termination */
	static void cleanup_library();
};

#endif