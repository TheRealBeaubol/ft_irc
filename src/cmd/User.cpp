/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:38 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 21:23:30 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void userCommand(Client *client, std::vector<std::string> command) {

	std::string serverName = std::string(SERVER_NAME);
	std::string msg;

	if (client->getIsLog() == true) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 462 " + client->getNickName() + " :You may not reregister\r\n");
	}
	if (command.size() < 2) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 461 " + client->getNickName() + " USER :Not enough parameters\r\n");
	}
	
	client->setUserName(command[1]);

	if (client->getNickName() != "") {
		client->setIsLog(true);
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 001 " + client->getNickName() + " :Welcome to the Internet Relay Chat Network " + client->getNickName() + "!" + client->getUserName() + "@" + serverName + "\r\n");
	}
}