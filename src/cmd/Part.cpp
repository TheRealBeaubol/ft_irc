/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:36:00 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 19:33:26 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	partCommand(Server *server, Client *client, std::vector<std::string> command) {
    
    Channel *channel = server->findChannel(command[1]);
    if (!channel)
        return ;
    client->removeChannel(channel);
    channel->eraseClient(client);

    std::string msg = ":" + client->getNickName() + " PART #" + channel->getChannelName() + "\r\n";
    channel->broadcastChannel(msg, NULL);
}