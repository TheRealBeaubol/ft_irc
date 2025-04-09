/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:36:00 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 00:51:40 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	partCommand(Server *server, Client *client, std::vector<std::string> command) {
    
    std::string serverName = std::string(SERVER_NAME);
    std::string msg;
    
    if (command.size() < 2)
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 461 " + client->getNickName() + " PART :Not enough parameters\r\n");

    Channel *channel = server->findChannel(command[1]);

    if (!channel)
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 403 " + client->getNickName() + " " + command[1] + " :No such channel\r\n");
    
    if (channel->getClientByName(client->getNickName()) == NULL)
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 442 " + client->getNickName() + " " + command[1] + " :You're not on that channel\r\n");

    client->removeChannel(channel);
    channel->eraseClient(client);

    msg = ":" + client->getNickName() + " PART #" + channel->getChannelName() + "\r\n";
    channel->broadcastChannel(msg, NULL);

	channel->eraseClient(client);
	if (channel->getClients().size() == 0)
		server->removeChannel(channel);
}