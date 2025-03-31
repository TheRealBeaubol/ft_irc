#include "../inc/includes.hpp"
#include "../inc/Client.hpp"
#include "../inc/Serveur.hpp"
#include "../inc/Salon.hpp"
#include <sys/socket.h>

//struct pollfd initPollfd(int fd) { return (struct pollfd) {fd, POLLIN, 0}; }

int stoi(const char *str) {
    int result = 0;
    for (int i = 0; str[i]; i++) { result = result * 10 + str[i] - '0'; }
    return result;
}

int checkFailure(int ret, const char *msg) {
    if (ret == -1) {
        std::cerr << msg << ": " << strerror(errno) << std::endl;
        return 1;
    }
    return 0;
}

/*int setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) { 
        return -1; 
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        return -1;
    }
    return 0;
}*/

std::vector<std::string> split(const std::string& str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string item;

	// Utilisation de getline pour séparer la chaîne au niveau du délimiteur
	while (getline(ss, item, delimiter)) {
		result.push_back(item);
	}

	return result;
}

void	command_nick(Client *client, std::vector<std::string> commands)
{
	std::cout << "NICK command call" << std::endl;
	client->set_nick_name(commands[1]);
	std::cout << "nickname: " << client->get_nick_name() << std::endl;
	std::string msg = ":" + client->get_nick_name() + " NICK " + commands[1] + "\r\n";
	send(client->get_clientSocket(), msg.c_str() , msg.length(), 0);
}

void	command_join(Serveur *serveur, Client *client, std::vector<std::string> commands)
{
	std::cout << "JOIN command call" << std::endl;
	commands[1].erase(std::remove(commands[1].begin(), commands[1].end(), '\n'), commands[1].end()); //faut vraiment remplacer cette ligne ptdrrrrr
	commands[1].erase(std::remove(commands[1].begin(), commands[1].end(), '\r'), commands[1].end()); //faut vraiment remplacer cette ligne ptdrrrrr
	std::cout << "command param: " << commands[1] << std::endl;
	for (size_t i = 0; i < serveur->get_salon().size() + 1; i++)
	{
		std::cout << i << std::endl;
		std::string	msg = ":" + client->get_nick_name() + " JOIN :#" + commands[1] + "\r\n";
		if ( i < serveur->get_salon().size() )
		{
			if (serveur->get_salon()[i]->getSalonName() == commands[1])
			{
				serveur->get_salon()[i]->addClient(client);
				serveur->get_salon()[i]->showClient();
				serveur->send_message(client->get_clientSocket(), msg.c_str());
			}
		}
		else if (i == serveur->get_salon().size())
		{
			std::cout << "Salon actually doesn't exist we going to create it" << std::endl;
			Salon *salon = new Salon(commands[1]);
			serveur->add_salon(salon);
			if (i != 0)
				i++;
			serveur->get_salon()[i]->addClient(client);
			//serveur->get_salon()[i]->
			serveur->get_salon()[i]->showClient();
			serveur->send_message(client->get_clientSocket(), msg.c_str());
			return ;
		}
	}
}

void	handle_receive_message(std::vector<struct pollfd> poll_fds, int i, Serveur *serveur)
{
	char	buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	int bytesRead = recv(poll_fds[i].fd, buffer, sizeof(buffer), 0);
	std::string s_buffer = std::string(buffer);
	s_buffer.erase(std::remove(s_buffer.begin(), s_buffer.end(), '\r'), s_buffer.end());
	if (bytesRead > 0)
	{
		Client *client = serveur->get_clients()[i];
		if (client)
			std::cout << "message receive: " << buffer << std::endl;
		std::vector<std::string> commands = split(buffer, ' ');
		std::cout << "command :" << commands[0] << std::endl;
		if (commands[0] == "NICK")
			command_nick(client, commands);
		else if (commands[0] == "JOIN")
			command_join(serveur, client, commands);
		return ;
	}
	else
	{
		std::cout << "Client " << poll_fds[i].fd << " disconnected." << std::endl;
		std::cout << "i = " << i << std::endl;
		close(poll_fds[i].fd);
		serveur->remove_poll_fd(poll_fds[i]);
		serveur->remove_client(serveur->get_clients()[i]);
		// --i;
	}
	std::cout << "error in message reception" << std::endl;
}

int	handle_new_connection(int client_fd, std::vector<struct pollfd> poll_fds)
{	
	//std::vector<Client *> clientsVector;


	if (client_fd >= 0) 
	{
		if (setNonBlocking(client_fd) == 0) 
		{
			struct pollfd client_pollfd = initPollfd(client_fd);
            poll_fds.push_back(client_pollfd);
            std::cout << "Accepted new client: " << client_fd << std::endl;
            //clientsVector.push_back(new Client(client_fd));
			send(client_fd, "Weclome to our IRC Server!\n", 27, 0);
		} 
		else 
		{
			close(client_fd);
			return (-1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	(void) av;
	if (ac != 3)
	{
		std::cout << "error: wrong number of argument" << std::endl;
		return (1);
	}
	Serveur *serveur = new Serveur;
	/*Salon	*salooncaca = new Salon("CACA");
	Salon	*saloonpipi = new Salon("PIPI");
	Salon	*saloon = new Salon("CHANEL");
		
	serveur->add_salon(salooncaca);
	serveur->add_salon(saloonpipi);
	serveur->add_salon(saloon);*/
	while (true)
	{
		std::vector<struct pollfd> poll_fds = serveur->get_poll_fds();

		int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
		if (poll_count < 0)
		{
			std::cout << "poll failed" << ": " << strerror(errno) << std::endl;
			break;
		}

		// Check if there is activity on serveur_fd, which mean that there is a new connection
		if (poll_fds[0].revents & POLLIN && serveur->handdle_new_connexion() == -1)
			continue;

		for (size_t i = 1/*ou 1 mais jsp prq ca marche pas*/; i < poll_fds.size(); ++i)
		{
			if (poll_fds[i].revents & POLLIN)
			{
				handle_receive_message(poll_fds, i, serveur);
			}
		}
		//verif_client()
		//while (true)
		//handle_command();
		//close(client_fd);
	}
	for (size_t i = 0; i < serveur->get_poll_fds().size(); ++i) { close(serveur->get_poll_fds()[i].fd); }
	return (0);
}
