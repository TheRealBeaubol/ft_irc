#pragma once

#include "Client.hpp"
#include <map>
#include <string>

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

		std::string	getTopic() const;
		void		setTopic(std::string topic);

		void		broadcastMessage(std::string message, Client *sender);

	private:
		std::string	_name;
		std::string	_topic;
		std::map<Client *, int> _clients;
};