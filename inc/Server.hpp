/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:48:03 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/11 19:53:55 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Includes.hpp"

class Channel;

class Server {
	public:
		Server(int port, std::string password);
		~Server();

		int handleNewConnexion();
		int run();
		
		void removePollFd(struct pollfd poll_fd);
		std::vector<struct pollfd> getPollFds();
		
		void removeChannel(Channel *channel);
		void addChannel(Channel *channel);
		std::vector<Channel *> getChannels();
		Channel *getChannelByName(std::string channelName);
		
		void removeClient(Client* client);
		std::vector<Client *> getClients();
		Client *getClientByName(std::string ClientName);

		std::string getPassword() const;

	private:
		int _serverFd;
		int _port;
		std::string _password;
		
		std::vector<struct pollfd> _pollFds;
		std::vector<Client *> _clients;
		std::vector<Channel *> _channels;

};
