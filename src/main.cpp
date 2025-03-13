/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:18:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/13 18:00:23 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdio.h> 
#include <fcntl.h>
#include <vector>
#include <poll.h>
#include "colors.hpp"

#define BUFFER_SIZE 1024

std::string repeatChar(int n, const std::string& s) {
    std::string result;
    result.reserve(n * s.size());
    for (int i = 0; i < n; ++i) {
        result += s;
    }
    return result;
}

void drawBox(int width, std::string const title) {
    
    std::string errorText = "ERROR:";
    int leftPadding = (width - errorText.size()) / 2;
    int rightPadding = width - errorText.size() - leftPadding;
    std::cout << BOLD RED << "╔" << repeatChar(width, "═") << "╗" << std::endl << VERTICAL << repeatChar(width, " ") << VERTICAL << std::endl;
    std::cout << VERTICAL << repeatChar(leftPadding, " ") << errorText << repeatChar(rightPadding, " ") << VERTICAL << std::endl;

    leftPadding = (width - title.size()) / 2;
    rightPadding = width - title.size() - leftPadding;
    std::cout << VERTICAL << repeatChar(leftPadding, " ") << title << repeatChar(rightPadding, " ") << VERTICAL << std::endl;
    std::cout << VERTICAL << repeatChar(width, " ") << VERTICAL << std::endl;
    std::cout << "╚" << repeatChar(width, "═") << "╝" << RESET << std::endl;
}


void perror(const char *msg) {
    std::cerr << msg << ": " << strerror(errno) << std::endl;
}

int stoi(const char *str) {
    int result = 0;
    for (int i = 0; str[i]; i++) {
        result = result * 10 + str[i] - '0';
    }
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

int main(int ac, char **av) {
    
    if (ac != 3) {
        drawBox(50, "Usage: ./ircserv [port] [password]");
        return 1;
    }
    
    int port = stoi(av[1]);
    std::cout << BOLD BLUE << "Port: " << port << std::endl;
    
    const char* password = av[2];
    (void)password;

    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    std::cout << GREEN << "Socket created !" << std::endl;
    std::cout << GREEN << "Server fd: " << server_fd << std::endl;
    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        return 1;
    }  
    
    std::cout << GREEN << "Socket options set !" << std::endl;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    if (bind(server_fd, (sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind");
        return 1;
    }

    std::cout << GREEN << "Socket binded !" << std::endl;
    
    if (listen(server_fd, SOMAXCONN) == -1) {
        perror("listen");
        return 1;
    }

    std::cout << GREEN << "Server listening !" << std::endl;

    if (setNonBlocking(server_fd) == -1) {
        perror("setNonBlocking");
        return 1;
    }

    std::cout << GREEN << "Server set to non-blocking !" << std::endl;

    std::vector<struct pollfd> poll_fds;

    struct pollfd server_pollfd;
    server_pollfd.fd = server_fd;
    server_pollfd.events = POLLIN;
    server_pollfd.revents = 0;
    poll_fds.push_back(server_pollfd);

    std::cout << GREEN << "Server listening on port : " << port << std::endl;
    

    while (true) {
        // Wait indefinitely (-1) for an event on any socket in the poll_fds vector
        int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
        if (poll_count < 0) {
            perror("poll failed");
            break;
        }

        // Check if there's an event on the server socket (new connection)
        if (poll_fds[0].revents & POLLIN) {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
            if (client_fd >= 0) {
                // Set the new client socket to non-blocking mode
                if (setNonBlocking(client_fd) == 0) {
                    struct pollfd client_pollfd;
                    client_pollfd.fd = client_fd;
                    client_pollfd.events = POLLIN; // Monitor for incoming data
                    client_pollfd.revents = 0;
                    poll_fds.push_back(client_pollfd);
                    std::cout << "Accepted new client: " << client_fd << std::endl;
                } else {
                    close(client_fd);
                }
            }
        }

        // Iterate over the client sockets (starting at index 1, as index 0 is the server)
        for (size_t i = 1; i < poll_fds.size(); ++i) {
            if (poll_fds[i].revents & POLLIN) {
                char buffer[BUFFER_SIZE];
                int bytes_read = recv(poll_fds[i].fd, buffer, BUFFER_SIZE, 0);
                if (bytes_read <= 0) {
                    // If bytes_read is 0, the client disconnected or an error occurred
                    std::cout << "Client " << poll_fds[i].fd << " disconnected." << std::endl;
                    close(poll_fds[i].fd);
                    poll_fds.erase(poll_fds.begin() + i);
                    --i; // Adjust the index after erasing an element
                } else {
                    // Null-terminate and print the received data
                    buffer[bytes_read] = '\0';
                    std::cout << "Received from client " << poll_fds[i].fd << ": " << buffer;
                    // Here, you would typically parse and handle the client's commands
                }
            }
        }
    }

    // Clean up: close all sockets
    for (size_t i = 0; i < poll_fds.size(); ++i) {
        close(poll_fds[i].fd);
    }
    return 0;
}


