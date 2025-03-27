/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:48:03 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/27 23:22:46 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

class Server {
	public:
		Server(int port);
		~Server();

		int handleNewConnection();
		void sendMessage(int clientSocket, const char *msg);
		
		void removePollFd(struct pollfd poll_fd);
		std::vector<struct pollfd> getPollFds();
		
		void removeClient(Client* client);
		std::vector<Client *> getClients();

	private:
		int _serverFd;
		int _port;
		
		std::vector<struct pollfd> _pollFds;
		std::vector<Client *> _clients;
};
