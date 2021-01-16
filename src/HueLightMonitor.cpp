#include <chrono>
#include <thread>

#include "HueLightMonitor.hpp"

unsigned int HueLightMonitor::getBrightnessPercent(int brightValue){
	brightValue = (brightValue < MIN_BRIGHTNESS) ? MIN_BRIGHTNESS : brightValue;
	brightValue = (brightValue > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : brightValue;

	return ceil((static_cast<double>(brightValue) / MAX_BRIGHTNESS) * 100);
}

json HueLightMonitor::trimLightRequest(const std::string & lightRequest, const std::string & id){
	json light = json::parse(lightRequest);
	json trimmedLight;

	trimmedLight["name"] = light["name"];
	trimmedLight["id"] = id;
	trimmedLight["on"] = light["state"]["on"];
	trimmedLight["brightness"] = getBrightnessPercent(light["state"]["bri"]);

	return trimmedLight;
}

json HueLightMonitor::getChanges(json & request){
	json changes;

	for (const auto & obj : request.items()) {
		json light = trimLightRequest(httpConn.get()->getLightState(user, obj.key()), obj.key());	
		
		//Check on/off state
		if (light["on"] != lightMap[obj.key()]["on"]){
			changes.push_back(json::object({
				{"id", light["id"]},
				{"on", light["on"]}
			}));
	
			lightMap[obj.key()]["on"] = light["on"];
		
		}
	
		//check brightness
		if (light["brightness"] != lightMap[obj.key()]["brightness"]) {
			changes.push_back(json::object({
				{"id", light["id"]},
				{"brightness", light["brightness"]}
			}));
	
			lightMap[obj.key()]["brightness"] = light["brightness"];
		}
	}

	return changes;	
}

void HueLightMonitor::start(){
	json request = json::parse(httpConn.get()->getAllLights(user));	
	json lightList;
	int tries = 0;
	
	//print all initial lights	
	for (const auto & obj : request.items()) {
		json light = trimLightRequest(httpConn.get()->getLightState(user, obj.key()), obj.key());
		lightMap[obj.key()] = light;
		lightList.push_back(lightMap[obj.key()]);
	}
	std::cout << lightList.dump(NUM_INDENTS) << std::endl;

	//Loop to get change in light
	while(true){
		try {
			std::this_thread::sleep_for(std::chrono::milliseconds(refreshRate));		
			json request = json::parse(httpConn.get()->getAllLights(user));
			
			json changes = getChanges(request);		
				
			//print changes			
			if (!changes.empty()){
				for (int i = 0; i < changes.size(); i++) {
					std::cout << changes[i].dump(NUM_INDENTS) << std::endl;
				}
			}
				tries = 0;
		}		
		catch (httplib::Error & e){
			if (e == httplib::Error::Connection){
				if (++tries > NUM_CONNECTION_RETRIES) std::rethrow_exception(std::current_exception()); 
				else {
					std::cout << "Lost Connection. Attempting to Reconnect.";
					std::cout << "(" << tries << "/" << NUM_CONNECTION_RETRIES << ")" << std::endl;
				}
			} 
			else std::rethrow_exception(std::current_exception());
		}
	}
}	

