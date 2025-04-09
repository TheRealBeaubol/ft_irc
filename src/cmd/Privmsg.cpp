/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:20 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/09 21:03:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	msgChannel(Server *server, Client *client, std::string channelName, std::string messageSent){
	
	std::string serverName = std::string(SERVER_NAME);
	std::string msg;

	Channel *receiver = server->findChannel(channelName);
	
	if (!receiver)
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 403 " + client->getNickName() + " " + channelName + " :No such channel\r\n");

	if (receiver->getClientByName(client->getNickName()) == NULL)
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 442 " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n");

	msg = ":" + client->getNickName() + " PRIVMSG #" + receiver->getChannelName() + " :" + messageSent + "\r\n"; 
	receiver->broadcastChannel(msg, NULL);
}

void	msgUser(Server *server, Client *client, std::string receiverName, std::string messageSent){

	std::string serverName = std::string(SERVER_NAME);
	std::string msg;

	Client *receiver = server->findClient(receiverName);

	if (!receiver)
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 401 " + client->getNickName() + " " + receiverName + " :No such nick/channel\r\n");
	
	msg = ":" + client->getNickName() + " PRIVMSG " + receiver->getNickName() + " :" + messageSent + "\r\n"; 
	send(receiver->getClientSocket(), msg.c_str(), msg.length(), 0);
}

void	prvmsgCommand(Server *server, Client *client, std::vector<std::string>	command){

	std::string msg;
	std::string serverName = std::string(SERVER_NAME);

	if (command.size() < 2)
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 411 " + client->getNickName() + " :No recipient given\r\n");

	if (command.size() < 3)
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 412 " + client->getNickName() + " :No text to send\r\n");
	
	if (command[1][0] == '#')
		msgChannel(server, client, command[1], command[2]);
	else
		msgUser(server, client, command[1], command[2]);
}
