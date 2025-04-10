/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:20 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 22:40:47 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	msgChannel(Server *server, Client *client, std::string channelName, std::string messageSent) {
	
	std::string serverName = std::string(SERVER_NAME);
	std::string msg;

	Channel *receiver = server->getChannelByName(channelName);
	
	if (!receiver) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 403 " + client->getNickName() + " " + channelName + " :No such channel\r\n");
	}
	if (receiver->getClientByName(client->getNickName()) == NULL) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 442 " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n");
	}
	
	msg = ":" + client->getNickName() + "!" + client->getUserName() + " PRIVMSG " + channelName + " :" + messageSent + "\r\n";
	receiver->broadcastChannel(msg, client);
}

void	msgUser(Server *server, Client *client, std::string receiverName, std::string messageSent) {

	std::string serverName = std::string(SERVER_NAME);
	std::string msg;

	Client *receiver = server->getClientByName(receiverName);

	if (!receiver) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 401 " + client->getNickName() + " " + receiverName + " :No such nick/channel\r\n");
	}
	if (receiver->getIsLog() == false || receiver->getIsAuth() == false) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 401 " + client->getNickName() + " " + receiverName + " :No such nick/channel\r\n");
	}
	
	msg = ":" + client->getNickName() + "!" + client->getUserName() + " PRIVMSG " + receiverName + " :" + messageSent + "\r\n"; 			
	send(receiver->getClientSocket(), msg.c_str(), msg.length(), 0);
}

void	prvmsgCommand(Server *server, Client *client, std::vector<std::string>	command) {

	std::string msg;
	std::string serverName = std::string(SERVER_NAME);

	if (command.size() < 2) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 411 " + client->getNickName() + " :No recipient given\r\n");
	}
	if (command.size() < 3) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 412 " + client->getNickName() + " :No text to send\r\n");
	}

	std::vector<std::string> target = split(command[1], ',');

	if (target.size() > 0) {
		for (size_t i = 0; i < target.size(); i++)
		{
			if (target[i][0] == '#')
				msgChannel(server, client, target[i], command[2]);
			else
				msgUser(server, client, target[i], command[2]);
		}
		return ;
	}
}
