/**
 * Main file for TCP client app
 */

#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <bits/ostream.tcc>
#include <netdb.h>
#include <strings.h>
#include <csignal>
#include <vector>

/// Socket file descriptor to communicate whit the server
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
 * @param argv client <host ipv6> <port> <n° of iterations> <ms between messages>
 */
int main(const int argc, char *argv[])
{
	// Verify arguments
	if (argc < 5)
	{
		std::cerr << "Usage: " << argv[0] << " <host> <port> <iterations> <delta time ms>" << std::endl;
		return EXIT_FAILURE;
	}

	// Setup signal handlers
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	// Find server address info using host and port arguments
	addrinfo hints{}, *res;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(argv[1], argv[2], &hints, &res) != 0 || res == nullptr)
	{
		std::cerr << "Failed to resolve host/port" << std::endl;
		return EXIT_FAILURE;
	}

	// Create a socket to communicate with the server
	sock_fd = socket(res->ai_family, res->ai_socktype, 0);
	if (sock_fd < 0)
	{
		std::cerr << "Failed to create socket" << std::endl;
		freeaddrinfo(res);
		return EXIT_FAILURE;
	}

	// Connect to server
	if (connect(sock_fd, res->ai_addr, res->ai_addrlen) < 0)
	{
		if (sock_fd > 0)
		{
			close(sock_fd);
		}
		freeaddrinfo(res);
		std::cerr << "Failed to connect to server" << std::endl;
		return EXIT_FAILURE;
	}

	const auto iterations = std::stoi(argv[3]);
	const auto sleep_ms = std::stoi(argv[4]);
	const std::string preamble = "WI-Fighters-";
	std::string msg{};

	// Begin communications
	for (auto i = 0; i < iterations; ++i)
	{
		// First send a message (WI_Fighters-i)
		msg = preamble + std::to_string(i);
		if (write(sock_fd, msg.data(), msg.size()) < 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			freeaddrinfo(res);
			std::cerr << "Failed to write to server" << std::endl;
			return EXIT_FAILURE;
		}

		// Then receive a successful response
		std::vector<char> buffer(1024);
		if (read(sock_fd, buffer.data(), 1024) <= 0)
		{
			if (sock_fd != -1)
				close(sock_fd);

			freeaddrinfo(res);
			std::cerr << "Failed to read from server" << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "SERVER: " << buffer.data() << std::endl;

		// Sleep
		usleep(sleep_ms * 1000);
	}

	if (sock_fd != -1)
	{
		// Send the "quit" message to the server before exiting
		msg = "quit";
		write(sock_fd, msg.data(), msg.size());
		close(sock_fd);
	}
	freeaddrinfo(res);

	return EXIT_SUCCESS;
}
