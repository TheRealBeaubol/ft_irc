/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:23 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 00:43:10 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	joinCommand(Server *server, Client *client, std::vector<std::string> commands) {
		
	commands[1].erase(std::remove(commands[1].begin(), commands[1].end(), '\n'), commands[1].end()); //faut vraiment remplacer cette ligne ptdrrrrr
	commands[1].erase(std::remove(commands[1].begin(), commands[1].end(), '\r'), commands[1].end()); //faut vraiment remplacer cette ligne ptdrrrrr
	
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
			}
		}
		else if (i == channelSize)
		{
			std::cout << LIGHTMAGENTA << "The [ " << commands[1] << " ] channel doesn't exists, it will be created" << std::endl;
			Channel *channel = new Channel(commands[1]);
			server->addChannel(channel);
			server->getChannel()[i]->addClient(client);
			server->sendMessage(client->getClientSocket(), msg.c_str());
			return;
		}
	}
}
