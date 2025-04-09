/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:32 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 23:31:05 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	inviteCommand(Server *server, Client *client, std::vector<std::string> command)
{
	std::string	msg;
	std::string serverName = std::string(SERVER_NAME);

	if (command.size() < 3)
	{
		msg = ":" + serverName + " 461 " + client->getNickName() + " INVITE :Not enough parameters\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	
	std::string channelName = command[2];
	std::string receiverName = command[1];
	Channel	*channel = server->findChannel(channelName);

	if (!channel) {
		msg = ":" + serverName + " 403 " + client->getNickName() + " " + channelName + " :No such channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	if (channel->getClientByName(client->getNickName()) == NULL) {
		msg = ":" + serverName + " 442 " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	if (channel->getClientParam(client)[2] == false) {
		msg = ":" + serverName + " 482 " + client->getNickName() + " " + channelName + " :You're not channel operator\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}

	Client *receiver = server->findClient(command[1]);

	if (!receiver) {
		msg = ":" + serverName + " 401 " + client->getNickName() + " " + command[1] + " :No such nick/channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	if (channel->getClientByName(receiver->getNickName()) != NULL) {
		msg = ":" + serverName + " 443 " + client->getNickName() + " " + command[1] + " " + channelName + " :is already on channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	
	channel->addClient(receiver);
	channel->setClientParam(receiver, true, false, false);
	
	msg = ":" + serverName + " 341 " + client->getNickName() + " " + command[1] + " " + channelName + "\r\n";
	send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
	
	msg = ":" + client->getNickName() + " INVITE " + command[1] + " " + channelName + "\r\n";
	send(receiver->getClientSocket(), msg.c_str(), msg.length(), 0);
}