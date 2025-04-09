/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:31 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 22:55:20 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include <string>

void	passCommand(Server *server, Client *client, std::vector<std::string> commands) {

    std::string serverName = std::string(SERVER_NAME);
    std::string msg;

    if (client->getIsLog() == true) {
        msg = ":" + serverName + " 462 " + client->getNickName() + " :You may not reregister\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        std::cout << BOLD RED << msg << RESET;
        return ;
    }
    if (commands.size() < 2) {
        msg = ":" + serverName + " 461 " + client->getNickName() + " PASS :Not enough parameters\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        std::cout << BOLD RED << msg << RESET;
        return ;
    }

    std::string password = commands[1];

    if (password != server->getPassword()) {

        msg = ":" + serverName + " 464 " + client->getNickName() + " :Password incorrect\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);

        close(client->getClientSocket());
        client->setIsAuth(false);
        client->setIsLog(false);
        server->removeClient(client);
        std::cout << LIGHTMAGENTA << "Password incorrect" << RESET << std::endl;
        return ;
    }
    
    client->setIsAuth(true);
    std::cout << LIGHTMAGENTA << "Password accepted" << RESET << std::endl;
}