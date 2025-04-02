/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommands.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:45:39 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 15:43:37 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void executeCommand(Server *server, Client *client, std::vector<std::string> command) {

	std::cout << BOLD CYAN << "Message receive from [" << client->getNickName() << "] :" << std::endl << RESET << "	";
	for (size_t i = 0; i < command.size(); i++) {
		std::cout << CYAN << command[i] << " ";
	}
	std::cout << std::endl << RESET;
	std::cout << std::endl << BOLD BLUE << "_____________ " << command[0] << " COMMAND _____________" << RESET << std::endl << std::endl;

	if (client->getIsAuth() == true && (command[0] != "PASS" && command[0] != "NICK" && command[0] != "USER")) {

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

		else
			std::cout << RED << "Commande inconnue (" << command[0] << ")" << std::endl << RESET;

		std::cout << BOLD BLUE << "_________________________________________" << std::endl << std::endl  << std::endl << RESET;
		return;
	}

	if (command[0] == "PASS")
		passCommand(server, client, command);

	else if (command[0] == "NICK")
		commandNick(server, client, command);

	else if (command[0] == "USER")
		userCommand(client, command);

	else
		std::cout << RED << "Commande inconnue (" << command[0] << ")" << std::endl << RESET;

	std::cout << BOLD BLUE << "_________________________________________" << std::endl << std::endl << std::endl << RESET;
}

/*
	if (! logged && )
		if commande == pass
			command_pass

	else if (nick == "")
		if (commande == nick)
			command_nick
	
	else if (user_name == "")
		if (commande == user)
			command_user

	else if (command == JOIN || PRIVMSG || ...)
		do_cmd

	else
		cout unknown command;

*/