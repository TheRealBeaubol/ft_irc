#pragma once

#include "Client.hpp"
#include <map>

class Salon
{
	public:
		Salon();
		Salon(std::string name);
		~Salon();

		void	addClient(std::map<Client *, int> _clients, Client* newClient);
		void	eraseClient(std::map<Client *, int> _clients, Client* indClient);
		void	showClient(std::map<Client *, int> _clients);
	private:
		std::string	_name;
		std::map<Client *, int> _clients;
};

Salon::Salon(){}

Salon::Salon(std::string name): _name(name) {}

Salon::~Salon(){}

void	Salon::addClient(std::map<Client *, int> _clients, Client *newClient){

	if (_clients.size() == 0)
		_clients[newClient] = 1;
	else
		_clients[newClient] = 0;
}

void	Salon::showClient(std::map<Client *, int> _clients){
	
	for (const auto& pair : _clients) {
		if (pair.second == 1)
	    	std::cout << "Client : " << pair.first->get_nick_name() << ", he's an operator!" << std::endl;
		else
			std::cout << "Client : " << pair.first->get_nick_name() << ", he's a simple user!" << std::endl;
	}
}

void	Salon::eraseClient(std::map<Client *, int> _clients, Client *indClient){

	_clients.erase(indClient);
}
