
#include "Server.hpp"

int main(int ac, char **av) {
	try {
		if (ac != 2) {
			std::string error = av[0];
			throw std::runtime_error("Usage : " + error + " <port>");
		}
		Server server(av[1], 10);
		server.run();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}