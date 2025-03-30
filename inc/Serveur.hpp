#include "includes.hpp"
#include "Salon.hpp"
#include "Client.hpp"

class Serveur
{
	public:
		Serveur();
		~Serveur();

		void set_serveurSocket(int serveurSocket);
		int get_serveurSocket();

		int handdle_new_connexion();
		void send_message(int clientSocket, const char *msg);

		void add_client(Client* client);
		void remove_client(Client* client);
		std::vector<Client *> get_clients();

		void add_poll_fd(struct pollfd poll_fd);
		void remove_poll_fd(struct pollfd poll_fd);
		std::vector<struct pollfd> get_poll_fds();

		void add_salon(Salon *salon);
		void remove_salon(Salon *salon);
		std::vector<Salon *> get_salon();

	private:

		// std::string serveur_name;
		int serveurSocket;
		// int max_connexion;
		// int max_queue_connexion;

		std::vector<Client *> clients;
		std::vector<struct pollfd> poll_fds;

		std::vector<Salon *> salons;
};

struct pollfd initPollfd(int fd)
{
	return (struct pollfd) {fd, POLLIN, 0};
}

int setNonBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
	{ 
        return -1; 
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1)
	{
        return -1;
    }
    return 0;
}

// int checkFailure(int ret, const char *msg)
// {
//     if (ret == -1)
// 	{
//         std::cerr << msg << ": " << strerror(errno) << std::endl;
//         return 1;
//     }
//     return 0;
// }

Serveur::Serveur()
{
	std::cout << "Creating default IRC serveur" << std::endl;

	// Création du socket (AF_INET pour IPv4, SOCK_STREAM pour TCP)
	this->serveurSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serveurSocket == -1)
		std::cerr << "Erreur lors de la création du socket." << std::endl;

	// Permet de réutiliser immédiatement le port après la fermeture
	int opt = 1;
	setsockopt(this->serveurSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	// Configuration de l'adresse du serveur
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(6667); // Le port IRC par défaut
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Permet à tous les hôtes d'accéder

	// Lier le socket à l'adresse spécifiée
	if (bind(this->serveurSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		std::cerr << "Erreur lors de la liaison du socket." << std::endl;

	// Mise en écoute des connexions
	int max_queue_connexion = 5;
	if (listen(this->serveurSocket, max_queue_connexion) == -1)
		std::cerr << "Erreur lors de l'écoute sur le socket." << std::endl;

	this->add_client(new Client(serveurSocket));
	this->add_poll_fd(initPollfd(serveurSocket));

	std::cout << "Serveur IRC en écoute sur le port 6667..." << std::endl << std::endl;
}

Serveur::~Serveur(){}

void Serveur::set_serveurSocket(int serveurSocket){this->serveurSocket = serveurSocket;}
int Serveur::get_serveurSocket(){return this->serveurSocket;}

void Serveur::add_client(Client* client)
{
	std::cout << "Adding " << client->get_clientSocket() << " to serveur.clients " << this->clients.size() << std::endl;
	this->clients.push_back(client);
}

void Serveur::remove_client(Client* client)
{
	std::cout << "Removing " <<  client->get_clientSocket() << " from serveur.clients " << std::endl;
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if ( (this->clients[i] == client) && (i < this->clients.size()) )
		{
			this->clients.erase(this->clients.begin() + i);
		}
	}
}

std::vector<Client *> Serveur::get_clients()
{
	return this->clients;
}

void	Serveur::add_salon(Salon *salon)
{
	std::cout << "Adding " << salon->getSalonName() << " to serveur.salon " << std::endl;
	this->salons.push_back(salon);
}

void	Serveur::remove_salon(Salon *salon){
	
	for (size_t i = 0; i < this->salons.size(); i++)
	{
		if ( (this->salons[i]->getSalonName() == salon->getSalonName()) && (i < this->salons.size()) )
		{
			std::cout << "Removing " << salon->getSalonName() << " from serveur.salons " << std::endl;
			this->salons.erase(this->salons.begin() + i);
		}
	}
}

std::vector<Salon *> Serveur::get_salon(){ return(this->salons); }

void Serveur::add_poll_fd(struct pollfd poll_fd)
{
	std::cout << "Adding " << poll_fd.fd << " to serveur.poll_fds " << this->poll_fds.size() << std::endl;
	this->poll_fds.push_back(poll_fd);
}

void Serveur::remove_poll_fd(struct pollfd poll_fd)
{
	for (size_t i = 0; i < this->poll_fds.size(); i++)
	{
		if ( (this->poll_fds[i].fd == poll_fd.fd) && (i < this->poll_fds.size()) )
		{
			std::cout << "Removing " << poll_fd.fd << " from serveur.poll_fds " << std::endl;
			this->poll_fds.erase(this->poll_fds.begin() + i);
		}
	}
}

std::vector<struct pollfd> Serveur::get_poll_fds()
{
	return this->poll_fds;
}

int Serveur::handdle_new_connexion()
{
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(this->serveurSocket, (struct sockaddr*)&client_addr, &client_len);
	if (client_fd >= 0)
	{
		if (setNonBlocking(client_fd) == 0)
		{
			std::cout << "New connexion accepted: " << client_fd << std::endl;

			Client *client = new Client(client_fd);
			this->add_client(client);
			this->add_poll_fd(initPollfd(client_fd));

			this->send_message(client->get_clientSocket(), "Welcome to the IRC server!\r\n");
		}
		else
		{
			close(client_fd);
			return -1;
		}
	}
	return 0;
}

void Serveur::send_message(int clientSocket, const char *msg)
{
	std::cout << "Sending message : " << msg << std::endl;
	send(clientSocket, msg, strlen(msg), 0);
}
