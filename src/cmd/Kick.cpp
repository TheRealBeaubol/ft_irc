/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/07 23:32:34 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	commandKick(Server *server, Client *client, std::vector<std::string> command){

	std::string msg;
	std::string serverName = std::string(SERVER_NAME);

	if (command.size() < 3)
	{
		msg = ":" + serverName + " 461 " + client->getNickName() + " KICK :Not enough parameters\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	
	std::string channelName = command[1];
	std::string receiverName = command[2];
	Channel *channel = server->findChannel(channelName);

	if (!channel)
	{
		msg = ":" + serverName + " 403 " + client->getNickName() + " " + channelName + " :No such channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	if (channel->getClientByName(client->getNickName()) == NULL)
	{
		msg = ":" + serverName + " 442 " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	if (channel->getClientParam(client)[2] == false)
	{
		msg = ":" + serverName + " 482 " + client->getNickName() + " " + channelName + " :You're not channel operator\r\n";
		send(client->getClientSocket(), msg.c_str(), msg.length(), 0);
		std::cout << BOLD RED << msg << RESET;
		return ;
	}
	
	// Client *receiver = server->findClient(receiverName);
	
	
	msg = ":" + client->getNickName() + " KICK " + channelName + " " + command[2] + "\r\n";
	std::cout << "Msg sent : " << msg << std::endl << "Total number of clients: " << server->getClients().size() <<std::endl;
	channel->broadcastChannel(msg, NULL);
}
