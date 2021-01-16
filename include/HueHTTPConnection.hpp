#ifndef __HUE_HTTP_CONNECTION__
#define __HUE_HTTP_CONNECTION__

#include <memory>
#include <string>

#include "httplib.h"
#include "HueConnectionAPI.hpp"

class HueHTTPConnection : public HueConnectionAPI{
	httplib::Client client; 
	
	/*
 	* Returns a unique pointer to a char *
 	* @param request 	stringstream containing API call
 	* @return			unique pointer to a char * that represents the API call
 	*/ 	  	
	std::unique_ptr<char[]> getSharedCharPtr(std::ostringstream & request);

	public:
		HueHTTPConnection(std::string _ipAddress, int _port) : client(_ipAddress, _port) {}
		
		~HueHTTPConnection() {}
	
		std::string getAllLights(std::string user);

		std::string getLightState(std::string user, std::string id);		

};

#endif 
