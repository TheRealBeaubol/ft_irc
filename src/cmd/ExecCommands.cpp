/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommands.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:45:39 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 02:58:52 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void execute_command(Server *server, Client *client, std::vector<std::string> command) {

	std::cout << BOLD CYAN << "Message receive from [" << client->getNickName() << "] :" << std::endl << RESET << "	";
	for (size_t i = 0; i < command.size(); i++) {
		std::cout << CYAN << command[i] << " ";
	}
	std::cout << std::endl << RESET;
	std::cout << std::endl << BOLD BLUE << "_____________ " << command[0] << " COMMAND _____________" << RESET << std::endl << std::endl;

	if (client->getIsAuth() == true){
		if (command[0] == "JOIN")
		{
			joinCommand(server, client, command);
		}

		else if (command[0] == "PRIVMSG")
		{
			std::cout << "PRIVMSG command" << std::endl;
		}

		else if (command[0] == "QUIT")
		{
			std::cout << "QUIT command" << std::endl;
		}
	}

	if (command[0] == "PASS")
	{
		passCommand(server, client, command);
	}

	else if (command[0] == "NICK")
    {
		commandNick(server, client, command);
	}

	else if (command[0] == "USER")
	{
		userCommand(client, command);
	}

	else
	{
		std::cout << RED << "Commande inconnue (" << command[0] << ")" << std::endl << RESET;
	}
	std::cout << BOLD BLUE << "_________________________________________" << std::endl << std::endl << RESET;
	std::cout << std::endl;
}

