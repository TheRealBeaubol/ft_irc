/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:27 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 19:37:47 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool	isNickNameAvailable(Server *server, std::vector<std::string> commands){
	
	std::vector<Client *>	clients = server->getClients();

	for (size_t i = 0; i < clients.size(); ++i)
		if (clients[i]->getNickName() == commands[1])
			return (0);
			
	return (1);
}

bool checkNicknameFormat(const std::string &nickname) {
	
	if (nickname.empty())
        return false;
	if (nickname.size() > 16)
		return false;

    char c = nickname[0];

    if (!(std::isalpha(c) || (c == '[' || c == ']' || c == '\\' || 
                              c == '`' || c == '_' || c == '^' ||
                              c == '{' || c == '|' || c == '}')))
        return false;

    for (size_t i = 1; i < nickname.size(); i++)
	{
        c = nickname[i];
        if (!(std::isalpha(c) || std::isdigit(c) ||
              (c == '[' || c == ']' || c == '\\' ||
               c == '`' || c == '_' || c == '^' ||
               c == '{' || c == '|' || c == '}') || c == '-'))
            return false;
    }
	
    return true;
}

void    commandNick(Server *server, Client *client, std::vector<std::string> commands) {
	
	std::string msg;
	std::string serverName = std::string(SERVER_NAME);
	
	if (commands.size() < 2) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 431 " + client->getNickName() + " :No nickname given\r\n");
	}
	std::string newNickname = commands[1];

	if (!checkNicknameFormat(newNickname)) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 432 " + client->getNickName() + " " + newNickname + " :Erroneous nickname\r\n");
	}
	if (!isNickNameAvailable(server, commands)) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 433 " + client->getNickName() + " " + newNickname + " :Nickname is already in use\r\n");
	}
	
	std::string	oldNickname = client->getNickName();
	client->setNickName(newNickname);

	if (client->getIsLog() == false && client->getUserName().empty() == false) {
		client->setIsLog(true);
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 001 " + client->getNickName() + " :Welcome to the Internet Relay Chat Network " + client->getNickName() + "!" + client->getUserName() + "@" + serverName + "\r\n");
	} 
	else {
		msg = ":" + oldNickname + "!" + client->getUserName() + "@localhost NICK :" + client->getNickName() + "\r\n";
		int isOnChannel = 0;
		for (size_t i = 0; i < server->getChannels().size(); i++) {
			if (server->getChannels()[i]->getClientByName(oldNickname) != NULL) {
				server->getChannels()[i]->broadcastChannel(msg, client);
				isOnChannel = 1;
			}
		}
		if (isOnChannel == 0)
			SEND_MESSAGE(msg);
	}
}
