#ifndef __HUE_LIGHT_MONITOR__
#define __HUE_LIGHT_MONITOR__

#include <unordered_map>
#include <string>

#include "HueConnectionAPI.hpp"
#include "HueHTTPConnection.hpp"
#include "json.hpp"

#define MAX_BRIGHTNESS 254
#define MIN_BRIGHTNESS 0

#define NUM_INDENTS 2 

#define NUM_CONNECTION_RETRIES 5

using json = nlohmann::json;


/**
 * Class Monitors the state of the lights tied to a certain ip/port and specific user
 */
class HueLightMonitor{
		std::shared_ptr<HueConnectionAPI> httpConn;
		std::string user;
		unsigned int refreshRate;
		json lightMap; 

		/**
		* Returns a json object that is trimmed to include only brightness, id, on state, and name
		* @param lightRequest	Original json light request
		* @param id			Light ID
		* @return				json object with trimmed data mentioned above
		*/ 	 
		json trimLightRequest(const std::string & lightRequest, const std::string & id);	
		
		/**
 		* Returns an array of changes for a give light if the brightness or on state changes
 		* @param request	json request for a light
 		* @return			json object that is of type json::array 
 		*/ 	
		json getChanges(json & request);
		
		/**
		 * Returns brightness as a percentage
		 * @param brightValue 	Raw brightness value
		 * @return 				Brightness percentage
		 */
		unsigned int getBrightnessPercent(int brightValue);
		
	public:
		HueLightMonitor(std::shared_ptr<HueConnectionAPI> _httpConn, std::string _user, unsigned int _refreshRate) : httpConn(_httpConn), user(_user), refreshRate(_refreshRate) {}
		
		~HueLightMonitor() {}

		/**
		 * Starts the program to monitor the status of the lights
		 */	
		void start();
};
#endif

