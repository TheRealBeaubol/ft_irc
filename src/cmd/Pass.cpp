/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:31 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 21:24:07 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	passCommand(Server *server, Client *client, std::vector<std::string> commands) {

    std::string serverName = std::string(SERVER_NAME);
    std::string msg;

    if (client->getIsLog() == true) {
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 462 " + client->getNickName() + " :You may not reregister\r\n");
    }
    if (commands.size() < 2) {
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 461 " + client->getNickName() + " PASS :Not enough parameters\r\n");
    }
    std::string password = commands[1];

    if (password != server->getPassword()) {

        SEND_MESSAGE(":" + serverName + " 464 " + client->getNickName() + " :Password incorrect\r\n");
        for (size_t i = 0; i < server->getClients().size(); i++) {
            if (server->getClients()[i] == client) {
                server->removePollFd(server->getPollFds()[i]);
                close(client->getClientSocket());
                server->removeClient(client);
                return;
            }
        }
        return;
    }
    
    client->setIsAuth(true);
}