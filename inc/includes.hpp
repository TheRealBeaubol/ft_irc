/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:59:50 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/31 20:17:42 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstring>
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

#include "colors.hpp"
#include "define.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "errorDraw.hpp"