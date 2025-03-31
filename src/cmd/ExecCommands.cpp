/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommands.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:45:39 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 00:46:41 by lboiteux         ###   ########.fr       */
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

	if (command[0] == "PASS") {
		std::cout << "PASS command " ;

		if (command[1] == PASSWORD)	
		{
			std::cout << "(Correct password)" << std::endl;
		}
		else
		{
			std::cout << "(Incorrect password)" << std::endl ;
		}
	}

	else if (command[0] == "NICK")
    {
		std::cout << "NICK command" << std::endl;
	}

	else if (command[0] == "USER")
		userCommand(client, command);

	else if (command[0] == "JOIN")
		joinCommand(server, client, command);

	else if (command[0] == "PRIVMSG")
	{
		std::cout << "PRIVMSG command" << std::endl;
	}

	else if (command[0] == "QUIT")
	{
		std::cout << "QUIT command" << std::endl;
	}

	else
	{
		std::cout << RED << "Commande inconnue (" << command[0] << ")" << std::endl << RESET;
	}
	std::cout << BOLD BLUE << "_________________________________________" << std::endl << std::endl << RESET;
	std::cout << std::endl;
}

