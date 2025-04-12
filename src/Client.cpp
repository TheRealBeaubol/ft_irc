/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:48:50 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 21:40:27 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

Client::Client(){}
Client::~Client(){}

Client::Client(int clientFd) {

	_clientFd = clientFd;
	_isAuth = false;
	_isLog = false;
	_nickName = "";
	_userName = "";
}

void Client::setClientFd( int clientFd ) { _clientFd = clientFd; }
int Client::getClientFd() const { return _clientFd; }

void Client::setNickName( std::string nick_name ) { _nickName = nick_name; }
std::string Client::getNickName() const { return _nickName; }

void Client::setUserName(std::string user_name) { _userName = user_name; }
std::string Client::getUserName() const { return _userName; }

void Client::setIsLog( bool isLog ) { _isLog = isLog; }
bool Client::getIsLog() const { return _isLog; }

void Client::setIsAuth( bool isAuth ) { _isAuth = isAuth; }
bool Client::getIsAuth() const { return _isAuth; }
