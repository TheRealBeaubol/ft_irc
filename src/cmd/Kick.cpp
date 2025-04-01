/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 17:22:16 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool	verifPriv(Client *client, Channel *channel){
	//std::cout << "i: " << i << std::endl;
	//for (std::map<Client *, int>::iterator it = server->getChannel()[i]->getClients().begin(); it != server->getChannel()[i]->getClients().end(); ++i){
	for (std::map<Client *, int>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); ++it){

		if (it->first->getClientSocket() == client->getClientSocket())
		{
			if (it->second != 1)
				return (0);
			return (1);
		}
	}
	return (1);
}

void	commandKick(Server *server, Client *client, std::vector<std::string> command){

	/*if (Verif syntaxe command){

		//probleme message
		return ;
	}*/
	command[3].erase(std::remove(command[3].begin(), command[3].end(), ':'), command[3].end());
	for (size_t ite = 0; ite < command.size(); ++ite)
	{ 
		std::cout << "command[" << ite << "] : " << command[ite] << std::endl;
	}
	Channel *tmpChannel = server->findChannel(command[2]);
	if (!verifPriv(client, tmpChannel)){

		//pas un op
		return ;
	}

	std::string msg = ":" + client->getNickName() + " KICK " + command[2] + " " + command[3] + " :" + command[4];	
	//for (std::map<Client *, int>::iterator it = server->getChannel()[i]->getClients().begin(); it != server->getChannel()[i]->getClients().end(); ++it){
	std::cout << "message que je send: " << msg << std::endl << "nombre total client: " << server->getClients().size() <<std::endl;
	tmpChannel->broadcastMessage(msg, client);
	/*for (std::map<Client *, int>::iterator it = tmpChannel->getClients().begin(); it != tmpChannel->getClients().end(); ++it){

		send(it->first->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << "CACACACACAC" << std::endl;
	}*/
	std::cout << "LAAAAAAAAAAAAAAAA" << std::endl;
}
