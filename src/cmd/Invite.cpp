/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:32 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 00:12:20 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool	inviteIsInChannel(Channel *channel, std::string	nickname){
	std::cout << "PIPI" << std::endl;
	std::cout << "Nb de client dans le channel: " << channel->getClients().size() << std::endl;
	std::cout << "CACA" << std::endl;
	for (std::map<Client *, int>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); ++it){
	//for (size_t i = 0; i < channel->getClients().size(); ++i){
		//std::cout << "ICIII" << std::endl;
		if (!it->first)
			std::cout << "GOLMON Y'A RIEN ICI TDC!!!" << std::endl; 
		if (it->first->getNickName() == nickname)
			return(1);
		//std::cout << "ICIII" << std::endl;
	}
	//std::cout << "ICIII" << std::endl;
	return (0);
}

bool	checkSenter(Channel *channel, Client *client){

	for (std::map<Client *, int>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); ++it){

		if (it->first->getClientSocket() == client->getClientSocket()){

			if (it->second != 1)
				return (0);
			return (1);
		}
	}
	return (0);
}

bool	checkInviteUser(Server *server, std::string nickname){

	for (size_t i = 0; i < server->getClients().size(); ++i){

		if (server->getClients()[i]->getNickName() == nickname)
			return (1);
	}		
	return (0);
}

void	inviteCommand(Server *server, Client *client, std::vector<std::string> command)
{
	std::cout << "0000000000000000000" << std::endl;
	Channel	*tmpChannel = server->findChannel(command[2]);
	std::cout << "11111111111111111" << std::endl;
	if (!checkSenter(tmpChannel, client)){
		
		std::cout << "client not in channel or dont have permission for this!" << std::endl;
		return ;
	}

	std::cout << "222222222222222222" << std::endl;
	/*if (inviteIsInChannel(tmpChannel, command[1]))
	{
		std::cout << "The user u want to invite is already in the Channel!" << std::endl;
		return ;
	}*/

	/*if (verif connection via getAut)
	{
		std::cout << "the user isn't connected" << std::endl;
		return ;
	}*/
	
	std::cout << "333333333333333333" << std::endl;
	if (!checkInviteUser(server, command[1])){

		std::cout << "The user you want to invite do not exist!" << std::endl;
		return ;
	}

	if (/*!tmpChannel->invite_mod*/ 1 == 0){
	
		std::cout << "The channel is not in 'invite-only'(+i) mode!" << std::endl;
		return ;
		}
	
	std::cout << "44444444444444444" << std::endl;
	Client *tmpUser = server->findClient(command[1]);
	std::cout << "55555555555555555" << std::endl;
	std::string	msg = "You have been invited to join " + tmpChannel->getChannelName() + " by " + client->getNickName() + "\n";
	send(tmpUser->getClientSocket(), msg.c_str(), msg.length(), 0);
}
