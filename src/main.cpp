/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:18:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 03:01:59 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

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

int handle_message(Server *server, Client *client, std::string buffer) {

	std::vector<std::vector<std::string> > commands = tokenize(buffer);

	for (size_t i = 0; i < commands.size(); i++) {
		execute_command(server, client, commands[i]);
	}

	// send(client->getClientSocket(), "Message reçu!\r\n", 15, 0);
	return 0;
}

int main(int ac, char **av) {
    
    if (ac != 3)
	{
        drawBox(50, "Usage: ./ircserv [port] [password]");
        return 1;
    }
	if (atoi(av[1]) < 1024)
	{
		drawBox(50, "Port must be greater than 1024");
		return 1;
	}

    Server *server = new Server(atoi(av[1]), av[2]);	

    while (true) {
	
		std::vector<struct pollfd> poll_fds = server->getPollFds();

        int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
		if (poll_count < 0) 
		{
            std::cerr << "poll failed" << ": " << strerror(errno) << std::endl;
            break;
        }

        if (poll_fds[0].revents & POLLIN && server->handleNewConnexion() == -1)
		{
			std::cerr << "handleNewConnexion failed" << ": " << strerror(errno) << std::endl;
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


