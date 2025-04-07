/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:30 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 19:32:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void modeICommand(Channel *channel, char sign)
{
	bool inviteOnly = channel->getInviteOnly();

	if (sign == '-' && inviteOnly == true)
	{
		channel->setInviteOnly(false);
		std::cout << "Succes, now cannal is 100%% accessible" << std::endl;
	}
	else if (sign == '+' && inviteOnly == false)
	{
		channel->setInviteOnly(true);
		std::cout << "Succes, nnow canal is on invite only mode" << std::endl;
	}
	else
		std::cout << "Nothing to do ???" << std::endl;
}

void modeTCommand(Channel *channel, char sign)
{
	bool topicUserAccess = channel->getTopicUserAccess();

	if (sign == '-' && topicUserAccess == true)
	{
		channel->setTopicUserAccess(false);
		std::cout << "Succes, now topic is no more modifiable by users" << std::endl;
	}
	else if (sign == '+' && topicUserAccess == false)
	{
		channel->setTopicUserAccess(true);
		std::cout << "Succes, now topic is modifiable by user" << std::endl;
	}
	else
		std::cout << "Nothing to do ???" << std::endl;
}

void modeOCommand(Channel *channel, char sign, std::string clientNameToMode)
{
	std::cout << "Mode O command" << std::endl;

	Client *clientToMode = channel->getClientByName(clientNameToMode);
	if (clientToMode == NULL)
	{
		std::cout << "Error : There is no user named " << clientNameToMode << std::endl;
		return ;
	}

	bool* client_param;
	client_param = channel->getClientParam(clientToMode);

	if (client_param == NULL)
		std::cout << "NULLLLLLL" << std::endl;

	if (sign == '-' && client_param[2] == true)
	{
		channel->setOperator(clientToMode, false);
		std::cout << "Succes, operator been retrograded (need to send confirmation to client who sended mode command)" << std::endl;
	}
	else if (sign == '+' && client_param[2] == false)
	{
		channel->setOperator(clientToMode, true);
		std::cout << "Succes, operator been promoted (need to send confirmation to client who sended mode command)" << std::endl;
	}
	else
		std::cout << "Nothing to do ???" << std::endl;
}

void modeKCommand(Channel *channel, char sign, std::string newPassword)
{
	std::string password = channel->getPassword();
	if (sign == '-' && password != "")
	{
		channel->setPassword("");
		std::cout << "Succes, password removed" << std::endl;
	}
	else if (sign == '+' && newPassword != password)
	{
		channel->setPassword(newPassword);
		std::cout << "Succes, password setted to : " << newPassword << std::endl;
	}
	else
		std::cout << "Nothing to do ???" << std::endl;
}

void modeLCommand(Channel *channel, char sign, int newClientLimit)
{
	int clientLimit = channel->getClientLimit();

	if (sign == '-' && clientLimit != 0)
	{
		channel->setClientLimit(0);
		std::cout << "Succes, ClientLimit removed" << std::endl;
	}
	else if (sign == '+' && newClientLimit >= 0 && newClientLimit != clientLimit)
	{
		channel->setClientLimit(newClientLimit);
		std::cout << "Succes, ClientLimit setted to : " << newClientLimit << std::endl;
	}
	else
		std::cout << "Nothing to do ???" << std::endl;
}

void modeCommand(Server *server, Client *client, std::vector<std::string> command)
{
	std::cout << "MODE command" << std::endl;

	size_t commandSize = command.size();
	for (size_t i = 0; i < commandSize; i++) {
		std::cout << "command " << i << " = " << CYAN << command[i] << RESET << std::endl;
	}
	
	if (commandSize <= 2)
	{
		std::cout << "voiding that one..." << std::endl; // probably need to send error too
		return;
	}

	Channel *channel = server->findChannel(command[1]);
	if (channel == NULL)
	{
		std::cout << "Error : There is no channel with that name... (need to send error...)" << std::endl;
		return;
	}
	else if (channel->getClientParam(client)[2] == 0)
	{
		std::cout << "You're not operator, you can't use /MODE command... (need to send error...)" << std::endl;
		return;
	}
	else if ((command[2][0] == '+' || command[2][0] == '-') && (command[2][1] == '+' || command[2][1] == '-')) // check si commence par un + ou un - (si pas de +/- ou plus de un, return error)
	{
		std::cout << "Error : require only on sign, need to send: : irc.exemple.com 472 MonPseudo #canal :Unknown channel mode" << std::endl;
		return;
	}
		
	// on itère sur chaque char jusqua la fin de command[1] et on éxécute chaque char "existant", si il y en a un inconnu on le skip et on enverra une erreur (globale, une seul meme si plusieur inconnu) (:irc.exemple.com 472 MonPseudo #canal :Unknown channel mode(s))
	int err = 0;
	for ( std::size_t i = 1 ; i < command[2].size() ; i++)
	{
		std::cout << "Im on " << command[2][i] << std::endl;
		if (command[2][i] == 'i')
			modeICommand(channel, command[2][0]);
		else if (command[2][i] == 't')
			modeTCommand(channel, command[2][0]);
		else if (command[2][i] == 'o')
			modeOCommand(channel, command[2][0], command[3]);
		else if (command[2][i] == 'k')
		{
			// modeKCommand(channel, command[2][0], command[3].empty() ? NULL : command[3]);

			if (commandSize >= 4)
				modeKCommand(channel, command[2][0], command[3]);
			else
				modeKCommand(channel, command[2][0], "");
		}
		else if (command[2][i] == 'l')
		{
			// modeLCommand(channel, command[2][0], std::atoi(command[3].c_str()));
			
			if (commandSize >= 4)
				modeLCommand(channel, command[2][0], std::atoi(command[3].c_str()));
			else
				modeLCommand(channel, command[2][0], 0);
		}
		else
			err++;
	}
	if (err > 0)
		std::cout << "There was an invalid char, need to send : irc.exemple.com 472 MonPseudo #canal :Unknown channel mode" << std::endl;
}
