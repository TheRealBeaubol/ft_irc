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

		void		setName(std::string name);
		std::string	getName() const;

		void		setPassword(std::string password);
		std::string	getPassword() const;
		
		void		setTopic(std::string topic);
		std::string	getTopic() const;

		void		setTopicUserAccess(bool topicUserAccess);
		bool		getTopicUserAccess() const;

		void		setInviteOnly(bool inviteOnly);
		bool		getInviteOnly() const;

		void		setClientLimit(int clientLimit);
		int			getClientLimit() const;

		void		addClient(Client* newClient);
		Client*		getClientByName(std::string name);
		void		setClientParam(Client* client, bool *param);
		bool*		getClientParam(Client* client);
		void		eraseClient(Client* indClient);
		void		showClient();

		void		broadcastMessage(std::string message, Client *sender);

	private:

		std::string	_name;
		std::string _password;	// /MODE +k
		std::string	_topic;
		bool _topicUserAccess;	// /MODE +t
		bool _inviteOnly;		// /MODE +i
		int _clientLimit;		///MODE +l

		std::map<Client *,  bool*> _clients; //bool[3] = {invited, logged, operator}
};
