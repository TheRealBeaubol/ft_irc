/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:48:03 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/13 00:41:56 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Includes.hpp"

class Channel;

class Server
{
	public:

		Server(int port, std::string password);
		~Server();

		std::string getPassword() const;
		std::vector<struct pollfd> getPollFds();
		
		void addClient(Client* client);
		void removeClient(Client* client);
		std::vector<Client *> getClients();
		Client *getClientByName(std::string ClientName);
		Client *getClientByFd(int fd);
		bool isClientActive(Client *client);
		
		void addChannel(Channel *channel);
		void removeChannel(Channel *channel);
		std::vector<Channel *> getChannels();
		Channel *getChannelByName(std::string channelName);
		
		int handleNewConnexion();
		void handleMessage(Client *client);
		int run();

	private:

		int _port;
		std::string _password;
		int _serverFd;
		
		std::vector<Client *> _clients;
		std::vector<Channel *> _channels;

};
