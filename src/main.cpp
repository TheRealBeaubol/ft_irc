/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:18:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 18:34:40 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

int main(int ac, char **av) {
    
    if (ac != 3 || atoi(av[1]) < 1024)
        drawBoxErrorAndExit(50, "Usage: ./ircserv [port > 1024] [password]");

    Server server(atoi(av[1]), av[2]);	    
    return server.run();
}


