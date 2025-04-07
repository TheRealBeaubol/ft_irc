/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:27 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 20:33:50 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include <string>
//#include "includes.hpp"

bool	verifyNickname(Server *server, std::vector<std::string> commands){
	
	std::vector<Client *>	clients = server->getClients();
	for (size_t i = 0; i < clients.size(); ++i){
		
		if (clients[i]->getNickName() == commands[1])
			return (0);
	}
	return (1);
}

bool checkNicknameFormat(const std::string &nickname) {
    if (nickname.empty())
        return false;

    char c = nickname[0];
    if (!(std::isalpha(c) || (c == '[' || c == ']' || c == '\\' || 
                              c == '`' || c == '_' || c == '^' ||
                              c == '{' || c == '|' || c == '}')))
        return false;

    for (size_t i = 1; i < nickname.size(); i++) {
        c = nickname[i];
        if (!(std::isalpha(c) || std::isdigit(c) ||
              (c == '[' || c == ']' || c == '\\' ||
               c == '`' || c == '_' || c == '^' ||
               c == '{' || c == '|' || c == '}') || c == '-'))
            return false;
    }
    return true;
}

void    commandNick(Server *server, Client *client, std::vector<std::string> commands)
{

	std::string	oldNickname = client->getNickName();
	std::string serverName = std::string(SERVER_NAME);
	std::string msg;
	
	if (commands.size() < 2){
		msg = ":" + serverName + " 431 " + client->getNickName() + " :No nickname given\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	if (!checkNicknameFormat(commands[1])) {
		msg = ":" + serverName + " 432 " + client->getNickName() + " :Erroneous nickname\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	if (!verifyNickname(server, commands)) {
		msg = ":" + serverName + " 433 " + client->getNickName() + " " + commands[1] + " :Nickname is already in use\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;	
	}
	
	client->setNickName(commands[1]);

	if (client->getIsLog() == false && client->getUserName().empty() == false)
	{
		client->setIsLog(true);
		msg = ":" + serverName + " 001 " + client->getNickName() + " :Welcome to the Internet Relay Chat Network " + client->getNickName() + "!" + client->getUserName() + "@" + SERVER_NAME + "\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		std::cout << BOLD GREEN << msg << RESET;
	} 
	else
	{
		msg = ":" + oldNickname + "!" + client->getUserName() + "@localhost NICK :" + client->getNickName() + "\r\n";
		
		if (client->getChannels().empty()) {
			send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
		} else
		{
			for (size_t i = 0; i < client->getChannels().size(); i++) {
				std::cout << "Broadcasting to channel " << client->getChannels()[i]->getChannelName() << std::endl;
				client->getChannels()[i]->broadcastChannel(msg, NULL);
			}
		}		
		std::cout << BOLD GREEN << "Nickname changed to " << client->getNickName() << RESET << std::endl;
	}
}
