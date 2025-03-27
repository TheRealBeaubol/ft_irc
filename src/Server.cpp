/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:35:55 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/27 23:25:18 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

int setNonBlocking(int fd) {
	
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) { 
        return -1; 
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        return -1;
    }
    return 0;
}

Server::Server(int port)
{

	std::cout << BOLD BLUE << "Creating default IRC Server" << RESET << std::endl;

	_port = port;
	_serverFd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( _serverFd == -1 ) { std::cerr << BOLD RED << "Error while creating socket" << RESET << std::endl; }
	std::cout << "Port: " << port << std::endl << GREEN << "Socket created !" << std::endl << "Server fd: " << _serverFd << std::endl;
   
	int opt = 1;
	if ( setsockopt( _serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) == -1 ) {	std::cerr << BOLD RED << "Error while setting socket options" << RESET << std::endl; }
    std::cout << GREEN << "Socket options set !" << std::endl;

    sockaddr_in address = {AF_INET, htons( port ), {INADDR_ANY}, {0}};

	if ( bind( _serverFd, ( struct sockaddr* )&address, sizeof( address ) ) == -1 ) { std::cerr << BOLD RED << "Error while binding socket" << RESET << std::endl; }
	std::cout << GREEN << "Socket binded !" << std::endl;

	if ( listen( _serverFd, SOMAXCONN ) == -1 ) { std::cerr << BOLD RED << "Error while listening" << RESET << std::endl; }
    std::cout << GREEN << "Server listening !" << std::endl;

	if ( setNonBlocking( _serverFd ) == -1 ) { std::cerr << BOLD RED << "Error while setting non-blocking" << RESET << std::endl; }
	std::cout << GREEN << "Server set to non-blocking !" << std::endl;

	_clients.push_back( new Client( _serverFd ) );
	_pollFds.push_back( ( struct pollfd ) {_serverFd, POLLIN, 0} );

    std::cout << GREEN << "Server listening on port : " << _port << std::endl;
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

int Server::handleNewConnection()
{

	std::cout << "Handling new connection" << std::endl;

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(_serverFd, (struct sockaddr*)&client_addr, &client_len);
	if (client_fd >= 0)	{
		if (setNonBlocking(client_fd) == 0)
		{
			std::cout << "New connexion accepted: " << client_fd << std::endl;

			Client *client = new Client(client_fd);
			std::cout << "Adding " << client->getClientSocket() << " to serveur.clients " << _clients.size() << std::endl;
			_clients.push_back(client);
			struct pollfd poll_fd = {client_fd, POLLIN, 0};
			std::cout << "Adding " << poll_fd.fd << " to serveur.poll_fds " << _pollFds.size() << std::endl;
			_pollFds.push_back(poll_fd);
		}
		else
		{
			close(client_fd);
			return -1;
		}
	}
	return 0;
}

void Server::sendMessage(int clientSocket, const char *msg)
{
	std::cout << "Sending message : " << msg << std::endl;
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

std::vector<struct pollfd> Server::getPollFds() { return _pollFds; }
std::vector<Client *> Server::getClients() { return _clients; }