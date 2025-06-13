/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/13 17:59:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	commandKick(Server *server, Client *client, std::vector<std::string> command){
	
	if (command.size() < 3)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " KICK :Not enough parameters\r\n");
	
	std::string channelName = command[1];
	std::string receiverName = command[2];
	Channel *channel = server->getChannelByName(channelName);

	if (!channel)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOSUCHCHANNEL + " " + client->getNickName() + " " + channelName + " :No such channel\r\n");
	if (channel->getClientByName(client->getNickName()) == NULL || channel->getClientParam(client)[LOGGED] == false)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOTONCHANNEL + " " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n");
	if (channel->getClientParam(client)[OPERATOR] == false)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_CHANOPRIVSNEEDED + " " + client->getNickName() + " " + channelName + " :You're not channel operator\r\n");	

	Client *receiver = server->getClientByName(receiverName);
	
	if (!receiver)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOSUCHNICK + " " + client->getNickName() + " " + receiverName + " :No such nick/channel\r\n");
	
	if (channel->getClientByName(receiver->getNickName()) == NULL)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_USERNOTINCHANNEL + " " + client->getNickName() + " " + receiver->getNickName() + " " + channelName + " :They aren't on that channel\r\n");
	
	std::string comment = (command.size() > 3) ? command[3] : client->getNickName();

	channel->broadcastChannel(":" + client->getNickName() + " KICK " + channelName + " " + receiverName + " :" + comment + "\r\n", NULL);
	
	channel->removeClient(receiver);
	if (channel->getClients().size() == 0)
		server->removeChannel(channel);
}
