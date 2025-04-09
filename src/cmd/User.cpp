/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:38 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 22:39:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void userCommand(Client *client, std::vector<std::string> command) {

	std::string serverName = std::string(SERVER_NAME);
	std::string msg;

	if (client->getIsLog() == true)	{
		msg = ":" + serverName + " 462 " + client->getNickName() + " :You may not reregister\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	if (command.size() < 2)	{
		msg = ":" + serverName + " 461 " + client->getNickName() + " USER :Not enough parameters\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}

	client->setUserName(command[1]);

	if (client->getNickName() != "") {
		client->setIsLog(true);
		msg = ":" + serverName + " 001 " + client->getNickName() + " :Welcome to the Internet Relay Chat Network " + client->getNickName() + "!" + client->getUserName() + "@" + serverName + "\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		std::cout << BOLD GREEN << msg << RESET;
	}
}