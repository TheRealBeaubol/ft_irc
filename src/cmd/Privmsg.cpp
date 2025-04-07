/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:20 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 21:02:07 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	msgChannel(Server *server, Client *client, std::vector<std::string> command){
	Channel *receiver = server->findChannel(command[1]);
	std::string msg;
	
	if (!receiver)
	{
		msg = ":" + std::string(SERVER_NAME) + " 403 " + client->getNickName() + " " + command[1] + " :No such channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (receiver->getClientByName(client->getNickName()) == NULL)
	{
		msg = ":" + std::string(SERVER_NAME) + " 404 " + client->getNickName() + " " + command[1] + " :Cannot send to channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		return ;
	}

	msg = ":" + client->getNickName() + " PRIVMSG #" + receiver->getChannelName() + " :" + command[2] + "\r\n"; 
	receiver->broadcastChannel(msg, NULL);
}

void	msgUser(Server *server, Client *client, std::vector<std::string> command){

	Client *receiver = server->findClient(command[1]);
	std::string msg;

	std::cout << "Receiver: " << receiver->getNickName() << std::endl;
	if (!receiver)
	{
		msg = ":" + std::string(SERVER_NAME) + " 401 " + client->getNickName() + " " + command[1] + " :No such nick/channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		return ;
	}
	
	msg = ":" + client->getNickName() + " PRIVMSG " + receiver->getNickName() + " :" + command[2] + "\r\n"; 
	send(receiver->getClientSocket(), msg.c_str(), msg.length(), 0);
}

void	prvmsgCommand(Server *server, Client *client, std::vector<std::string>	command){

	if (command.size() < 2)
	{
		std::string msg = ":" + std::string(SERVER_NAME) + " 411 " + client->getNickName() + " :No recipient given\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		return ;
	}
	if (command.size() < 3)
	{
		std::string msg = ":" + std::string(SERVER_NAME) + " 412 " + client->getNickName() + " :No text to send\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		return ;
	}
	
	if (command[1][0] == '#')
		msgChannel(server, client, command);
	else
		msgUser(server, client, command);
}
