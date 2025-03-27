/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:18:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/27 22:53:14 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

class Client {
	public:
		Client();
		Client(int clientSocket);
		~Client();

		void setClientSocket(int clientSocket);
		int getClientSocket();

		void setNickName(std::string nick_name);
		std::string getNickName();

		void setRealName(std::string real_name);
		std::string getRealName();

	private:
		int _clientSocket;

		std::string _nickName;
		std::string _realName;
};