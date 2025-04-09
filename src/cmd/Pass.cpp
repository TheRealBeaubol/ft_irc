/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:31 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 01:11:31 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include <string>

void	passCommand(Server *server, Client *client, std::vector<std::string> commands) {

    std::string serverName = std::string(SERVER_NAME);
    std::string msg;

    if (client->getIsLog() == true)
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 462 " + client->getNickName() + " :You may not reregister\r\n");

    if (commands.size() < 2)
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 461 " + client->getNickName() + " PASS :Not enough parameters\r\n");

    std::string password = commands[1];

    if (password != server->getPassword()) {

        close(client->getClientSocket());
        client->setIsAuth(false);
        client->setIsLog(false);
        server->removeClient(client);
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 464 " + client->getNickName() + " :Password incorrect\r\n");
    }
    
    client->setIsAuth(true);
}