/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:35 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 21:23:03 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"


void topicCommand(Server *server, Client *client, std::vector<std::string> command) {

    std::string serverName = std::string(SERVER_NAME);
    std::string msg;
    
    if (command.size() < 2) {
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 461 " + client->getNickName() + " TOPIC :Not enough parameters\r\n");
    }
    
    std::string channelName = command[1];
    std::string newTopic = command[2];
    Channel *channel = server->getChannelByName(channelName);
    
    if (channel == NULL) {
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 403 " + client->getNickName() + " " + channelName + " :No such channel\r\n");
    }
    if (channel->getClientByName(client->getNickName()) == NULL) {
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 442 " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n");
    }
    if (channel->getTopicUserAccess() == false && channel->getClientParam(client)[OPERATOR] == false) {
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 482 " + client->getNickName() + " " + channelName + " :You're not channel operator\r\n");
    }
    if (command.size() == 2) {
        std::string topic = channel->getTopic();
    
        if (topic == "") {
            SEND_MESSAGE_AND_RETURN(":" + serverName + " 331 " + client->getNickName() + " " + channelName + " :No topic set\r\n");
        }
        
        SEND_MESSAGE_AND_RETURN(":" + serverName + " 332 " + client->getNickName() + " " + channelName + " :" + topic + "\r\n" +
                               ":" + serverName + " 333 " + client->getNickName() + " " + channelName + " " + channel->getTopicAuthor() + "\r\n");
    }
   
    channel->setTopic(newTopic);
    channel->setTopicAuthor(client->getNickName());
    
    msg = ":" + client->getNickName() + "!" + client->getUserName() + "@localhost TOPIC " + channelName + " " + newTopic + "\r\n";
    channel->broadcastChannel(msg, NULL);
}