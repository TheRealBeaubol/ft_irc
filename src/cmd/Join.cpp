/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:23 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 23:58:29 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	joinCommand(Server *server, Client *client, std::vector<std::string> commands) {
	
	std::string	msg_R;
	std::string	serverName = std::string(SERVER_NAME);
	if (commands.size() < 2)
	{
		msg_R = serverName + " 461 " + client->getNickName();
		send(client->getClientSocket(), msg_R.c_str(), msg_R.size(), 0);
		std::cout << BOLD RED << msg_R << RESET;
		return ;
	}
	size_t 	channelSize = server->getChannel().size();
	Channel *tmpChannel = server->findChannel("#" + commands[1]);

	std::string	msg = ":" + client->getNickName() + " JOIN :#" + commands[1] + "\r\n";
	if (tmpChannel != NULL)
	{
		if (tmpChannel->getClients().size() > (unsigned long) tmpChannel->getClientLimit())
		{
			msg_R = serverName + " 471 " + client->getNickName();
			send(client->getClientSocket(), msg_R.c_str(), msg_R.size(), 0);
			std::cout << BOLD RED << msg_R << RESET;
			return ;
		}
		if (tmpChannel->getClientByName(client->getNickName()) != NULL)
		{
			msg_R = serverName + " 443 " + client->getNickName();
			send(client->getClientSocket(), msg_R.c_str(), msg_R.size(), 0);
			std::cout << BOLD RED << msg_R << RESET;
			return ;
		}
		if (tmpChannel->getInviteOnly() == true && tmpChannel->getClientByName(client->getNickName()) && tmpChannel->getClients()[client][0] == false){
			msg_R = serverName + " 473 " + client->getNickName();
			send(client->getClientSocket(), msg_R.c_str(), msg_R.size(), 0);
			std::cout << BOLD RED << msg_R << RESET;
			return ;
		}
		if (tmpChannel->getPassword().empty() == false){
		
			msg_R = serverName + " 475 " + client->getNickName();
			if (commands.size() < 3){
				send(client->getClientSocket(), msg_R.c_str(), msg_R.size(), 0);
				std::cout << BOLD RED << msg_R << RESET;
				return ;
			}
			if(tmpChannel->getPassword() != commands[2]){
				send(client->getClientSocket(), msg_R.c_str(), msg_R.size(), 0);
				std::cout << BOLD RED << msg_R << RESET;
				return ;
			}
		}
		std::cout << LIGHTMAGENTA << "Channel [ " << tmpChannel->getChannelName() << " ] exists, user joined it" << RESET << std::endl;
		tmpChannel->addClient(client);
		tmpChannel->getClients()[client][1] = true;
		server->sendMessage(client->getClientSocket(), msg.c_str());
		msg_R = ":server 332 " + client->getNickName() + " #" + tmpChannel->getChannelName() + " :" + tmpChannel->getTopic() + "\r\n";
		send(client->getClientSocket(), msg_R.c_str(), msg_R.size(), 0);
	}
	else
	{
		std::cout << LIGHTMAGENTA << "The [ " << commands[1] << " ] channel doesn't exists, it will be created" << std::endl;
		Channel *channel = new Channel(commands[1]);
		server->addChannel(channel);
		server->getChannel()[channelSize]->addClient(client);
		server->sendMessage(client->getClientSocket(), msg.c_str());
		server->getChannel()[channelSize]->showClient();
		return;
	}
}
