/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:27 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 02:40:01 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
//#include "includes.hpp"

bool	verifyNickname(Server *server, std::vector<std::string> commands){
	
	std::vector<Client *>	clients = server->getClients();
	for (size_t i = 0; i < clients.size(); ++i){
		
		if (clients[i]->getNickName() == commands[1])
			return (0);
	}
	return (1);
}

void    commandNick(Server *server, Client *client, std::vector<std::string> commands)
{

	std::string	old_nickname = client->getNickName();

	if (commands.size() < 2)
		std::cout << BOLD RED << "Error: Not enough arguments" << RESET << std::endl;
	// if (!checkNicknameFormat(server, client, commands))
	// 	std::cout << BOLD RED << "Error: Invalid nickname format" << RESET << std::endl;
	if (!verifyNickname(server, commands))
		std::cout << BOLD RED << "Error: Nickname already taken" << RESET << std::endl;
	
	client->setNickName(commands[1]);
	std::string msg;

	if (client->getRealName().empty() == true && client->getUserName().empty() == true)
	{
		msg = ":localhost 001 " + client->getNickName() + " :Welcome to the IRC server\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
	} 
	else
	{
		msg = ":" + old_nickname + " NICK " + client->getNickName() + "\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);

		std::cout << BOLD GREEN << "Nickname changed to " << client->getNickName() << RESET << std::endl;
	}
}
