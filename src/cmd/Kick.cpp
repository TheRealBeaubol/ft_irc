/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 16:34:47 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool	verifPriv(Server *server, Client *client, size_t i){
	//std::cout << "i: " << i << std::endl;
	for (std::map<Client *, int>::iterator it = server->getChannel()[i]->getClients().begin(); it != server->getChannel()[i]->getClients().end(); ++i){

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
	for (size_t ite = 0; ite < command.size(); ++ite)
	{ 
		std::cout << "command[" << ite << "] : " << command[ite] << std::endl;
	}
	size_t	i;
	for (i = 0; i < server->getChannel().size(); ++i){
		
		if (server->getChannel()[i]->getChannelName() == command[2])
			break ;
	}
	if (!verifPriv(server, client, i)){

		//pas un op
		return ;
	}

	std::string msg = ":" + client->getNickName() + " KICK #" + server->getChannel()[i]->getChannelName() + " " + command[3] + " :" + command[4];	
	for (std::map<Client *, int>::iterator it = server->getChannel()[i]->getClients().begin(); it != server->getChannel()[i]->getClients().end(); ++it){

		std::cout << "valeur de i: " << i << std::endl;
		std::cout << "message que je send: " << msg << std::endl << "nombre total client: " << server->getClients().size() <<std::endl;
		send(it->first->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << "CACACACACAC" << std::endl;
	}
	std::cout << "LAAAAAAAAAAAAAAAA" << std::endl;
}
