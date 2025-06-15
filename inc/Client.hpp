/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:18:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/12 23:07:22 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Includes.hpp"

class Channel;

class Client
{
	public:

		Client();
		Client(int clientFd);
		Client(int clientFd, struct pollfd clientPollFd);
		~Client();

		void setClientFd(int clientFd);
		int getClientFd() const;

		void setClientPollFd(struct pollfd clientPollFd);
		struct pollfd getClientPollFd() const;

		void setNickName(std::string nick_name);
		std::string getNickName() const;

		void setUserName(std::string user_name);
		std::string getUserName() const;

		void setIsLog(bool isLog);
		bool getIsLog() const;

		void setIsAuth(bool isAuth);
		bool getIsAuth() const;

		std::string& getInputBuffer();
		void appendToBuffer(const std::string& data);
		void clearBuffer();

	private:

		int _clientFd;
		struct pollfd _clientPollFd;
		bool _isAuth;
		bool _isLog;
		std::string _nickName;
		std::string _userName;
		std::string _inputBuffer;
};
