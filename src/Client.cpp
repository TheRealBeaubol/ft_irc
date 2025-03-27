/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:48:50 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/27 23:38:01 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

Client::Client(){}

Client::~Client(){}

Client::Client(int clientSocket) {

	std::cout << "Client been created with " << clientSocket << " as clientSocket" << std::endl;
	_clientSocket = clientSocket;
}

void Client::setClientSocket( int clientSocket ) { _clientSocket = clientSocket; }
int Client::getClientSocket() { return _clientSocket; }

void Client::setNickName( std::string nick_name ) { _nickName = nick_name; }
std::string Client::getNickName() { return _nickName; }

void Client::setRealName( std::string real_name ) { _realName = real_name; }
std::string Client::getRealName() { return _realName; }