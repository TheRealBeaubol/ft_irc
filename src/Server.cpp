/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:35:55 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 22:07:35 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"
#include <iostream>

int setNonBlocking(int fd) {
	
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) { return -1; }
	
    flags |= O_NONBLOCK;
    
	if (fcntl(fd, F_SETFL, flags) == -1) { return -1; }
    return 0;
}

Server::Server(int port, std::string password)
{

	std::cout << std::endl << BOLD BLUE << "Creating default IRC Server on the "<< port << " port" << RESET << std::endl << std::endl;

	std::cout << BOLD BLUE << "============ SERVER CREATION ============" << RESET << std::endl;
	
	_port = port;
	_password = password;
	
	_serverFd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( _serverFd == -1 ) { std::cerr << BOLD RED << "Error while creating socket" << RESET << std::endl; }
	std::cout << BOLD GREEN << "Socket created !" << std::endl;
   
	int opt = 1;
	if ( setsockopt( _serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) == -1 ) {	std::cerr << BOLD RED << "Error while setting socket options" << RESET << std::endl; }
    std::cout << "Socket options set !" << std::endl;

    sockaddr_in address = {AF_INET, htons( port ), {INADDR_ANY}, {0}};

	if ( bind( _serverFd, ( struct sockaddr* )&address, sizeof( address ) ) == -1 ) { std::cerr << BOLD RED << "Error while binding socket" << RESET << std::endl; }
	std::cout << "Socket binded !" << std::endl;

	if ( listen( _serverFd, SOMAXCONN ) == -1 ) { std::cerr << BOLD RED << "Error while listening" << RESET << std::endl; }
    std::cout << "Server listening !" << std::endl;

	if ( setNonBlocking( _serverFd ) == -1 ) { std::cerr << BOLD RED << "Error while setting non-blocking" << RESET << std::endl; }
	std::cout << "Server set to non-blocking !" << RESET << std::endl;

	std::cout << BOLD ORANGE << "Creating a new client for the server : " << std::endl << "	";
	Client *client = new Client( _serverFd );
	client->setIsAuth(true);
	client->setIsLog(true);
	std::cout << "getIsAuth() : " << client->getIsAuth() << std::endl;
	_clients.push_back( client );
	std::cout << std::endl << RESET ;
	
	_pollFds.push_back( ( struct pollfd ) {_serverFd, POLLIN, 0} );

    std::cout << BOLD GREEN << "Server listening on port : " << _port << std::endl << RESET;
	std::cout << BOLD BLUE << "=========================================" << std::endl << std::endl << RESET;
}

Server::~Server(){}

void Server::removePollFd(struct pollfd poll_fd)
{
	
	for (size_t i = 0; i < _pollFds.size(); i++) {
		if ( (_pollFds[i].fd == poll_fd.fd) && (i < _pollFds.size()) )
		{
			std::cout << "Removing " << poll_fd.fd << " from Server.poll_fds " << std::endl;
			_pollFds.erase(_pollFds.begin() + i);
		}
	}
}

int Server::handleNewConnexion()
{

	std::cout << BOLD BLUE << "------------- NEW CONNEXION -------------" << RESET << std::endl;

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(_serverFd, (struct sockaddr*)&client_addr, &client_len);
	if (client_fd >= 0)	{
		if (setNonBlocking(client_fd) == 0)
		{
			Client *client = new Client(client_fd);
			_clients.push_back(client);
			struct pollfd poll_fd = {client_fd, POLLIN, 0};
			_pollFds.push_back(poll_fd);
			send(client->getClientSocket(), "Welcome to the IRC server !\n", 28, 0);
		}
		else
		{
			close(client_fd);
			std::cout << BOLD BLUE << "-----------------------------------------" << std::endl << std::endl << RESET;
			return -1;
		}
	}
	std::cout << BOLD BLUE << "-----------------------------------------" << std::endl << std::endl << RESET;
	return 0;
}

void Server::sendMessage(int clientSocket, const char *msg)
{
	std::cout << BOLD LIGHTBLUE << "Sending message : " << RESET LIGHTBLUE << std::endl << "	" << msg << RESET;
	send(clientSocket, msg, strlen(msg), 0);
}

void Server::removeClient(Client* client)
{
	
	std::cout << "Removing " <<  client->getClientSocket() << " from server.clients " << std::endl;
	
	for (size_t i = 0; i < _clients.size(); i++){
		if ( (_clients[i] == client) && (i < _clients.size()) )
		{
			_clients.erase(_clients.begin() + i);
		}
	}
}

void Server::addChannel(Channel *channel) { 
	_channels.push_back(channel);
}

void Server::removeChannel(Channel *channel) { 
	_channels.erase(std::remove(_channels.begin(), _channels.end(), channel), _channels.end());
}

std::vector<Channel *> Server::getChannel() { return _channels; }
std::vector<struct pollfd> Server::getPollFds() { return _pollFds; }
std::vector<Client *> Server::getClients() { return _clients; }
std::string Server::getPassword() const { return _password; }

Channel *Server::findChannel(std::string channelName)
{
	std::vector<Channel *> channel = Server::getChannel();
	for (size_t i = 0; i < channel.size(); i++)
	{
		if ("#" + channel[i]->getChannelName() == channelName)
			return channel[i];
	}
	return NULL;
}
Client *Server::findClient(std::string clientName)
{
	std::vector<Client *> client = Server::getClients();
	for (size_t i = 0; i < client.size(); i++)
	{
		if (client[i]->getNickName() == clientName)
			return client[i];
	}
	return NULL;
}
