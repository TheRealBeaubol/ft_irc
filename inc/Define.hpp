/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:59:49 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 22:27:26 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define BUFFER_SIZE 1024
#define SERVER_NAME "IRCServer"

#define LOGGED 0
#define OPERATOR 1

#define SERVER_RUNNING 1
#define SERVER_STOPPED 0

#define SEND_MESSAGE_AND_RETURN(msg) do {                              \
    const std::string _msg = msg;                                   \
    send(client->getClientFd(), _msg.c_str(), _msg.size(), 0);  \
    std::cout << LIGHTBLUE << _msg << RESET << std::endl;           \
    return;                                                         \
} while (0)

#define SEND_MESSAGE(msg) do {                                         \
    const std::string _msg = msg;                                   \
    send(client->getClientFd(), _msg.c_str(), _msg.size(), 0);  \
    std::cout << LIGHTBLUE << _msg << RESET << std::endl;           \
} while (0)