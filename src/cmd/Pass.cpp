/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:31 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 03:00:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include <string>

void	passCommand(Server *server, Client *client, std::vector<std::string> commands) {

    std::string password = commands[1];

    if (password == server->getPassword())
    {
        client->setIsAuth(true);
        std::cout << LIGHTMAGENTA << "Password accepted" << RESET << std::endl;
    }
    else
    {
        std::cout << LIGHTMAGENTA << "Password incorrect" << RESET << std::endl;
    }
}