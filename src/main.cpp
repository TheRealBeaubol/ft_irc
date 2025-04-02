/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:18:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 02:55:48 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"


std::vector<std::string> splitBufferIntoLines(const std::string &buffer) {
    
	const std::string &delim = "\r\n";
	std::vector<std::string> lines;
    size_t pos = 0;
    while (pos < buffer.size()) {
        size_t end = buffer.find(delim, pos);
        if (end == std::string::npos)
            end = buffer.size();
        std::string line = buffer.substr(pos, end - pos);
        if (!line.empty())
            lines.push_back(line);
        pos = (end == buffer.size() ? end : end + delim.size());
    }
    return lines;
}

std::vector<std::string> tokenizeLine(const std::string &line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    bool lastParamFound = false;
    
    while (iss >> token) {
        if (!lastParamFound && token[0] == ':') {
            std::string lastParam = token.substr(1);
            std::string rest;
            std::getline(iss, rest);
            lastParam += rest;
            tokens.push_back(lastParam);
            lastParamFound = true;
            break;
        } else {
            tokens.push_back(token);
        }
    }
    return tokens;
}

std::vector<std::vector<std::string> > tokenize(std::string buffer) {
    std::vector<std::vector<std::string> > allTokens;
    std::vector<std::string> lines = splitBufferIntoLines(buffer);
    
    for (size_t i = 0; i < lines.size(); ++i)
        allTokens.push_back(tokenizeLine(lines[i]));
    
    return allTokens;
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


