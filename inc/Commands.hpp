/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:43:22 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 17:08:55 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Includes.hpp"
#include "Server.hpp"
#include "Client.hpp"

void    execute_command(Server *server, Client *client, std::vector<std::string> command);

void	joinCommand(Server *server, Client *client, std::vector<std::string> commands);

void    commandNick(Server *server, Client *client, std::vector<std::string> commands);

void	passCommand(Server *server, Client *client, std::vector<std::string> commands);

void    topicCommand(Server *server, Client *client, std::vector<std::string> command);

void    userCommand(Client *client, std::vector<std::string> command);

void	commandKick(Server *server, Client *client, std::vector<std::string> command);

