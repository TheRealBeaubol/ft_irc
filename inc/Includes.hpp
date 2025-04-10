/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:59:50 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/10 23:41:42 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <vector>
#include <sstream>

#include <algorithm>

#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h> 
#include <fcntl.h>
#include <poll.h>
#include <cstring>
#include <map>
#include <string>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <csignal>

#include "Channel.hpp"
#include "Client.hpp"
#include "Colors.hpp"
#include "Commands.hpp"
#include "Define.hpp"
#include "ErrorCode.hpp"
#include "Server.hpp"

std::string itoa(int n);
std::vector<std::string> split(std::string str, char delimiter);
std::string repeatChar(int n, const std::string& s);
void drawBoxErrorAndExit(int width, std::string const title);

std::vector<std::string> splitBufferIntoLines(const std::string &buffer);
std::vector<std::string> tokenizeLine(const std::string &line);
std::vector<std::vector<std::string> > tokenize(std::string buffer);