/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:32 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 22:26:32 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	inviteCommand(Server *server, Client *client, std::vector<std::string> command)
{
	if (command.size() < 3)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " INVITE :Not enough parameters\r\n");

	std::string channelName = command[2];
	std::string receiverName = command[1];
	Channel	*channel = server->getChannelByName(channelName);

	if (!channel)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOSUCHCHANNEL + " " + client->getNickName() + " " + channelName + " :No such channel\r\n");
	if (channel->getClientByName(client->getNickName()) == NULL)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOTONCHANNEL + " " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n");
	if (channel->getClientParam(client)[OPERATOR] == false)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_CHANOPRIVSNEEDED + " " + client->getNickName() + " " + channelName + " :You're not channel operator\r\n");
	
	Client *receiver = server->getClientByName(command[1]);

	if (!receiver)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOSUCHNICK + " " + client->getNickName() + " " + command[1] + " :No such nick/channel\r\n");
	if (channel->getClientByName(receiver->getNickName()) != NULL)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_USERONCHANNEL + " " + client->getNickName() + " " + command[1] + " " + channelName + " :is already on channel\r\n");

	channel->addClient(receiver);
	std::string	msg;
	
	msg = ":" + std::string(SERVER_NAME) + " " + RPL_INVITING + " " + client->getNickName() + " " + command[1] + " " + channelName + "\r\n";
	send(client->getClientFd(), msg.c_str(), msg.length(), 0);
	
	msg = ":" + client->getNickName() + " INVITE " + command[1] + " " + channelName + "\r\n";
	send(receiver->getClientFd(), msg.c_str(), msg.length(), 0);
}
