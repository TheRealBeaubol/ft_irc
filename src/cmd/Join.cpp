/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:23 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 22:40:19 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	joinCommand(Server *server, Client *client, std::vector<std::string> commands) {
	
	std::string	msg_ERR;
	std::string	serverName = std::string(SERVER_NAME);
	if (commands.size() < 2)
	{
		std::cout << "Need more param!" << std::endl;
		msg_ERR = serverName + " 461 " + client->getNickName();
		send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
		std::cout << BOLD RED << msg_ERR << RESET;
		return ;
	}
	size_t 	channelSize = server->getChannel().size();
	Channel *tmpChannel = server->findChannel("#" + commands[1]);

	std::string	msg = ":" + client->getNickName() + " JOIN :#" + commands[1] + "\r\n";
	if (tmpChannel != NULL)
	{
		if (tmpChannel->getClients().size() > (unsigned long) tmpChannel->getClientLimit())
		{
			std::cout << "limit of client on channel has been reach, You can't join it" << std::endl;
			msg_ERR = serverName + " 471 " + client->getNickName();
			send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
			std::cout << BOLD RED << msg_ERR << RESET;
			return ;
		}
		if (tmpChannel->getClientByName(client->getNickName()) != NULL)
		{
			std::cout << "User already in Channel" << std::endl;
			msg_ERR = serverName + " 443 " + client->getNickName();
			send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
			std::cout << BOLD RED << msg_ERR << RESET;
			return ;
		}
		if (tmpChannel->getInviteOnly() == true && tmpChannel->getClients()[client][0] == false){
			std::cout << "The channel you want to join is on Invit-only mode!" << std::endl;
			msg_ERR = serverName + " 473 " + client->getNickName();
			send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
			std::cout << BOLD RED << msg_ERR << RESET;
			return ;
		}
		if (tmpChannel->getPassword().empty() == false){
		
			if (commands.size() < 3){
				std::cout << "Need 1 more param: need password to join this channel" << std::endl;
				return ;
			}
			if(tmpChannel->getPassword() != commands[2]){
				std::cout << "Incorrect passowrd for channel!" << std::endl;
				return ;
			}
			msg_ERR = serverName + " 475 " + client->getNickName();
			send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
			std::cout << BOLD RED << msg_ERR << RESET;
		}
		std::cout << LIGHTMAGENTA << "Channel [ " << tmpChannel->getChannelName() << " ] exists, user joined it" << RESET << std::endl;
		tmpChannel->addClient(client);
		server->sendMessage(client->getClientSocket(), msg.c_str());
		
	}
	else
	{
		std::cout << "In creat channel" << std::endl;	
		std::cout << LIGHTMAGENTA << "The [ " << commands[1] << " ] channel doesn't exists, it will be created" << std::endl;
		Channel *channel = new Channel(commands[1]);
		server->addChannel(channel);
		std::cout << "Channel size: " << channelSize << std::endl;
		server->getChannel()[channelSize]->addClient(client);
		server->sendMessage(client->getClientSocket(), msg.c_str());
		server->getChannel()[channelSize]->showClient();
		return;
	}
}
