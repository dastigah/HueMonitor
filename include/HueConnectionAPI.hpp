#ifndef __HUE_CONNECTION_API__
#define __HUE_CONNECTION_API__

#include <string>

/**
 * Abstract class to act as API to get light status
 */
class HueConnectionAPI{
		
	public:
		
		/**
 		* Returns a json formatted string of all lights
 		* @param user 	authorized user id to connect to bridge
 		* @return		json formatted string of all lights
 		*/	  	
		virtual std::string getAllLights(std::string user) = 0;
		
		/**
 		* Returns a json formatted string of a light based on the light id
 		* @param user		authorized user id to connect to bridge 
 		* @param id			light id
 		* @return 			json formatted string of light with given id
 		*/
		virtual std::string getLightState(std::string user, std::string id) = 0;
		
};
#endif
