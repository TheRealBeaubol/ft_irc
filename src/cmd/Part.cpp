/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:36:00 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 19:38:30 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	partCommand(Server *server, Client *client, std::vector<std::string> command) {
    
    std::string serverName = std::string(SERVER_NAME);
    
    if (command.size() < 2) {
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 461 " + client->getNickName() + " PART :Not enough parameters\r\n");
    }
    
    std::vector<std::string> channelNames;
    channelNames = split(command[1], ',');

    for (size_t i = 0; i < channelNames.size(); i++) {

        Channel *channel = server->getChannelByName(channelNames[i]);

        if (!channel) {
            SEND_MESSAGE(":" + serverName + " 403 " + client->getNickName() + " " + channelNames[i] + " :No such channel\r\n");
        }    
        else if (channel->getClientByName(client->getNickName()) == NULL) {
            SEND_MESSAGE(":" + serverName + " 442 " + client->getNickName() + " " + channelNames[i] + " :You're not on that channel\r\n");
        }
        else {
            channel->broadcastChannel(":" + client->getNickName() + " PART " + channel->getChannelName() + "\r\n", NULL);

            channel->removeClient(client);
            if (channel->getClients().size() == 0)
                server->removeChannel(channel);
        }
    }
}