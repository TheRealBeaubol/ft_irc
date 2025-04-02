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

		void		addClient(Client* newClient);
		Client*		getClientByName(std::string name);
		void		setClientParam(Client* client, bool *param);
		bool*		getClientParam(Client* client);
		void		eraseClient(Client* indClient);
		void		showClient();
		
		std::string	getChannelName() const;
		std::map<Client *, bool *>	getClients() const;

		std::string	getTopic() const;
		void		setTopic(std::string topic);

		std::string getTopicAuthor() const;
		void		setTopicAuthor(std::string topicAuthor);

		void		broadcastChannel(std::string message, Client *sender);

		bool		getTopicUserAccess() const;

	private:

		std::string	_name;
		std::string _password;	// /MODE +k
		std::string	_topic;
		std::string _topicAuthor;
		bool _topicUserAccess;	// /MODE +t
		bool _inviteOnly;		// /MODE +i
		int _clientLimit;		///MODE +l

		std::map<Client *,  bool*> _clients; //bool[3] = {invited, logged, operator}
};
