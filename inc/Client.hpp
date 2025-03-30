#pragma once
#include "includes.hpp"

class Client
{
	public:
		Client();
		Client(int clientSocket);
		~Client();

		void set_clientSocket(int clientSocket);
		int get_clientSocket() const;

		void set_nick_name(std::string nick_name);
		std::string get_nick_name() const;

		void set_real_name(std::string real_name);
		std::string get_real_name() const;

	private:

		int clientSocket;

		std::string nick_name;
		std::string real_name;
};

Client::Client(){}
Client::Client(int clientSocket)
{
	std::cout << "Client been created with " << clientSocket << " as clientSocket" << std::endl;
	this->clientSocket = clientSocket;
	this->set_nick_name("mhervoch");
}
Client::~Client(){}

void Client::set_clientSocket(int clientSocket){this->clientSocket = clientSocket;}
int Client::get_clientSocket() const{return this->clientSocket;}

void Client::set_nick_name(std::string nick_name){this->nick_name = nick_name;}
std::string Client::get_nick_name() const{return this->nick_name;}

void Client::set_real_name(std::string real_name){this->real_name = real_name;}
std::string Client::get_real_name() const{return this->real_name;}
