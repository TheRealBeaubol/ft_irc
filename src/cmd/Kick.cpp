/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 23:26:14 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool	verifPriv(Client *client, Channel *channel){
	for (std::map<Client *, int>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); ++it){

		if (it->first->getClientSocket() == client->getClientSocket())
		{
			if (it->second != 1)
				return (0);
			return (1);
		}
	}
	return (0);
}

void	commandKick(Server *server, Client *client, std::vector<std::string> command){
	
	if (command.size() < 3){

		std::cout << "KICK error: need at least 2 param for KICK" << std::endl;
		return ;
	}
	
	Channel *tmpChannel = server->findChannel(command[1]);
	if (!tmpChannel){

		std::cout << "KICK error: channel doesn't exist!" << std::endl;
		return ;
	}

	if (!verifPriv(client, tmpChannel)){

		std::cout << client->getNickName() << "is not an operator he can't use KICK!" << std::endl;
		return ;
	}

		std::cout << "ICIIIIIII" << std::endl;

	command[2].erase(std::remove(command[2].begin(), command[2].end(), ':'), command[2].end());

	std::string msg = ":" + client->getNickName() + " KICK " + command[1] + " " + command[2] + "\r\n";	
	//std::cout << "message que je send: " << msg << std::endl << "nombre total client: " << server->getClients().size() <<std::endl;
	tmpChannel->broadcastMessage(msg, NULL);
}
