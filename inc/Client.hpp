/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:18:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/02 22:00:21 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Includes.hpp"
#include "Channel.hpp"

class Channel;

class Client {
	public:
		Client();
		Client(int clientSocket);
		~Client();

		void setClientSocket(int clientSocket);
		int getClientSocket() const;

		void setNickName(std::string nick_name);
		std::string getNickName() const;

		void setUserName(std::string user_name);
		std::string getUserName() const;

		void setIsLog(bool isLog);
		bool getIsLog() const;

		void setIsAuth(bool isAuth);
		bool getIsAuth() const;

		void addChannel(Channel *channel);
		void removeChannel(Channel *channel);
		std::vector<Channel *> getChannels() const;
	private:
		int _clientSocket;
		std::vector<Channel *>_channels;

		bool _isAuth;
		bool _isLog;
		std::string _nickName;
		std::string _userName;
};