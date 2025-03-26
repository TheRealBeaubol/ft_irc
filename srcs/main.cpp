#include "../inc/includes.hpp"
#include <sys/socket.h>

struct pollfd initPollfd(int fd) { return (struct pollfd) {fd, POLLIN, 0}; }

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

int setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) { 
        return -1; 
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        return -1;
    }
    return 0;
}

void	handle_receive_message(int	c_soc)
{
	char	buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	int bytesRead = recv(c_soc, buffer, sizeof(buffer), 0);
	std::string s_buffer = std::string(buffer);
	s_buffer.erase(std::remove(s_buffer.begin(), s_buffer.end(), '\r'), s_buffer.end());
	if (bytesRead <= 0)
	{
		std::cout << "error in message reception" << std::endl;
		return ;
	}
	std::cout << "message receive: " << buffer << std::endl;
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
	if (ac != 3)
	{
		std::cout << "error: wrong number of argument" << std::endl;
		return (1);
	}

	int	server_fd;
	int	port = stoi(av[1]);	
	(void) ac;
	
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (checkFailure(server_fd, "socket")) { return 1; }
    std::cout << "Port: " << port << std::endl << "Socket created !" << std::endl << "Server fd: " << server_fd << std::endl;
    
    int opt = 1;
    if (checkFailure(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)), "setsockopt")) { return 1;}  
    std::cout << "Socket options set !" << std::endl;

    sockaddr_in address = {AF_INET, htons(port), {INADDR_ANY}, {0}};
    
    if (checkFailure(bind(server_fd, (sockaddr *)&address, sizeof(address)), "bind")) { return 1; }
    std::cout << "Socket binded !" << std::endl;
    
    if (checkFailure(listen(server_fd, SOMAXCONN), "listen")) { return 1; }
    std::cout << "Server listening !" << std::endl;

    if (checkFailure(setNonBlocking(server_fd), "setNonBlocking")) { return 1; }
    std::cout << "Server set to non-blocking !" << std::endl;

	std::vector<struct pollfd> poll_fds;
    struct pollfd server_pollfd = initPollfd(server_fd);
    poll_fds.push_back(server_pollfd);
	
	std::cout << "Server listening on port : " << port << std::endl;

    //std::vector<Client *> clientsVector;
	while (true)
	{
		int poll_count = poll(&poll_fds[0], poll_fds.size(), -1);
        if (poll_count < 0) {
            std::cerr << "poll failed" << ": " << strerror(errno) << std::endl;
            break;
        }

		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);
		int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

		if (poll_fds[0].revents & POLLIN && handle_new_connection(client_fd, poll_fds) == -1)
			continue;

		for (size_t i = 0/*ou 1 mais jsp prq ca marche pas*/; i < poll_fds.size(); ++i)
		{
			if (poll_fds[i].revents & POLLIN)
			{
				handle_receive_message(client_fd);
			}
		}
		//verif_client()
		//while (true)
		//handle_command();
		//close(client_fd);
	}
	close(server_fd);
	return (0);
}
