/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:17:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 15:43:17 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

Channel::Channel(){}

Channel::Channel(std::string name): _name(name), _password(""), _topic(""), _topicUserAccess(0), _inviteOnly(0), _clientLimit(-1) {}

Channel::~Channel(){}

void	Channel::addClient(Client *newClient){

	if (_clients.size() == 0) {
		_clients[newClient] = new bool[3];  // Allocation dynamique
		_clients[newClient][0] = false;
		_clients[newClient][1] = false;
		_clients[newClient][2] = true;
	}
	else {
		bool array[3] = {false, false, false};
		_clients[newClient] = array;
	}
}

Client*	Channel::getClientByName(std::string name)
{
	for (std::map<Client *,  bool*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->first->getNickName() == name)
			return it->first;
	}
	return NULL;
}

void	Channel::setClientParam(Client* client, bool *param)
{
	for ( int i = 0 ; i < 3 ; i++)
	{
		if (param[i] == true || param[i] == false)
			_clients[client][i] = param[i];
	}
}

bool*	Channel::getClientParam(Client* client)
{
	for (std::map<Client *,  bool*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->first == client)
			return it->second;
	}
	return NULL;
}

void	Channel::showClient(){
	
	std::cout << "Size of Client for Channel " << _name << ": " << _clients.size() << std::endl;
	for (std::map<Client *,  bool*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second[2] == true)
		{
			std::cout << "Client : " << it->first->getNickName() << ", he's an operator!" << std::endl;
		}
		else if (it->second[2] == false){
			std::cout << "Client : " << it->first->getNickName() << ", he's a simple user!" << std::endl;
        }
		else
			std::cout << "Not define" << std::endl;
		
    }
}

void	Channel::broadcastChannel(std::string message, Client *sender){
	
	for (std::map<Client *, bool *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->first != sender)
			send(it->first->getClientSocket(), message.c_str(), message.size(), 0);
	}
}

void	Channel::eraseClient(Client *indClient) { _clients.erase(indClient); }

std::string	Channel::getChannelName() const{ return(_name); }

std::string Channel::getTopic() const { return(_topic); }
void	Channel::setTopic(std::string topic) { _topic = topic; }

std::string Channel::getTopicAuthor() const { return(_topicAuthor); }
void	Channel::setTopicAuthor(std::string topicAuthor) { _topicAuthor = topicAuthor; }
std::map<Client *, bool *>	Channel::getClients() const { return(_clients); }
