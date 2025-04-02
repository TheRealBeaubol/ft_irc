/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 00:37:35 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 19:49:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"


void topicCommand(Server *server, Client *client, std::vector<std::string> command) {

    std::string msg;
    
    if (command.size() < 2) {
        std::cout << BOLD RED << "Error: Not enough arguments" << RESET << std::endl;
        return ;
    }
    
    std::string channelName = command[1];
    std::string serverName = std::string(SERVER_NAME);
    
    Channel *channel = server->findChannel(channelName);
    if (channel == NULL) {
        msg = ":" + serverName + " 403 " + client->getNickName() + " " + channelName + " :No such channel\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        std::cout << BOLD RED << msg << RESET;
        return ;
    }
    if (channel->getClientByName(client->getNickName()) == NULL) {
        msg = ":" + serverName + " 442 " + client->getNickName() + " " + channelName + " :You're not on that channel\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        std::cout << BOLD RED << msg << RESET;
        return ;
    }
    if (channel->getTopicUserAccess() == true && channel->getClientParam(client)[2] == false) {
        msg = ":" + serverName + " 482 " + client->getNickName() + " " + channelName + " :You're not channel operator\r\n";
        send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
        std::cout << BOLD RED << msg << RESET; 
        return ;
    }    
    if (command.size() == 2) {
        std::string topic = channel->getTopic();
        if (topic == "")
        {
            msg = ":" + serverName + " 331 " + client->getNickName() + " " + channelName + " :No topic set\r\n";
            send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
            std::cout << BOLD GREEN << msg << RESET;
        }
        else
        {
            msg = ":" + serverName + " 332 " + client->getNickName() + " " + channelName + " :" + topic + "\r\n";
            msg += ":" + serverName + " 333 " + client->getNickName() + " " + channelName + " " + channel->getTopicAuthor() + "\r\n";
            send(client->getClientSocket(), msg.c_str(), msg.size(), 0);
            std::cout << BOLD GREEN << msg << RESET;
        }
    }
    else {

        std::string newTopic = command[2];
        channel->setTopic(newTopic);
        channel->setTopicAuthor(client->getNickName());
        
        msg = ":" + client->getNickName() + "!" + client->getUserName() + "@localhost TOPIC " + channelName + " " + newTopic + "\r\n";
        channel->broadcastChannel(msg, NULL);
        
        std::cout << BOLD GREEN << "Topic set to " << newTopic << RESET << std::endl;
    }
}