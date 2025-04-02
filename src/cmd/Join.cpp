/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:23 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 18:19:50 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	joinCommand(Server *server, Client *client, std::vector<std::string> commands) {
	
	//Channel *tmpChannel = server->findChannel(commands[1]);
	if (/*the channel is on invite only*/ 1 == 0){

		std::cout << "The channel you want to join is on Invit-only mode!" << std::endl;
		return ;
	}
	/*if (check si il y a pass word si il y est attendre le pass word et  1 == 0){
		
		if (!commands[2]){

			std::cout << "Need 1 more param: need password to join this channel" << std::endl;
			return ;
		}
		if(tmpChannel->_password != commands[2]){

				std::cout << "Incorrect passowrd for channel!" << std::endl;
				return ;
		}
	}*/

	size_t 	channelSize = server->getChannel().size();

	for (size_t i = 0; i < channelSize + 1; i++)
	{
		std::string	msg = ":" + client->getNickName() + " JOIN :#" + commands[1] + "\r\n";
	
		if ( i < channelSize)
		{
			std::cout << LIGHTMAGENTA << "Channel [ " << server->getChannel()[i]->getChannelName() << " ] exists, user joined it" << RESET << std::endl;
			if ( server->getChannel()[i]->getChannelName() == commands[1])
			{
				server->getChannel()[i]->addClient(client);
				server->sendMessage(client->getClientSocket(), msg.c_str());
				return ;			
			}
		}
		else if (i == channelSize)
		{
			std::cout << LIGHTMAGENTA << "The [ " << commands[1] << " ] channel doesn't exists, it will be created" << std::endl;
			Channel *channel = new Channel(commands[1]);
			server->addChannel(channel);
			server->getChannel()[i]->addClient(client);
			server->sendMessage(client->getClientSocket(), msg.c_str());
			server->getChannel()[i]->showClient();
			return;
		}
	}
}
