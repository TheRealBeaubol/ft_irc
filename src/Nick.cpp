#include "includes.hpp"

bool	verifNickname(Server *server, std::vector<std::string> commands){
	
	std::vector<Client *>	clients = server->getClients();
	if (clients.size() == 2)
		return 1;
	for (size_t i = 0; i < clients.size(); ++i){
		
		if (clients[i]->getNickName() == commands[1])
			return (0);
	}
	return (1);
}

oid    commandNick(Server *server, Client *client, std::vector<std::string> commands)
{
    std::cout << "NICK command call" << std::endl;

	std::string	old_nickname = client->getNickName();

	if (commands.size() < 2)
		throw IrcError(client->getNickname(), ERR_NONICKNAMEGIVEN);

	if (verifNickname(server, commands))
	{
    	client->setNickName(commands[1]);
    	std::cout << "nickname: " << client->getNickName() << std::endl;
    	std::string msg = ":" + old_nickname + " NICK " + commands[1] + "\r\n";
    	send(client->getClientSocket(), msg.c_str() , msg.length(), 0);
	}
}
