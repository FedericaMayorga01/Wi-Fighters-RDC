#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>

int sock_fd = -1;

// Función para obtener la timestamp actual en formato legible
std::string current_timestamp()
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::localtime(&now_c);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

void sig_handler(int signum)
{
	if (sock_fd > 0)
	{
		close(sock_fd);
	}
	sock_fd = -1;
}

int main(const int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
		return EXIT_FAILURE;
	}

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	// Abrir archivo de log en modo append
	std::ofstream log_file("server.log", std::ios::app);
	if (!log_file.is_open())
	{
		std::cerr << "Failed to open log file" << std::endl;
		perror("open"); // <-- Agrega esta línea para ver el error del sistema
		return EXIT_FAILURE;
	}

	sock_fd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		std::cerr << "Failed to create socket" << std::endl;
		return EXIT_FAILURE;
	}

	if (constexpr int disable{}; setsockopt(sock_fd, IPPROTO_IPV6, IPV6_V6ONLY, &disable, sizeof(disable)) < 0)
	{
		if (sock_fd != -1)
			close(sock_fd);
		std::cerr << "Failed to set socket option" << std::endl;
		return EXIT_FAILURE;
	}

	sockaddr_in6 addr{};
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(std::stoi(argv[1]));
	addr.sin6_addr = in6addr_any;
	if (bind(sock_fd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
	{
		if (sock_fd != -1)
			close(sock_fd);
		std::cerr << "Failed to bind socket" << std::endl;
		return EXIT_FAILURE;
	}

	if (listen(sock_fd, 1) < 0)
	{
		if (sock_fd != -1)
			close(sock_fd);
		std::cerr << "Failed to listen" << std::endl;
		return EXIT_FAILURE;
	}

	while (true) // Bucle principal del servidor
	{
		sockaddr_in6 client_addr{};
		socklen_t client_addr_len = sizeof(client_addr);
		const int client_fd = accept(sock_fd, reinterpret_cast<sockaddr *>(&client_addr), &client_addr_len);
		if (client_fd < 0)
		{
			std::cerr << "Failed to accept connection" << std::endl;
			continue;
		}

		std::string msg{};
		while (true)
		{
			std::vector<char> buffer(1024);
			ssize_t bytes_read = read(client_fd, buffer.data(), 1024);
			if (bytes_read <= 0)
			{
				std::cerr << "Failed to read from client" << std::endl;
				break;
			}
			msg = std::string(buffer.data(), bytes_read);

			log_file << "[" << current_timestamp() << "] Received: " << msg << std::endl;
			std::cout << "CLIENT: " << msg << std::endl;

			if (msg == "quit")
			{
				std::cout << "Client disconnected" << std::endl;
				break; // Sale del bucle y cierra la conexión SIN enviar "success"
			}

			msg = "success";
			if (write(client_fd, msg.data(), msg.size()) < 0)
			{
				std::cerr << "Failed to write to client" << std::endl;
				break;
			}
			log_file << "[" << current_timestamp() << "] Sent: " << msg << std::endl;
		}
		close(client_fd);
		log_file << "[" << current_timestamp() << "] Client connection closed" << std::endl;
	}

	if (sock_fd != -1)
		close(sock_fd);
	log_file << "[" << current_timestamp() << "] Server closed" << std::endl;
	log_file.close();
	std::cout << "Closing server" << std::endl;
	return EXIT_SUCCESS;
}
