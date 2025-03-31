#pragma once

#include "Client.hpp"
#include <map>

class Channel
{
	public:
		Channel();
		Channel(std::string name);
		~Channel();

		void	addClient(Client* newClient);
		void	eraseClient(Client* indClient);
		void	showClient();
		
		std::string	getChannelName() const;

	private:
		std::string	_name;
		std::map<Client *, int> _clients;
};