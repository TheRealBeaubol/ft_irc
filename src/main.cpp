/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:18:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/08 18:58:16 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "colors.hpp"

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

int main(int ac, char **av) {
    if (ac != 3) {
        drawBox(50, "Usage: ./ircserv [port] [password]");
        return 1;
    }
    (void)av;
    return 0;
}