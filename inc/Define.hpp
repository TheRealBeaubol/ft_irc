/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:59:49 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 00:37:11 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define BUFFER_SIZE 1024
#define SERVER_NAME "IRCServer"

#define SEND_MESSAGE_AND_RETURN(msg) {                              \
    const std::string _msg = msg;                                   \
    send(client->getClientSocket(), _msg.c_str(), _msg.size(), 0);  \
    std::cout << BOLD RED << _msg << RESET;                         \
    return;                                                         \
}

#define SEND_MESSAGE(msg) {                                         \
    const std::string _msg = msg;                                   \
    send(client->getClientSocket(), _msg.c_str(), _msg.size(), 0);  \
    std::cout << RED << _msg << RESET;                         \
}