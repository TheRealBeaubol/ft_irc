/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:48:50 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 22:06:52 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

Client::Client(){}

Client::~Client(){}

Client::Client(int clientSocket) {

	std::cout << BOLD YELLOW << "Client has been created with " << clientSocket << " as clientSocket" << std::endl;
	_clientSocket = clientSocket;
	_isAuth = false;
	_isLog = false;
	setNickName("");
	setUserName("");
	_channels = std::vector<Channel *>();
}

void Client::setClientSocket( int clientSocket ) { _clientSocket = clientSocket; }
int Client::getClientSocket() const { return _clientSocket; }

void Client::setNickName( std::string nick_name ) { _nickName = nick_name; }
std::string Client::getNickName() const { return _nickName; }

void Client::setUserName(std::string user_name) { _userName = user_name; }
std::string Client::getUserName() const { return _userName; }

void Client::setIsLog( bool isLog ) { _isLog = isLog; }
bool Client::getIsLog() const { return _isLog; }

void Client::setIsAuth( bool isAuth ) { _isAuth = isAuth; }
bool Client::getIsAuth() const { return _isAuth; }

void Client::addChannel( Channel *channel ) { _channels.push_back(channel); }
void Client::removeChannel( Channel *channel ) { _channels.erase(std::remove(_channels.begin(), _channels.end(), channel), _channels.end()); }
std::vector<Channel *> Client::getChannels() const { return _channels; }