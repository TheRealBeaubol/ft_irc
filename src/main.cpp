/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:18:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/31 21:33:58 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

int stoi(const char *str) {
    int result = 0;
    for (int i = 0; str[i]; i++) { result = result * 10 + str[i] - '0'; }
    return result;
}

void send_message(int clientSocket, const char *msg) { send(clientSocket, msg, strlen(msg), 0); }

std::vector<std::string> split(const std::string& str, char delimiter) {

	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string item;

	// Utilisation de getline pour séparer la chaîne au niveau du délimiteur
	while (getline(ss, item, delimiter)) {
		result.push_back(item);
	}

	return result;
}

std::vector<std::vector<std::string> > tokenize(std::string buffer) {

	std::vector<std::vector<std::string> > res;

	std::vector<std::string> commands = split(buffer, '\n');
	for (size_t i = 0; i < commands.size(); i++) {
		res.push_back(split(commands[i], ' '));
	}
	
	return res;
}


void	joinCommand(Server *server, Client *client, std::vector<std::string> commands)
{
	std::cout << BOLD GREEN << "User used the JOIN command with : [ " << commands[1] << " ]" << RESET << std::endl;
	
	commands[1].erase(std::remove(commands[1].begin(), commands[1].end(), '\n'), commands[1].end()); //faut vraiment remplacer cette ligne ptdrrrrr
	commands[1].erase(std::remove(commands[1].begin(), commands[1].end(), '\r'), commands[1].end()); //faut vraiment remplacer cette ligne ptdrrrrr
	
	size_t 	channelSize = server->getChannel().size();

	for (size_t i = 0; i < channelSize + 1; i++)
	{
		std::string	msg = ":" + client->getNickName() + " JOIN :#" + commands[1] + "\r\n";
	
		if ( i < channelSize)
		{
			std::cout << GREEN << "Channel [ " << server->getChannel()[i]->getChannelName() << " ] exists, user joined it" << RESET << std::endl;
			if ( server->getChannel()[i]->getChannelName() == commands[1])
			{
				server->getChannel()[i]->addClient(client);
				server->getChannel()[i]->showClient();
				server->sendMessage(client->getClientSocket(), msg.c_str());
			}
		}
		else if (i == channelSize)
		{
			std::cout << BOLD GREEN << "The [ " << commands[1] << " ] channel doesn't exists, it will be created" << std::endl;
			Channel *channel = new Channel(commands[1]);
			server->addChannel(channel);
			server->getChannel()[i]->addClient(client);
			server->getChannel()[i]->showClient();
			server->sendMessage(client->getClientSocket(), msg.c_str());
			return;
		}
	}
}

void execute_command(Server *server, Client *client, std::vector<std::string> command) {

	if (command[0] == "PASS") {
		std::cout << "PASS command " ;

		if (command[1] == PASSWORD)	
		{
			std::cout << "(Correct password)" << std::endl;
			// Client is allowed to talk on the server
		}
		else
		{
			std::cout << "(Incorrect password)" << std::endl ;
			// Got to close this socket
		}
	}

	else if (command[0] == "NICK") {
		std::cout << "NICK command" << std::endl;
	}

	else if (command[0] == "USER")
	{
		std::cout << "USER command" << std::endl;
	}

	else if (command[0] == "JOIN")
	{
		joinCommand(server, client, command);
	}

	else if (command[0] == "PRIVMSG")
	{
		std::cout << "PRIVMSG command" << std::endl;
	}

	else if (command[0] == "QUIT")
	{
		std::cout << "QUIT command" << std::endl;
	}

	else
	{
		std::cout << "Commande inconnue (" << command[0] << ")" << std::endl;
	}
}

int handle_message(Server *server, Client *client, std::string buffer) {

	std::cout << std::endl << BOLD CYAN << "Message receive from [" << client->getNickName() << "] : {"<< buffer << "}" RESET << std::endl;

	std::vector<std::vector<std::string> > commands = tokenize(buffer);

	for (size_t i = 0; i < commands.size(); i++) {
		execute_command(server, client, commands[i]);
	}
	std::cout << std::endl;

	// Répondre avec un message IRC simple
	send_message(client->getClientSocket(), "Message reçu!\r\n");

	return 0;
}

int main(int ac, char **av) {
    
    if (ac != 3)
	{
        drawBox(50, "Usage: ./ircserv [port] [password]");
        return 1;
    }

    Server *server = new Server(stoi(av[1]));

    while (true) {
	
		std::vector<struct pollfd> poll_fds = server->getPollFds();

        int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
        if (poll_count < 0) 
		{
            std::cerr << "poll failed" << ": " << strerror(errno) << std::endl;
            break;
        }

        if (poll_fds[0].revents & POLLIN && server->handleNewConnection() == -1)
		{
			std::cerr << "handleNewConnection failed" << ": " << strerror(errno) << std::endl;
            continue;
        }

        for (size_t i = 1; i < poll_fds.size(); ++i)
		{
            if (poll_fds[i].revents & POLLIN)
			{
                char buffer[BUFFER_SIZE];
				memset(buffer, 0, BUFFER_SIZE);
                int bytes_read = recv(poll_fds[i].fd, buffer, BUFFER_SIZE, 0);
                std::string s_buffer = std::string(buffer);
                s_buffer.erase(std::remove(s_buffer.begin(), s_buffer.end(), '\r'), s_buffer.end());

                if (bytes_read > 0)
				{
					Client *client = server->getClients()[i];

                    if (client)
					{
						std::cout << GREEN << client->getClientSocket() << " is clients[" << i << "]" << std::endl;
						handle_message(server, client, s_buffer);
					}
	
					else
					{
						std::cout << "No client at index : " << i << std::endl;
					}
				}

				else
				{
					std::cout << "Client " << poll_fds[i].fd << " disconnected." << std::endl;
					std::cout << "i = " << i << std::endl;
					close(poll_fds[i].fd);
					server->removePollFd(poll_fds[i]);
					server->removeClient(server->getClients()[i]);
				}
            }
        }
    }
	// for (size_t i = 0; i < poll_fds.size(); ++i) { close(poll_fds[i].fd); }
    return 0;
}


