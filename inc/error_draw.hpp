/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_draw.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:01:21 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/13 19:01:51 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "colors.hpp"

std::string repeatChar(int n, const std::string& s);
void drawBox(int width, std::string const title);