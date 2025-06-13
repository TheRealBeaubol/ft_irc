/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:23 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 22:27:01 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string	getListOfClient(Channel* channel) {

	std::string	list;

	for (std::map<Client *, bool*>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); ++it){
		if (it->second[OPERATOR] == true)
			list += "@" + it->first->getNickName() + " ";
		else
			list += it->first->getNickName() +" ";
	}

	return (list);
}

std::vector<std::pair<std::string, std::string> > fillChannelList(std::vector<std::string> commands) {

	std::vector<std::pair<std::string, std::string> > channelList;
	std::vector<std::string> channelNames;
	std::vector<std::string> channelPasswords;

	channelNames = split(commands[1], ',');
	if (commands.size() > 2)
		channelPasswords = split(commands[2], ',');

	for (size_t i = 0; i < channelNames.size(); i++) {
		if (channelPasswords.size() > i)
			channelList.push_back(std::make_pair(channelNames[i], channelPasswords[i]));
		else
			channelList.push_back(std::make_pair(channelNames[i], ""));
	}
	return channelList;
}

void	createChannel(Server *server, Client *client, std::pair<std::string, std::string> joinedChannel) {

	std::string channelName = joinedChannel.first;
	std::string channelPassword = joinedChannel.second;

	Channel *newChannel = new Channel(channelName);
	
	if (channelPassword != "")
		newChannel->setPassword(channelPassword);

	newChannel->addClient(client);
	
	newChannel->setClientParam(client, true, true);
	
	server->addChannel(newChannel);

	SEND_MESSAGE(":" + client->getNickName() + " JOIN :" + channelName + "\r\n" +
		":" + std::string(SERVER_NAME) + " " + RPL_NAMREPLY + " " + client->getNickName() + " = " + channelName + " :" + getListOfClient(newChannel) + "\r\n" +
		":" + std::string(SERVER_NAME) + " " + RPL_ENDOFNAMES + " " + client->getNickName() + " " + channelName + " :End of /NAMES list.\r\n");
}

void	joinChannel(Channel *channel, Client *client, std::pair<std::string, std::string> joinedChannel) {

	std::string channelName = joinedChannel.first;
	std::string channelPassword = joinedChannel.second;
	std::string clientName = client->getNickName();
	
	if (channel->getInviteOnly() == true && (channel->getClientByName(clientName) == NULL))
		SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + ERR_INVITEONLYCHAN + " " + clientName + " " + channelName + " :Cannot join channel (+i)\r\n");
	else if (channel->getClientByName(clientName) != NULL && channel->getClientParam(client)[LOGGED] == true)
		SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + ERR_USERONCHANNEL + " " + clientName + " " + channelName + " :is already on channel\r\n");
	else if (channel->getPassword().empty() == false && channel->getPassword() != channelPassword)
		SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + ERR_BADCHANNELKEY + " " + clientName + " " + channelName + " :Cannot join channel (+k)\r\n");
	else if (channel->getClients().size() >= (size_t) channel->getClientLimit() && channel->getClientLimit() != 0)
		SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + ERR_CHANNELISFULL + " " + clientName + " " + channelName + " :Cannot join channel (+l)\r\n");
	else {	
		if (channel->getClientByName(clientName) == NULL) {
		
			channel->addClient(client);
			channel->setClientParam(client, true, false);
		}
		else
			channel->setClientParam(client, true, false);

		channel->broadcastChannel(":" + clientName + " JOIN :" + channelName + "\r\n", NULL);

		SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + RPL_TOPIC + " " + clientName + " " + channelName + " :" + channel->getTopic() + "\r\n" +
				":" + std::string(SERVER_NAME) + " " + RPL_NAMREPLY + " " + clientName + " = " + channelName + " :" + getListOfClient(channel) + "\r\n" + 
				":" + std::string(SERVER_NAME) + " " + RPL_ENDOFNAMES + " " + clientName + " " + channelName + " :End of /NAMES list.\r\n");
	}
}

void	joinCommand(Server *server, Client *client, std::vector<std::string> commands) {
		
	if (commands.size() < 2)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " JOIN :Not enough parameters\r\n");
	
	std::vector<std::pair<std::string, std::string> > channelList = fillChannelList(commands);

	for (size_t i = 0; i < channelList.size(); i++) {
		std::string channelName = channelList[i].first;
		std::string channelPassword = channelList[i].second;
		
		if (channelName[0] != '#') {
			SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + ERR_NOSUCHCHANNEL + " " + client->getNickName() + " " + channelName + " :No such channel\r\n");
			continue;
		}
		Channel *channel;
		channel = server->getChannelByName(channelName);
		
		if (channel == NULL)
			createChannel(server, client, channelList[i]);
		else
			joinChannel(channel, client, channelList[i]);
	}
}
