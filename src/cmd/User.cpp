/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:38 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 00:40:16 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void userCommand(Client *client, std::vector<std::string> command)
{
	// std::cout << "USER command" << std::endl;

	size_t 	commandSize = command.size();

	// for (size_t i = 0; i < commandSize; i++)
	// 	std::cout << "command [" << i << "] == " << command[i] << std::endl;

	if (client->getRealName() != "")
		std::cout << "Already logged (need to send : ERR_ALREADYREGISTRED (462))" << std::endl;
	else if (commandSize <= 3)
		std::cout << "Too few parameter (need to send ERR_NEEDMOREPARAMS (461))" << std::endl;
	else
	{
		client->setUSerName(command[1]);
		// std::cout << "Username = " << command[1] << std::endl;

		std::string realName;
		for (size_t i = 4; i < commandSize; i++)
		{
			realName += command[i];
			if (i < commandSize - 1)
				realName += " ";
		}
		client->setRealName(realName);
		// std::cout << "Realname = " << realName << std::endl;
	}
}