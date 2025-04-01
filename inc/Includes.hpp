/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:59:50 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 00:58:31 by lboiteux         ###   ########.fr       */
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

#include "Channel.hpp"
#include "Client.hpp"
#include "Colors.hpp"
#include "Commands.hpp"
#include "Define.hpp"
#include "ErrorCode.hpp"
#include "ErrorDraw.hpp"
#include "Server.hpp"