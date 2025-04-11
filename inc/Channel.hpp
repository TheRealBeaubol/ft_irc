#pragma once

#include "Includes.hpp"

class Client;

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

		std::string getTopicAuthor() const;
		void		setTopicAuthor(std::string topicAuthor);

		void		setTopicUserAccess(bool topicUserAccess);
		bool		getTopicUserAccess() const;

		void		setInviteOnly(bool inviteOnly);
		bool		getInviteOnly() const;

		void		setOperator(Client *client, bool isOperator);

		void		setClientLimit(int clientLimit);
		int			getClientLimit() const;

		void		addClient(Client* newClient);
		Client*		getClientByName(std::string name);
		void		setClientParam(Client* client, bool isLogged, bool isOperator);
		bool*		getClientParam(Client* client);
		void		removeClient(Client* indClient);
		
		std::string	getChannelName() const;
		std::map<Client *, bool *>	&getClients();

		void		broadcastChannel(std::string message, Client *sender);

		void setCreationTime(time_t time);
		time_t getCreationTime() const;

	private:

		std::string	_name;
		std::string _password;	// /MODE +k
		std::string	_topic;
		std::string _topicAuthor;
		bool _topicUserAccess;	// /MODE +t
		bool _inviteOnly;		// /MODE +i
		int _clientLimit;		///MODE +l
		time_t _creationTime;

		std::map<Client *,  bool*> _clients; //bool[2] = {logged, operator}
};
