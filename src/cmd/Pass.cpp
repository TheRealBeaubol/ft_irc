/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:31 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 22:29:56 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	passCommand(Server *server, Client *client, std::vector<std::string> commands) {

	if (client->getIsLog() == true)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_ALREADYREGISTRED + " " + client->getNickName() + " :You may not reregister\r\n");
	if (commands.size() < 2)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " PASS :Not enough parameters\r\n");
	std::string password = commands[1];

	if (password != server->getPassword()) {

		SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + ERR_PASSWDMISMATCH + " " + client->getNickName() + " :Password incorrect\r\n");
		for (size_t i = 0; i < server->getClients().size(); i++) {
			if (server->getClients()[i] == client) {
				close(client->getClientFd());
				server->removeClient(client);
				return;
			}
		}
		return;
	}
	client->setIsAuth(true);
}
