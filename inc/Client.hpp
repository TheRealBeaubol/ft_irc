/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:18:37 by lboiteux          #+#    #+#             */
/*   Updated: 2025/04/01 02:56:44 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Includes.hpp"

class Client {
	public:
		Client();
		Client(int clientSocket);
		~Client();

		void setClientSocket(int clientSocket);
		int getClientSocket() const;

		void setNickName(std::string nick_name);
		std::string getNickName() const;

		void setUSerName(std::string user_name);
		std::string getUSerName() const;

		void setRealName(std::string real_name);
		std::string getRealName() const;

		void setIsAuth(bool isAuth);
		bool getIsAuth() const;

	private:
		int _clientSocket;

		bool _isAuth;
		std::string _nickName;
		std::string _userName;
		std::string _realName;
};