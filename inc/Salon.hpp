#pragma once

#include "Client.hpp"
#include <map>

class Salon
{
	public:
		Salon();
		Salon(std::string name);
		~Salon();

		void	addClient(Client* newClient);
		void	eraseClient(Client* indClient);
		void	showClient();
		
		std::string	getSalonName() const;
	private:
		std::string	_name;
		std::map<Client *, int> _clients;
};

Salon::Salon(){}

Salon::Salon(std::string name): _name(name) {}

Salon::~Salon(){}

void	Salon::addClient(Client *newClient){

	if (_clients.size() == 0)
		_clients[newClient] = 1;
	else
		_clients[newClient] = 0;
}

#define IRC_AUTO	__auto_type

void	Salon::showClient(){
	
	std::cout << "show client command call!" << std::endl;
	std::cout << "Size of Client for Salon " << _name << " :" << _clients.size() << std::endl;
	for (IRC_AUTO it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second == 1)
	    	std::cout << "Client : " << it->first->get_nick_name() << ", he's an operator!" << std::endl;
		else
			std::cout << "Client : " << it->first->get_nick_name() << ", he's a simple user!" << std::endl;
	}
}

void	Salon::eraseClient(Client *indClient){

	_clients.erase(indClient);
}

std::string	Salon::getSalonName() const{ return(_name); }
