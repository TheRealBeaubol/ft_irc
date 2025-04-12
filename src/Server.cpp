/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:35:55 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 23:36:07 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"
volatile sig_atomic_t server_status = SERVER_RUNNING;

Server::~Server() {
	for (size_t i = 0; i < _clients.size(); i++) {
		close(_clients[i]->getClientFd());
		delete _clients[i];
	}
	for (size_t i = 0; i < _channels.size(); i++) {
		delete _channels[i];
	}
	close(_serverFd);
	std::cout << BOLD BLUE << "Server closed" << RESET << std::endl;
}

int setNonBlocking(int fd) {
	
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) { return -1; }
	
	flags |= O_NONBLOCK;
		
	if (fcntl(fd, F_SETFL, flags) == -1) { return -1; }
	return 0;
}

void	handleSigInt(int sig) {
	
	if (sig == SIGINT) {
		std::cout << BOLD RED << "\n\nServer stopped" << RESET << std::endl;
		server_status = SERVER_STOPPED;
	}
}

Server::Server(int port, std::string password)
{

	std::cout << std::endl << BOLD BLUE << "Creating default IRC Server on the "<< port << " port" << RESET << std::endl << std::endl;

	std::cout << BOLD BLUE << "============ SERVER CREATION ============" << RESET << std::endl << std::endl;
	
	_port = port;
	_password = password;
	
	_serverFd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( _serverFd == -1 ) { 
		throw std::runtime_error("Error while creating socket");
	}
	int opt = 1;
	if ( setsockopt( _serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) == -1 ) {
		throw std::runtime_error("Error while setting socket options");
	}
	
	sockaddr_in address = {AF_INET, htons( port ), {INADDR_ANY}, {0}};
	if ( bind( _serverFd, ( struct sockaddr* )&address, sizeof( address ) ) == -1 ) {
		throw std::runtime_error("Error while binding socket");
	}

	if ( listen( _serverFd, SOMAXCONN ) == -1 ) {
		throw std::runtime_error("Error while listening on socket");
	}

	if ( setNonBlocking( _serverFd ) == -1 ) { 
		throw std::runtime_error("Error while setting socket to non-blocking");
	}

	Client *client = new Client( _serverFd );
	client->setIsAuth(true);
	client->setIsLog(true);
	_clients.push_back( client );
	
	std::cout << BOLD GREEN << "	Server created on port " << _port << RESET << std::endl << std::endl;
}

bool isClientActive(Client *client, Server *server) {
	std::vector<Client *> clients = server->getClients();
	for (size_t i = 0; i < clients.size(); i++) {
		if (clients[i] == client) {
			return true;
		}
	}
	return false;
}

int Server::run() {

	signal(SIGINT, handleSigInt);
	while (server_status == SERVER_RUNNING) {
	
		std::vector<struct pollfd> poll_fds = getPollFds();

		int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
		if (poll_count < 0) {
			return -1;
		}

		if (poll_fds[0].revents & POLLIN && handleNewConnexion() == -1)	{
			std::cerr << "handleNewConnexion failed" << ": " << strerror(errno) << std::endl;
			continue;
		}

		for (size_t i = 1; i < poll_fds.size(); ++i) {
		
			if (poll_fds[i].revents & POLLIN) {
			
				char buffer[BUFFER_SIZE];
				memset(buffer, 0, BUFFER_SIZE);
				int bytes_read = recv(poll_fds[i].fd, buffer, BUFFER_SIZE, 0);

				if (bytes_read > 0) {
				
					Client *client = getClients()[i];

					if (client) {
						client->appendToBuffer(std::string(buffer, bytes_read));

						size_t pos;
						while ((pos = client->getInputBuffer().find("\r\n")) != std::string::npos) {
							std::string line = client->getInputBuffer().substr(0, pos);
							client->getInputBuffer().erase(0, pos + 2);

							std::vector<std::vector<std::string> > commands = tokenize(line);
							for (size_t j = 0; j < commands.size(); j++) {
								if (isClientActive(client, this))
									executeCommand(this, client, commands[j]);
								else
									break;
							}
						}
					}
				}
				else {
					std::cout << ITALIC << "Client " << poll_fds[i].fd << " disconnected." << RESET << std::endl;
					Client *client = getClients()[i];
					size_t channelSize = _channels.size();
					if (client) {
						for (size_t j = 0; j < channelSize; j++) {
							Channel *channel = _channels[j];
							if (channel->getClientByName(client->getNickName()) != NULL) {
								channel->removeClient(client);
								if (channel->getClients().size() == 0) {
									removeChannel(channel);
								}
							}
							
						}
						removeClient(client);
					}
				}
			}
		}
	}

	return 0;
}

int Server::handleNewConnexion() {

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(_serverFd, (struct sockaddr*)&client_addr, &client_len);

	if (client_fd >= 0)	{
	
		if (setNonBlocking(client_fd) == 0)	{
			_clients.push_back(new Client(client_fd));
		}
		else {
			close(client_fd);
			return -1;
		}
	}
	return 0;
}

std::vector<struct pollfd> Server::getPollFds()
{
	std::vector<struct pollfd> poll_fds;

	poll_fds.push_back((struct pollfd){_serverFd, POLLIN, 0});
	
	for (size_t i = 1; i < _clients.size(); i++) {
		poll_fds.push_back((struct pollfd){_clients[i]->getClientFd(), POLLIN, 0});
	}
	return poll_fds;
}

std::vector<Client *> Server::getClients() { return _clients; }

void Server::addChannel(Channel *channel) { _channels.push_back(channel); }

std::vector<Channel *> Server::getChannels() { return _channels; }

std::string Server::getPassword() const { return _password; }


void Server::removeClient(Client* client) {
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i] == client) {
			close(client->getClientFd());
			_clients.erase(_clients.begin() + i);
			delete client;
			break;
		}
	}
}

void Server::removeChannel(Channel *channel) {
	
	for (size_t i = 0; i < _channels.size(); i++) {
		if (_channels[i] == channel) {
			_channels.erase(_channels.begin() + i);
			delete channel;
			break;
		}
	}
}

Channel *Server::getChannelByName(std::string channelName) {

	std::vector<Channel *> channel = getChannels();

	for (size_t i = 0; i < channel.size(); i++) {
		if (channel[i]->getName() == channelName)
			return channel[i];
	}

	return NULL;
}

Client *Server::getClientByName(std::string clientName) {

	std::vector<Client *> client = getClients();

	for (size_t i = 0; i < client.size(); i++) {
		if (client[i]->getNickName() == clientName)
			return client[i];
	}

	return NULL;
}
