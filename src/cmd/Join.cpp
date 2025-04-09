/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:23 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/09 16:58:05 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string	getListOfClient(Channel* channel){
	std::string	list;
	for (std::map<Client *, bool*>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); ++it){
		if (it->second[2] == true)
			list += "@" + it->first->getNickName() + " ";
		else
			list += it->first->getNickName() +" ";
	}
	std::cout <<"list of client: "<< list << std::endl;
	return (list);
}

void	joinCommand(Server *server, Client *client, std::vector<std::string> commands) {
	
	std::string	serverName = std::string(SERVER_NAME);
	std::string	msg_ERR;

	if (commands.size() < 2)
	{
		msg_ERR = serverName + " 461 " + client->getNickName() + " JOIN :Not enough parameters\r\n";
		send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
		std::cout << BOLD RED << msg_ERR << RESET;
		return ;
	}
	Channel *channel = server->findChannel("#" + commands[1]);

	std::string	msg = ":" + client->getNickName() + " JOIN :#" + commands[1] + "\r\n";
	if (channel != NULL){
		if (channel->getInviteOnly() == true && ((channel->getClientByName(client->getNickName()) == NULL) || (channel->getClients()[client][0] == false))){
			msg_ERR = serverName + " 473 " + client->getNickName() + " " + commands[1] + " :Cannot join channel (+i)\r\n";
			send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
			std::cout << BOLD RED << msg_ERR << RESET;
			return ;
		}
		if (channel->getClientByName(client->getNickName()) != NULL) {
			if (channel->getClients()[client][1] == true){			
				msg_ERR = serverName + " 443 " + client->getNickName() + " " + commands[1] + " :is already on channel\r\n";
				send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
				std::cout << BOLD RED << msg_ERR << RESET;
				return ;
			}
		}
		if (channel->getPassword().empty() == false) {
			msg_ERR = serverName + " 475 " + client->getNickName() + " " + commands[1] + " :Cannot join channel (+k)\r\n";
			if (commands.size() < 3) {
				send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
				std::cout << BOLD RED << msg_ERR << RESET;
				return ;
			}
			if(channel->getPassword() != commands[2]) {
				send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
				std::cout << BOLD RED << msg_ERR << RESET;
				return ;
			}
		}
		if (channel->getClients().size() >= (size_t) channel->getClientLimit() && channel->getClientLimit() != 0) {
			msg_ERR = serverName + " 471 " + client->getNickName() + " " + commands[1] + " :Cannot join channel (+l)\r\n";
			send(client->getClientSocket(), msg_ERR.c_str(), msg_ERR.size(), 0);
			std::cout << BOLD RED << msg_ERR << RESET;
			return ;
		}
		std::cout << LIGHTMAGENTA << "Channel [ " << channel->getChannelName() << " ] exists, user joined it" << RESET << std::endl;
		
		if (channel->getClientByName(client->getNickName()) == NULL){
			channel->addClient(client);
			channel->setClientParam(client, false, true, false);
		}
		else
			channel->setClientParam(client, true, true, false);
		server->sendMessage(client->getClientSocket(), msg.c_str());
		msg = ":" + serverName + " 353 " + client->getNickName() + " = " + channel->getChannelName() + " :"+ getListOfClient(channel) + "\r\n" ;
		server->sendMessage(client->getClientSocket(), msg.c_str());
		msg = ":" + serverName + " 366 " + client->getNickName() + " " + channel->getChannelName() + " :End of /NAMES list.\r\n";
		server->sendMessage(client->getClientSocket(), msg.c_str());
		
	}
	else
	{
		std::cout << LIGHTMAGENTA << "The [ " << commands[1] << " ] channel doesn't exists, it will be created" << std::endl;
		size_t 	channelSize = server->getChannel().size();
		Channel *newChannel = new Channel(commands[1]);
		server->addChannel(newChannel);
		server->getChannel()[channelSize]->addClient(client);
		server->getChannel()[channelSize]->setClientParam(client, false, true, true);
		server->sendMessage(client->getClientSocket(), msg.c_str());
		server->getChannel()[channelSize]->showClient();
		return;
	}
}
