#include <iostream>
#include <sstream>

#include "HueHTTPConnection.hpp"

std::unique_ptr<char[]> HueHTTPConnection::getSharedCharPtr(std::ostringstream & request){
	std::string requestStr = request.str();
	std::unique_ptr<char []> pString(new char[requestStr.length() + 1]);
	std::copy(requestStr.c_str(), requestStr.c_str() + requestStr.length() + 1, pString.get());
	return pString;
}

std::string HueHTTPConnection::getAllLights(std::string user){
	std::ostringstream request;
	request << "/api/" << user << "/lights";
	std::unique_ptr<char[]> pString = getSharedCharPtr(request);

	if (auto res = client.Get(pString.get())) {
		if (res->status == 200) return res->body;
 	} else {
   		auto err = res.error();
		throw err;
 	}
	
	return "N/A";
}

std::string HueHTTPConnection::getLightState(std::string user, std::string id){
	std::ostringstream request;
	request << "/api/" << user << "/lights/" << id;	

	std::unique_ptr<char[]> pString = getSharedCharPtr(request);

	if (auto res = client.Get(pString.get())) {
		if (res->status == 200) return res->body;
	}
	else {
		auto err = res.error();	
		throw err;
	}

	return "N/A";
}
