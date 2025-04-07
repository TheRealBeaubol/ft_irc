/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:36:00 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 23:08:33 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	partCommand(Server *server, Client *client, std::vector<std::string> command) {
    
    std::string serverName = std::string(SERVER_NAME);
    std::string msg;
    
    if (command.size() < 2) {
        msg = ":" + serverName + " 461 " + client->getNickName() + " PART :Not enough parameters\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        std::cout << BOLD RED << msg << RESET;
        return ;
    }

    Channel *channel = server->findChannel(command[1]);

    if (!channel) {
        msg = ":" + serverName + " 403 " + client->getNickName() + " " + command[1] + " :No such channel\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        std::cout << BOLD RED << msg << RESET;
        return ;
    }
    if (channel->getClientByName(client->getNickName()) == NULL) {
        msg = ":" + serverName + " 442 " + client->getNickName() + " " + command[1] + " :You're not on that channel\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        std::cout << BOLD RED << msg << RESET;
        return ;
    }

    client->removeChannel(channel);
    channel->eraseClient(client);

    msg = ":" + client->getNickName() + " PART #" + channel->getChannelName() + "\r\n";
    channel->broadcastChannel(msg, NULL);
}