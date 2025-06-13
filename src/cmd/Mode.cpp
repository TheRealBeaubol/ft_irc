/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:30 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/13 17:52:41 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void modeICommand(Channel *channel, int sign) {

	bool inviteOnly = channel->getInviteOnly();

	if (sign == -1 && inviteOnly == true) {
		channel->setInviteOnly(false);
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " -i\r\n", NULL);		
	}
	else if (sign == 1 && inviteOnly == false) {
		channel->setInviteOnly(true);
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " +i\r\n", NULL);
	}
	
}

void modeKCommand(Channel *channel, int sign, std::string newPassword) {

	std::string password = channel->getPassword();

	if (sign == -1 && password != "") {
		channel->setPassword("");
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " -k\r\n", NULL);
	}
	else if (sign == 1)
	{
		if (password == "")	{
			channel->setPassword(newPassword);
			channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " +k " + newPassword + "\r\n", NULL);
		}
		else
			channel->broadcastChannel(":" + std::string(SERVER_NAME) + " " + ERR_KEYSET + " " + channel->getName() + " :Channel key already set\r\n", NULL);
	}
}

void modeLCommand(Channel *channel, Client *client, int sign, int newClientLimit) {

	int clientLimit = channel->getClientLimit();

	if (sign == -1 && clientLimit != 0)	{
		channel->setClientLimit(0);
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " -l\r\n", NULL);
	}
	else if (sign == 1 && newClientLimit == 0) {
		std::string msg = ":" + std::string(SERVER_NAME) + " 696 " + channel->getName() + " l :Invalid mode parameter\r\n";
		send(client->getClientFd(), msg.c_str(), msg.size(), 0);
	}
	else if (sign == 1 && newClientLimit > 0 && newClientLimit != clientLimit)	{
		channel->setClientLimit(newClientLimit);
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " +l " + itoa(newClientLimit) + "\r\n", NULL);
	}
}

void modeOCommand(Server *server, Channel *channel, Client *client, int sign, std::string clientNameToMode) {

	Client *clientOnServer = server->getClientByName(clientNameToMode);

	if (clientOnServer == NULL)
		SEND_MESSAGE_AND_RETURN("" + std::string(SERVER_NAME) + " " + ERR_NOSUCHNICK + " " + client->getNickName() + " " + clientNameToMode + " :No such nick/channel\r\n");
	
	Client *clientOnChannel = channel->getClientByName(clientNameToMode);
	if (clientOnChannel == NULL || channel->getClientParam(clientOnChannel)[LOGGED] == false)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_USERNOTINCHANNEL + " " + client->getNickName() + " " + clientNameToMode + " :They aren't on that channel\r\n");

	bool* client_param;
	client_param = channel->getClientParam(clientOnChannel);

	if (sign == -1 && client_param[OPERATOR] == true) {
		channel->setOperator(clientOnChannel, false);
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " -o " + clientOnChannel->getNickName() + "\r\n", NULL);
	}
	else if (sign == 1 && client_param[OPERATOR] == false) {
		channel->setOperator(clientOnChannel, true);
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " +o " + clientOnChannel->getNickName() + "\r\n", NULL);
	}
}

void modeTCommand(Channel *channel, int sign) {

	bool topicUserAccess = channel->getTopicUserAccess();

	if (sign == -1 && topicUserAccess == true) {
		channel->setTopicUserAccess(false);
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " -t\r\n", NULL);
	}
	else if (sign == 1 && topicUserAccess == false)	{
		channel->setTopicUserAccess(true);
		channel->broadcastChannel(":" + std::string(SERVER_NAME) + " MODE " + channel->getName() + " +t\r\n", NULL);
	}
}

int isThereArgv(Channel *channel, Client *client, int argv_counter, int commandSize, char flag) {

	if (argv_counter >= commandSize) {
		SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " " + channel->getChannelName() + " : mode +" + flag + " requires a parameter\r\n");
		return 0;
	}

	return 1;
}

void execModeCmd(Server *server, Channel *channel, Client *client, std::vector<std::string> command, int commandSize, int modeCharIndex, int last_sign, int *argv_counter) {

	std::string modeFlags = command[2];

	if (modeFlags[modeCharIndex] == 'i')
		modeICommand(channel, last_sign);

	else if (modeFlags[modeCharIndex] == 'k')
	{
		if (last_sign == 1)
		{
			if (isThereArgv(channel, client, *argv_counter, commandSize, 'k') == 0) 
				return ;
			modeKCommand(channel, last_sign, command[*argv_counter]);
			*argv_counter += 1;
		}
		else
			modeKCommand(channel, last_sign, "");
	}

	else if (modeFlags[modeCharIndex] == 'l')
	{
		if (last_sign == 1)
		{
			if (isThereArgv(channel, client, *argv_counter, commandSize, 'l') == 0)
				return ;
			modeLCommand(channel, client, last_sign, std::atoi(command[*argv_counter].c_str()));
			*argv_counter += 1;
		}
		else
			modeLCommand(channel, client, last_sign, 0);
	}

	else if (modeFlags[modeCharIndex] == 'o')
	{
		if (isThereArgv(channel, client, *argv_counter, commandSize, 'o') == 0)
			return ;
		modeOCommand(server, channel, client, last_sign, command[*argv_counter]);
		*argv_counter += 1;
	}

	else if (modeFlags[modeCharIndex] == 't')
		modeTCommand(channel, last_sign);

	return ;
}

void modeCommand(Server *server, Client *client, std::vector<std::string> command)
{
	int last_sign = 0;
	int argv_counter = 3;
	size_t commandSize = command.size();

	if (commandSize <= 1)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " " + command[0] + " :Not enough parameters\r\n");
	
	if (commandSize == 2)
	{
		if (command[1][0] == '#')
		{
			std::string channelMode;
			Channel *channel = server->getChannelByName(command[1]);
			std::vector<std::string> argv;

			if (channel == NULL)
				SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOSUCHCHANNEL + " " + client->getNickName() + " " + command[1] + " :No such channel\r\n");
			else {

				if (channel->getInviteOnly() == true)
					channelMode += "i";
				if (channel->getPassword() != "")
					channelMode += "k";
				if (channel->getClientLimit() != 0)
				{
					channelMode += "l";
					argv.push_back(itoa(channel->getClientLimit()));
				}
				if (channel->getTopicUserAccess() == true)
					channelMode += "t";

				std::string msg;
				msg = ":" + std::string(SERVER_NAME) + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " " + channel->getChannelName() + " +" + channelMode;
				for (size_t i = 0; i < argv.size(); i++)
					msg += " " + argv[i];
				msg += "\r\n";
				SEND_MESSAGE(msg);

				SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + RPL_CREATIONTIME + " " + client->getNickName() + " " + channel->getChannelName() + " " + itoa(channel->getCreationTime()) + "\r\n");
			}
		}
		else
		{
			if (command[1] == client->getNickName())
				SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + RPL_UMODEIS + " " + client->getNickName() + " " + command[1] + " :is now known as " + client->getNickName() + "\r\n");
			SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_USERSDONTMATCH + " " + client->getNickName() + " :Cannot change mode for other users\r\n");
		}
		return ;
	}
	
	Channel *channel = server->getChannelByName(command[1]);
	if (channel == NULL)
		SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOSUCHCHANNEL + " " + client->getNickName() + " " + command[1] + " :No such channel\r\n");
	else {
	
		Client *clientOnChannel = channel->getClientByName(client->getNickName());
	
		if (clientOnChannel == NULL || channel->getClientParam(clientOnChannel)[LOGGED] == false)
			SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOTONCHANNEL + " " + client->getNickName() + " " + command[1] + " :You're not on that channel\r\n");
		else if (channel->getClientParam(clientOnChannel)[OPERATOR] == false)
			SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_CHANOPRIVSNEEDED + " " + client->getNickName() + " " + command[1] + " :You're not channel operator\r\n");
	}

	int i = 0;
	while (command[2][i])
	{
		if (command[2][i] == '+' || command[2][i] == '-')
		{
			last_sign = (command[2][i] == '-') ? -1 : 1;
			i++;
			continue ;
		}
		else if (std::string("iklot").find(command[2][i]) != std::string::npos && last_sign != 0) {
			execModeCmd(server, channel, client, command, commandSize, i, last_sign, &argv_counter);
		}
		else
			SEND_MESSAGE(":" + std::string(SERVER_NAME) + " " + ERR_UNKNOWNMODE + " " + client->getNickName() + " " + channel->getChannelName() + " :Unknown mode flag " + command[2][i] + "\r\n");
		i++;
	}
}
