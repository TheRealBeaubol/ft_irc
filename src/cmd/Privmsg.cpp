/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:20 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 03:20:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool	checkInChannel(Channel *channel, Client *client){

	for (std::map<Client *, int>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); ++it){

		if (it->first->getClientSocket() == client->getClientSocket())
			return (1);
	}		
	return (0);
}

void	msgChannel(Server *server, Client *client, std::vector<std::string> command){
	Channel *tmpChannel = server->findChannel(command[1]);
	if (!tmpChannel)
	{
		std::cout << "channel doesn't exist!" << std::endl;
		return ;
	}
	if (!checkInChannel(tmpChannel, client))
	{
		std::cout << "Senter is not in the Channel!" << std::cout;
		return ;
	}
	std::string	msg = ":" + client->getNickName() + " PRIVMSG #" + tmpChannel->getChannelName() + " :" + command[2] + "\r\n"; 
	tmpChannel->broadcastChannel(msg, NULL);
}

void	msgUser(Server *server, Client *client, std::vector<std::string> command){

	Client *tmpClient = server->findClient(command[1]);
	if (!tmpClient)
	{
		std::cout << "User doesn't exist!" << std::endl;
		return ;
	}
	if (!tmpClient->getIsAuth())
	{
		std::cout << "the user is not found!" << std::endl;
		return ;
	}
	std::string	msg = ":" + client->getNickName() + " PRIVMSG " + tmpClient->getNickName() + " :" + command[2] + "\r\n"; 
	send(tmpClient->getClientSocket(), msg.c_str(), msg.length(), 0);
}
void	prvmsgCommand(Server *server, Client *client, std::vector<std::string>	command){

	if (command[1][0] == '#')
		msgChannel(server, client, command);
	else
		msgUser(server, client, command);
}
