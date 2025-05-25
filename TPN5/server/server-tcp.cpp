/**
 * Mian file for the TCP server app
 */

#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <vector>

/// Socket file descriptor of the server
int sock_fd = -1;

/**
 * signal handler used to force program exit
 */
void sig_handler(int signum)
{
	if (sock_fd > 0)
	{
		close(sock_fd);
	}
	sock_fd = -1;
}

/**
 * @param argc number of arguments
 * @param argv server <port>
 */
int main(const int argc, char* argv[])
{
	// Verify arguments
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
		return EXIT_FAILURE;
	}

	// Setup signal handlers
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	// Create a socket for the server
	sock_fd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		std::cerr << "Failed to create socket" << std::endl;
		return EXIT_FAILURE;
	}

	// Set socket options so the server can accept both IPv4 and IPv6 connections
	if (constexpr int disable{}; setsockopt(sock_fd, IPPROTO_IPV6, IPV6_V6ONLY, &disable, sizeof(disable)) < 0)
	{
		if (sock_fd != -1)
			close(sock_fd);
		std::cerr << "Failed to set socket option" << std::endl;
		return EXIT_FAILURE;
	}

	// Bind socket to address/port
	sockaddr_in6 addr{};
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(std::stoi(argv[1]));
	addr.sin6_addr = in6addr_any;
	if (bind(sock_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
	{
		if (sock_fd != -1)
			close(sock_fd);
		std::cerr << "Failed to bind socket" << std::endl;
		return EXIT_FAILURE;
	}

	// Setup max number of connections
	if (listen(sock_fd, 1) < 0)
	{
		if (sock_fd != -1)
			close(sock_fd);
		std::cerr << "Failed to listen" << std::endl;
		return EXIT_FAILURE;
	}

	// Begin passive open (accept)
	sockaddr_in6 client_addr{};
	socklen_t client_addr_len = sizeof(client_addr);
	const int client_fd = accept(sock_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_addr_len);
	if (client_fd < 0)
	{
		if (sock_fd != -1)
			close(sock_fd);
		std::cerr << "Failed to accept connection" << std::endl;
		return EXIT_FAILURE;
	}

	std::string msg{};
	while (true)
	{
		// Wait for the client to send a message
		std::vector<char> buffer(1024);
		if (read(client_fd, buffer.data(), 1024) <= 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			close(client_fd);
			std::cerr << "Failed to read from client" << std::endl;
			return EXIT_FAILURE;
		}
		msg = {buffer.data()};

		// TODO: log received message
		std::cout << "CLIENT: " << msg << std::endl;

		// If the message is "quit" finish
		if (msg == "quit")
		{
			std::cout << "Client disconnected" << std::endl;
			break;
		}

		// Response
		msg = "success";
		if (write(client_fd, msg.data(), msg.size()) < 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			close(client_fd);
			std::cerr << "Failed to write to client" << std::endl;
			return EXIT_FAILURE;
		}
		// TODO: log sent message
	}

	if (sock_fd != -1)
		close(sock_fd);
	close(client_fd);
	std::cout << "Closing server" << std::endl;
	return EXIT_SUCCESS;
}
