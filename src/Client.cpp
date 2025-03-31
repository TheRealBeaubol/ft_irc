/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:48:50 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 00:58:31 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

Client::Client(){}

Client::~Client(){}

Client::Client(int clientSocket) {

	std::cout << BOLD YELLOW << "Client has been created with " << clientSocket << " as clientSocket" << std::endl;
	_clientSocket = clientSocket;
	setNickName("eplouzen");
}

void Client::setClientSocket( int clientSocket ) { _clientSocket = clientSocket; }
int Client::getClientSocket() const { return _clientSocket; }

void Client::setNickName( std::string nick_name ) { _nickName = nick_name; }
std::string Client::getNickName() const { return _nickName; }

void Client::setRealName( std::string real_name ) { _realName = real_name; }
std::string Client::getRealName() const { return _realName; }