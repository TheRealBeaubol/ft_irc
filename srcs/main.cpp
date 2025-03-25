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
		int clientSocket = accept(server_fd, NULL, NULL);
		//verif_client()
		send(clientSocket, "Weclome to our IRC Server!\n", 27, 0);
		//handle_command();
		close(clientSocket);
	}
	close(server_fd);
	return (0);
}
