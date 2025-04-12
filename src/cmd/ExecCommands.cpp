/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommands.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:45:39 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 20:41:20 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void executeCommand(Server *server, Client *client, std::vector<std::string> command) {

	std::string serverName = std::string(SERVER_NAME);
	std::string msg;
	
	std::cout << BOLD UNDERLINE LIGHTMAGENTA << "Client " << client->getNickName() << " sent" << RESET BOLD LIGHTMAGENTA << " : " << RESET;
	for (size_t i = 0; i < command.size(); i++)
		std::cout << CYAN << command[i] << " ";
	std::cout << RESET << std::endl << std::endl;

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
			}
		}
	}
	else if (command[0] == "PASS")
		passCommand(server, client, command);	
	else if (command[0] != "CAP") {
		close(client->getClientSocket());
		server->removeClient(client);
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 421 " + client->getNickName() + " " + command[0] + " :Unknown command\r\n");
	}
}
