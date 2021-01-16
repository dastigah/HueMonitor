#include <iostream>

#include "cmdparser.hpp"
#include "HueConnectionAPI.hpp"
#include "HueHTTPConnection.hpp"
#include "HueLightMonitor.hpp"

void configureParser(cli::Parser & parser) {
	parser.set_required<std::string>("i", "ip_address","IP Address to connect to the bridge");
	parser.set_optional<int>("p", "port", 8080, "Port number to connect to");
	parser.set_required<std::string>("u", "user", "Authorized user to connect to bridge"); 
	parser.set_optional<unsigned int>("r", "refresh_rate", 1000, "Rate for which the program checks for updates. This will be in milliseconds");
}

int main(int argc, char * argv[]) {
	cli::Parser parser(argc, argv);
	configureParser(parser);
	parser.run_and_exit_if_error();

	std::string ipAddress = parser.get<std::string>("i");
	int port = parser.get<int>("p");
	std::string user = parser.get<std::string>("u");
	unsigned int refreshRate = parser.get<unsigned int>("r");

	try{
		std::shared_ptr<HueConnectionAPI> httpConn = std::make_shared<HueHTTPConnection>(ipAddress, port);	
		HueLightMonitor monitor(httpConn, user, refreshRate);

		monitor.start();
	}
	catch (httplib::Error & e) {
		if (e == httplib::Error::Connection) std::cout << "Unable to connect to the IP address or port given" << std::endl;
		else if (e == httplib::Error::Read) std::cout << "User given (" << user << ") is not an authorized user" << std::endl;
		else std::cout << "HTTP Error: " << e << std::endl;
	}
	catch (nlohmann::detail::parse_error & e) {
		std::cout << "Unrecognized/Illegal JSON format" << std::endl;
	}

	return 0;
}
