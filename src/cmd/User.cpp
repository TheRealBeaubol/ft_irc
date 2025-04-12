/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:38 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 22:31:03 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void userCommand(Client *client, std::vector<std::string> command) {

	if (client->getIsLog() == true)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_ALREADYREGISTRED + " " + client->getNickName() + " :You may not reregister\r\n");
	if (command.size() < 2)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " USER :Not enough parameters\r\n");
	
	client->setUserName(command[1]);

	if (client->getNickName() != "") {
		client->setIsLog(true);
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + RPL_WELCOME + " " + client->getNickName() + " :Welcome to the Internet Relay Chat Network " + client->getNickName() + "!" + client->getUserName() + "@" + std::string(SERVER_NAME) + "\r\n");
	}
}