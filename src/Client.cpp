/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:30:05 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/15 01:46:47 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int socket_fd) : _socket_fd(socket_fd), _authenticated(false), _username(""), _nickname(""), _channels(), _recvBuffer("") {}

Client::~Client() {}

int Client::getSocketFd() const { return _socket_fd; }

void Client::setAuthenticated(bool authenticated) { _authenticated = authenticated; }

bool Client::getAuthenticated() const { return _authenticated; }

void Client::setUsername(std::string username) { _username = username; }

std::string Client::getUsername() const { return _username; }

void Client::setNickname(std::string nickname) { _nickname = nickname; }

std::string Client::getNickname() const { return _nickname; }

void Client::addChannel(std::string channel) { _channels.push_back(channel); }

void Client::removeChannel(std::string channel) {
    for (size_t i = 0; i < _channels.size(); ++i) {
        if (_channels[i] == channel) {
            _channels.erase(_channels.begin() + i);
            break;
        }
    }
}

void Client::appendToRecvBuffer(std::string buffer) { _recvBuffer += buffer; }

std::string Client::getRecvBuffer() const { return _recvBuffer; }