/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:11:30 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/15 00:55:38 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseMessage.hpp"

void parseCommand(Client *client, std::string message) {
    static int isPrinted;

    std::istringstream iss(message);
    std::string command;
    iss >> command;
    
    std::string argument;
    iss >> argument;

    std::string params;
    std::getline(iss, params);
    
    if (isPrinted != client->getSocketFd()) {
        std::cout << "Message from client " << client->getSocketFd() << ": " << message << std::endl;
        std::cout << "Command: " << command << std::endl;
        std::cout << "Argument: " << argument << std::endl;
        std::cout << "Params: " << params << std::endl;
        isPrinted = 1;
    }
    isPrinted = client->getSocketFd();
}

void processClientBuffer(Client *client) {
    std::string buffer = client->getRecvBuffer();
    size_t pos;
    while ((pos = buffer.find('\n')) != std::string::npos) {
        std::string message = buffer.substr(0, pos);
        buffer.erase(0, pos + 1);
        parseCommand(client, message);
    }
}