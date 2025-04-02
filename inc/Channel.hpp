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
		std::map<Client *, int>	getClients() const;

		std::string	getTopic() const;
		void		setTopic(std::string topic);

		std::string getTopicAuthor() const;
		void		setTopicAuthor(std::string topicAuthor);

		void		broadcastChannel(std::string message, Client *sender);

	private:
		std::string	_name;
		std::string	_topic;
		std::string _topicAuthor;
		std::map<Client *, int> _clients;
};