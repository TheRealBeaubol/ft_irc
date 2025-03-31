/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:17:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 00:58:31 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

Channel::Channel(){}

Channel::Channel(std::string name): _name(name) {}

Channel::~Channel(){}

void	Channel::addClient(Client *newClient){

	if (_clients.size() == 0) {
		_clients[newClient] = 1;
    }
    else {
		_clients[newClient] = 0;
    }
}

void	Channel::showClient(){
	
	std::cout << "Size of Client for Channel " << _name << ": " << _clients.size() << std::endl;
	// for (IRC_AUTO it = _clients.begin(); it != _clients.end(); ++it) {
	for (std::map<Client *, int>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second == 1) {
	    	std::cout << "Client : " << it->first->getNickName() << ", he's an operator!" << std::endl;
        }
        else {
			std::cout << "Client : " << it->first->getNickName() << ", he's a simple user!" << std::endl;
        }
    }
}

void	Channel::eraseClient(Client *indClient) { _clients.erase(indClient); }
std::string	Channel::getChannelName() const{ return(_name); }
