/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:35 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 16:04:18 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void topicCommand(Server *server, Client *client, std::vector<std::string> command) {

    if (command.size() < 2) {
        std::cout << BOLD RED << "Error: Not enough arguments" << RESET << std::endl;
        return ;
    }
    
    std::string channelName = command[1];
    
    Channel *channel = server->findChannel(channelName);
    if (channel == NULL) {
        std::cout << BOLD RED << "Error: Channel not found" << RESET << std::endl;
        return ;
    }
    
    if (command.size() == 2) {
        std::string topic = channel->getTopic();
        if (topic == "")
        {
            std::cout << BOLD GREEN << "No topic is set" << RESET << std::endl;
            send(client->getClientSocket(), "No topic is set\r\n", 17, 0);
        }
        else
        {
            topic = "Topic is : " + topic + "\r\n";
            send(client->getClientSocket(), topic.c_str(), topic.size(), 0);
            std::cout << BOLD GREEN << topic << RESET << std::endl;
        }
    }
    else {
        command[2].erase(std::remove(command[2].begin(), command[2].end(), ':'), command[2].end());
        std::string topic = "";
        for (long unsigned int i = 2; i < command.size(); i++) {
            topic += command[i];
            if (i + 1 < command.size())
                topic += " ";
        }
        channel->broadcastMessage("Topic changed by " + client->getNickName() + " : " + topic + "\r\n", client);
        std::cout << BOLD GREEN << "Topic set to : " << topic << RESET << std::endl;
        channel->setTopic(topic);
    }
}