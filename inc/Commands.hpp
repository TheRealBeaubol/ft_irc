/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:43:22 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 01:52:29 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Includes.hpp"
#include "Server.hpp"
#include "Client.hpp"

void    execute_command(Server *server, Client *client, std::vector<std::string> command);

void	joinCommand(Server *server, Client *client, std::vector<std::string> commands);

void	passCommand(Server *server, Client *client, std::vector<std::string> commands);