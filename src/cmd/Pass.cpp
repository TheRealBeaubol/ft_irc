/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:31 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 20:38:32 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include <string>

void	passCommand(Server *server, Client *client, std::vector<std::string> commands) {

    std::string password = commands[1];

    if (password == server->getPassword())
    {
        client->setIsAuth(true);
        std::cout << LIGHTMAGENTA << "Password accepted" << RESET << std::endl;
    }
    else
    {
        std::string msg;
        msg = ":" + std::string(SERVER_NAME) + " 464 " + client->getNickName() + " :Password incorrect\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        close(client->getClientSocket());
        client->setIsAuth(false);
        client->setIsLog(false);
        server->removeClient(client);
        std::cout << LIGHTMAGENTA << "Password incorrect" << RESET << std::endl;
    }
}