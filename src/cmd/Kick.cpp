/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 19:38:26 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	commandKick(Server *server, Client *client, std::vector<std::string> command){

	std::string msg;
	std::string serverName = std::string(SERVER_NAME);

	if (command.size() < 3) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 461 " + client->getNickName() + " KICK :Not enough parameters\r\n");
	}
	
	std::string channelName = command[1];
	std::string receiverName = command[2];
	Channel *channel = server->getChannelByName(channelName);

	if (!channel) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 403 " + client->getNickName() + " " + channelName + " :No such channel\r\n");
	}
	if (channel->getClientByName(client->getNickName()) == NULL) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 442 " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n");
	}
	if (channel->getClientParam(client)[OPERATOR] == false) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 482 " + client->getNickName() + " " + channelName + " :You're not channel operator\r\n");	
	}
	
	Client *receiver = server->getClientByName(receiverName);
	
	if (!receiver) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 401 " + client->getNickName() + " " + receiverName + " :No such nick/channel\r\n");
	}
	
	if (channel->getClientByName(receiver->getNickName()) == NULL) {
		SEND_MESSAGE_AND_RETURN(":" + serverName + " 441 " + client->getNickName() + " " + receiver->getNickName() + " " + channelName + " :They aren't on that channel\r\n");
	}
	
	std::string comment = (command.size() > 3) ? command[3] : client->getNickName();

	msg = ":" + client->getNickName() + " KICK " + channelName + " " + receiverName + " :" + comment + "\r\n";
	channel->broadcastChannel(msg, NULL);
	
	channel->removeClient(receiver);
	if (channel->getClients().size() == 0)
		server->removeChannel(channel);
}