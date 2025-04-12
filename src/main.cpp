/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:18:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 17:36:12 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

int main(int ac, char **av) {
    
    if (ac != 3 || atoi(av[1]) < 1024)
	{
        drawBoxErrorAndExit(50, "Usage: ./ircserv [port > 1024] [password]");
		return (1);
	}
    
    try {
        Server server(atoi(av[1]), av[2]);	 
        server.run();   
    }
    catch (std::exception &e) {
        std::cerr << BOLD RED << "Error: " << e.what() << RESET << std::endl;
        return 1;
    }
    return 0;
}
