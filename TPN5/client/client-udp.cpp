/**
 * Main file for UDP client app
 */

#include <chrono>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <bits/ostream.tcc>
#include <netdb.h>
#include <strings.h>
#include <csignal>
#include <vector>
#include <fstream>

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
	hints.ai_socktype = SOCK_DGRAM;
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

	const auto iterations = std::stoi(argv[3]);
	const auto sleep_ms = std::stoi(argv[4]);
	const std::string preamble = "WI-Fighters-";
	std::string msg{};
	std::vector<double> rtt;
	std::vector<double> send_latency;
	std::vector<double> receive_latency;

	// Begin communications
	for (auto i = 0; i < iterations; ++i)
	{
		auto start_time = std::chrono::high_resolution_clock::now();

		// First send a message (WI_Fighters-i)
		msg = preamble + std::to_string(i);
        std::vector<unsigned char> bytes(msg.begin(), msg.end());

        if (sendto(sock_fd, bytes.data(), bytes.size(), 0, res->ai_addr, res->ai_addrlen) < 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			freeaddrinfo(res);
			std::cerr << "Failed to write to server" << std::endl;
			return EXIT_FAILURE;
		}
        auto send_time = std::chrono::high_resolution_clock::now();

		// Then receive a successful response
		std::vector<char> buffer(1024);
		if (recvfrom(sock_fd, buffer.data(), 1024, 0, nullptr, nullptr) <= 0)
		{
			if (sock_fd != -1)
				close(sock_fd);

			freeaddrinfo(res);
			std::cerr << "Failed to read from server" << std::endl;
			return EXIT_FAILURE;
		}

		auto end_time = std::chrono::high_resolution_clock::now(); // Marca tiempo después de recibir
		rtt.push_back(std::chrono::duration<double, std::milli>(end_time - start_time).count());
		send_latency.push_back(std::chrono::duration<double, std::milli>(send_time - start_time).count());
		receive_latency.push_back(std::chrono::duration<double, std::milli>(end_time - send_time).count());

		std::cout << "SERVER: " << buffer.data() << std::endl;

		// Sleep
		usleep(sleep_ms * 1000);
	}

	if (sock_fd != -1)
	{
		// Send the "quit" message to the server before exiting
		msg = "quit";
        std::vector<unsigned char> bytes(msg.begin(), msg.end());
		sendto(sock_fd, bytes.data(), bytes.size(), 0, res->ai_addr, res->ai_addrlen);
		close(sock_fd);
	}
	freeaddrinfo(res);

	if (!rtt.empty()) {
		double sum_rtt = 0, max_rtt = rtt[0], min_rtt = rtt[0];
		double sum_send = 0, max_send = send_latency[0], min_send = send_latency[0];
		double sum_recv = 0, max_recv = receive_latency[0], min_recv = receive_latency[0];

		double jitter = 0;
		for (size_t i = 0; i < rtt.size(); ++i) {
			sum_rtt += rtt[i];
			if (rtt[i] > max_rtt) max_rtt = rtt[i];
			if (rtt[i] < min_rtt) min_rtt = rtt[i];
			if (i > 0) jitter += std::abs(rtt[i] - rtt[i-1]);

			sum_send += send_latency[i];
			if (send_latency[i] > max_send) max_send = send_latency[i];
			if (send_latency[i] < min_send) min_send = send_latency[i];

			sum_recv += receive_latency[i];
			if (receive_latency[i] > max_recv) max_recv = receive_latency[i];
			if (receive_latency[i] < min_recv) min_recv = receive_latency[i];
		}
		jitter = jitter / (rtt.size() - 1);

		std::cout << "RTT promedio: " << sum_rtt / rtt.size() << " ms" << std::endl;
		std::cout << "Latencia de envío promedio: " << sum_send / send_latency.size() << " ms" << std::endl;
		std::cout << "Latencia de envío máxima: " << max_send << " ms" << std::endl;
		std::cout << "Latencia de envío mínima: " << min_send << " ms" << std::endl;
		std::cout << "Latencia de recepción promedio: " << sum_recv / receive_latency.size() << " ms" << std::endl;
		std::cout << "Latencia de recepción máxima: " << max_recv << " ms" << std::endl;
		std::cout << "Latencia de recepción mínima: " << min_recv << " ms" << std::endl;
		std::cout << "Jitter: " << jitter << " ms" << std::endl;
	}

	return EXIT_SUCCESS;
}

