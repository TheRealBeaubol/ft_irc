/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:18:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/15 00:51:26 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

int stoi(const char *str) {
    int result = 0;
    for (int i = 0; str[i]; i++) { result = result * 10 + str[i] - '0'; }
    return result;
}

int setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) { 
        return -1; 
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        return -1;
    }
    return 0;
}

int checkFailure(int ret, const char *msg) {
    if (ret == -1) {
        std::cerr << msg << ": " << strerror(errno) << std::endl;
        return 1;
    }
    return 0;
}

struct pollfd initPollfd(int fd) { return (struct pollfd) {fd, POLLIN, 0}; }

int main(int ac, char **av) {
    
    if (ac != 3) {
        drawBox(50, "Usage: ./ircserv [port] [password]");
        return 1;
    }
    
    int port = stoi(av[1]);
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (checkFailure(server_fd, "socket")) { return 1; }
    std::cout << BOLD BLUE << "Port: " << port << std::endl << GREEN << "Socket created !" << std::endl << "Server fd: " << server_fd << std::endl;
    
    int opt = 1;
    if (checkFailure(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)), "setsockopt")) { return 1;}  
    std::cout << GREEN << "Socket options set !" << std::endl;

    sockaddr_in address = {AF_INET, htons(port), {INADDR_ANY}, {0}};
    
    if (checkFailure(bind(server_fd, (sockaddr *)&address, sizeof(address)), "bind")) { return 1; }
    std::cout << GREEN << "Socket binded !" << std::endl;
    
    if (checkFailure(listen(server_fd, SOMAXCONN), "listen")) { return 1; }
    std::cout << GREEN << "Server listening !" << std::endl;

    if (checkFailure(setNonBlocking(server_fd), "setNonBlocking")) { return 1; }
    std::cout << GREEN << "Server set to non-blocking !" << std::endl;

    std::vector<struct pollfd> poll_fds;
    struct pollfd server_pollfd = initPollfd(server_fd);
    poll_fds.push_back(server_pollfd);
    
    std::cout << GREEN << "Server listening on port : " << port << std::endl;
    
    std::vector<Client *> clientsVector;
    while (true) {
        int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
        if (poll_count < 0) {
            std::cerr << "poll failed" << ": " << strerror(errno) << std::endl;
            break;
        }
        if (poll_fds[0].revents & POLLIN) {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
            if (client_fd >= 0) {
                if (setNonBlocking(client_fd) == 0) {
                    struct pollfd client_pollfd = initPollfd(client_fd);
                    poll_fds.push_back(client_pollfd);
                    std::cout << "Accepted new client: " << client_fd << std::endl;
                    clientsVector.push_back(new Client(client_fd));
                } else {
                    close(client_fd);
                }
            }
        }
        for (size_t i = 1; i < poll_fds.size(); ++i) {
            if (poll_fds[i].revents & POLLIN) {
                char buffer[BUFFER_SIZE];
                int bytes_read = recv(poll_fds[i].fd, buffer, BUFFER_SIZE, 0);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';
                    Client *client = NULL;
                    for (size_t j = 0; j < clientsVector.size(); ++j) {
                        if (clientsVector[j]->getSocketFd() == poll_fds[i].fd) {
                            client = clientsVector[j];
                            break;
                        }
                    }
                    if (client) {
                        std::string bufferString(buffer);
                        client->appendToRecvBuffer(bufferString);
                        processClientBuffer(client);
                    } else {
                        std::cerr << "No client found for this socket" << std::endl;
                    }
                } else {
                    std::cout << "Client " << poll_fds[i].fd << " disconnected." << std::endl;
                    close(poll_fds[i].fd);
                    poll_fds.erase(poll_fds.begin() + i);
                    clientsVector.erase(clientsVector.begin() + i);
                    --i;
                }
            }
        }
    }
    for (size_t i = 0; i < poll_fds.size(); ++i) { close(poll_fds[i].fd); }
    return 0;
}


