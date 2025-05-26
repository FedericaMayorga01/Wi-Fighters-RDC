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
#include <chrono> // Agrega esto

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
	std::vector<double> latencias; // Vector para guardar latencias

	// Begin communications
	for (auto i = 0; i < iterations; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now(); // Marca tiempo antes de enviar

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

		auto end = std::chrono::high_resolution_clock::now(); // Marca tiempo después de recibir
		std::chrono::duration<double, std::milli> rtt = end - start;
		latencias.push_back(rtt.count()); // Guarda la latencia en ms

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

	// Al final, calcula y muestra estadísticas
	if (!latencias.empty()) {
		double suma = 0, max = latencias[0], min = latencias[0], jitter = 0;
		for (size_t i = 0; i < latencias.size(); ++i) {
			suma += latencias[i];
			if (latencias[i] > max) max = latencias[i];
			if (latencias[i] < min) min = latencias[i];
			if (i > 0) jitter += std::abs(latencias[i] - latencias[i-1]);
		}
		double promedio = suma / latencias.size();
		jitter = jitter / (latencias.size() - 1);

		std::cout << "Latencia promedio: " << promedio << " ms\n";
		std::cout << "Latencia máxima: " << max << " ms\n";
		std::cout << "Latencia mínima: " << min << " ms\n";
		std::cout << "Jitter: " << jitter << " ms\n";
	}

	return EXIT_SUCCESS;
}
