/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:18:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/14 23:59:03 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

class Client {
    private:
        int _socket_fd;
        bool _authenticated;
        std::string _username;
        std::string _nickname;
        std::vector<std::string> _channels;
        std::string _recvBuffer;
    public:
        Client(int socket_fd);
        ~Client();
        int getSocketFd() const;
        void setAuthenticated(bool authenticated);
        bool getAuthenticated() const;
        void setUsername(std::string username);
        std::string getUsername() const;
        void setNickname(std::string nickname);
        std::string getNickname() const;
        void addChannel(std::string channel);
        void removeChannel(std::string channel);
        void appendToRecvBuffer(std::string buffer);
        std::string getRecvBuffer() const;
};