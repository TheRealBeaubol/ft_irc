/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:45:19 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 21:30:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes.hpp"

std::string itoa(int n) {

	std::ostringstream oss;
	oss << n;

	return oss.str();
}

std::vector<std::string> split(std::string str, char delimiter) {

	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter))
		tokens.push_back(token);

	return tokens;
}

std::string repeatChar(int n, const std::string& s) {
    
    std::string result;

    result.reserve(n * s.size());

    for (int i = 0; i < n; ++i)
        result += s;

    return result;
}

void drawBoxErrorAndExit(int width, std::string const title) {
    
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
    exit(1);
}

