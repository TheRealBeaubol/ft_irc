/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:30 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 00:40:27 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void modeICommand(Server *server, Client *client, std::vector<std::string> command){(void) server; (void) client; (void) command;}
void modeTCommand(Server *server, Client *client, std::vector<std::string> command){(void) server; (void) client; (void) command;}
void modeOCommand(Channel *channel, std::string clientNameToMode, char sign)
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
		// client_param[2] = false;
		bool new_param[3] = {NULL, NULL, false};
		channel->setClientParam(clientToMode, new_param);
		std::cout << "Succes, operator been retrograded (need to send confirmation to client who sended mode command)" << std::endl;
	}
	else if (sign == '+' && client_param[2] == false)
	{
		// client_param[2] = true;
		bool new_param[3] = {NULL, NULL, true};
		channel->setClientParam(clientToMode, new_param);
		std::cout << "Succes, operator been promoted (need to send confirmation to client who sended mode command)" << std::endl;
	}
	else
		std::cout << "Nothing to do ???" << std::endl;
}

void modeKCommand(Server *server, Client *client, std::vector<std::string> command){(void) server; (void) client; (void) command;}
void modeLCommand(Server *server, Client *client, std::vector<std::string> command){(void) server; (void) client; (void) command;}

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
			modeICommand(server, client, command);
		else if (command[2][i] == 't')
			modeTCommand(server, client, command);
		else if (command[2][i] == 'o')
			modeOCommand(channel, command[3], command[2][0]);
		else if (command[2][i] == 'k')
			modeKCommand(server, client, command);
		else if (command[2][i] == 'l')
			modeLCommand(server, client, command);
		else
			err++;
	}
	if (err > 0)
		std::cout << "There was an invalid char, need to send : irc.exemple.com 472 MonPseudo #canal :Unknown channel mode" << std::endl;
}
