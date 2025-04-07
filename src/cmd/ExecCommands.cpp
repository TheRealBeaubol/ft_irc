/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommands.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:45:39 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 23:07:54 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void executeCommand(Server *server, Client *client, std::vector<std::string> command) {

	std::string serverName = std::string(SERVER_NAME);
	std::string msg;

	std::cout << BOLD CYAN << "Message receive from [" << client->getNickName() << "] :" << std::endl << RESET << "	";
	for (size_t i = 0; i < command.size(); i++) {
		std::cout << CYAN << command[i] << " ";
	}
	std::cout << std::endl << RESET;
	std::cout << std::endl << BOLD BLUE << "_____________ " << command[0] << " COMMAND _____________" << RESET << std::endl << std::endl;

	if (client->getIsAuth() == true) {

		if (command[0] == "NICK")
				commandNick(server, client, command);

		else if (command[0] == "USER")
			userCommand(client, command);
			
		else if (client->getIsLog() == true)
		{
			if (command[0] == "JOIN")
				joinCommand(server, client, command);
			else if (command[0] == "TOPIC")
				topicCommand(server, client, command);
			else if (command[0] == "KICK")
				commandKick(server, client, command);
			else if (command[0] == "INVITE")
				inviteCommand(server, client, command);
			else if (command[0] == "MODE")
				modeCommand(server, client, command);
			else if (command[0] == "PRIVMSG")
				prvmsgCommand(server, client, command);
			else if (command[0] == "PART")
				partCommand(server, client, command);
			else {
				msg = ":" + serverName + " 421 " + client->getNickName() + " " + command[0] + " :Unknown command\r\n";
				send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
				close(client->getClientSocket());
				client->setIsAuth(false);
				client->setIsLog(false);
				server->removeClient(client);
			}
		}
	}
	else if (command[0] == "PASS")
		passCommand(server, client, command);	
	else if (command[0] != "CAP") {
        msg = ":" + serverName + " 421 " + client->getNickName() + " " + command[0] + " :Unknown command\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		close(client->getClientSocket());
		client->setIsAuth(false);
		client->setIsLog(false);
		server->removeClient(client);
	}
	
	std::cout << BOLD BLUE << "_________________________________________" << std::endl << std::endl << std::endl << RESET;
}
