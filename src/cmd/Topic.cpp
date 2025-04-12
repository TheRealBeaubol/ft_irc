/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:35 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 22:19:48 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void topicCommand(Server *server, Client *client, std::vector<std::string> command) {
    
    if (command.size() < 2) {
        SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " TOPIC :Not enough parameters\r\n");
    }
    
    std::string channelName = command[1];
    Channel *channel = server->getChannelByName(channelName);
    
    if (channel == NULL) {
        SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOSUCHCHANNEL + " " + client->getNickName() + " " + channelName + " :No such channel\r\n");
    }
    if (channel->getClientByName(client->getNickName()) == NULL) {
        SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_NOTONCHANNEL + " " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n");
    }
    if (channel->getTopicUserAccess() == false && channel->getClientParam(client)[OPERATOR] == false) {
        SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + ERR_CHANOPRIVSNEEDED + " " + client->getNickName() + " " + channelName + " :You're not channel operator\r\n");
    }
    if (command.size() == 2) {
        std::string topic = channel->getTopic();
    
        if (topic == "") {
            SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + RPL_NOTOPIC + " " + client->getNickName() + " " + channelName + " :No topic set\r\n");
        }
        
        SEND_MESSAGE_AND_RETURN(":" + std::string(SERVER_NAME) + " " + RPL_TOPIC + " " + client->getNickName() + " " + channelName + " :" + topic + "\r\n" +
                               ":" + std::string(SERVER_NAME) + " " + RPL_TOPICWHOTIME + " " + client->getNickName() + " " + channelName + " " + channel->getTopicAuthor() + "\r\n");
    }
   
    std::string newTopic = command[2];
    channel->setTopic(newTopic);
    channel->setTopicAuthor(client->getNickName());

    channel->broadcastChannel(":" + client->getNickName() + "!" + client->getUserName() + "@localhost TOPIC " + channelName + " " + newTopic + "\r\n", NULL);
}