/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:34:24 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 21:02:27 by lboiteux         ###   ########.fr       */
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
        } 
        else
            tokens.push_back(token);
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