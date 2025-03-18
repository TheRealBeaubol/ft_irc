/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:59:50 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/15 00:23:29 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
#include "define.hpp"
#include "error_draw.hpp"
#include "Client.hpp"
#include "ParseMessage.hpp"