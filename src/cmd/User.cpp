/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:39:38 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 00:09:42 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void userCommand(Client *client, std::vector<std::string> command) {

	if (client->getRealName() != "")
		std::cout << "Already logged (need to send : ERR_ALREADYREGISTRED (462))" << std::endl;
	else if (command.size() < 2)
		std::cout << "Too few parameter (need to send ERR_NEEDMOREPARAMS (461))" << std::endl;
	else
	{
		client->setUserName(command[1]);

		std::string realName;
		for (size_t i = 4; i < command.size(); i++)
		{
			realName += command[i];
			if (i < command.size() - 1)
				realName += " ";
		}
		client->setRealName(realName);
	}
}