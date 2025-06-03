/**
 * Mian file for the UDP server app
 */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sodium.h>

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
 * @param filename path to the key file
 * @param key char array to store the key
 */
bool load_key(const std::string& filename, unsigned char key[crypto_secretbox_KEYBYTES]) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;
    file.read(reinterpret_cast<char*>(key), crypto_secretbox_KEYBYTES);
    return file.gcount() == crypto_secretbox_KEYBYTES;
}

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

    if (sodium_init() == -1) 
    {
        std::cerr << "Failed to initialize libsodium" << std::endl;
        return EXIT_FAILURE;
    }

    unsigned char key[crypto_secretbox_KEYBYTES];
    if (!load_key("../key.txt", key)) 
    {
        std::cerr << "Failed to load encryption key" << std::endl;
        return EXIT_FAILURE;
    }

	// Setup signal handlers
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	// Create a socket for the server
	sock_fd = socket(AF_INET6, SOCK_DGRAM, 0);
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

	// Abrir archivo de log en modo append
    std::ofstream log_file("server_udp.log", std::ios::app);
    if (!log_file.is_open())
    {
        std::cerr << "Failed to open log file" << std::endl;
        perror("open");
        return EXIT_FAILURE;
    }

	std::string msg{};
	socklen_t addr_len = sizeof(addr);
	while (true)
	{
        std::vector<unsigned char> nonce(crypto_secretbox_NONCEBYTES);
		std::vector<unsigned char> buffer(1024);
		// Wait for the client to send a message
        if (recvfrom(sock_fd, nonce.data(), nonce.size(), 0, reinterpret_cast<sockaddr*>(&addr), &addr_len) <= 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			std::cerr << "Failed to read from client" << std::endl;
			return EXIT_FAILURE;
		}

        auto bytes_read = recvfrom(sock_fd, buffer.data(), buffer.size(), 0, reinterpret_cast<sockaddr*>(&addr), &addr_len);
		if (bytes_read <= 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			std::cerr << "Failed to read from client" << std::endl;
			return EXIT_FAILURE;
		}

        std::vector<unsigned char> decrypted(bytes_read - crypto_secretbox_MACBYTES);    
        if (crypto_secretbox_open_easy(decrypted.data(), buffer.data(), bytes_read, nonce.data(), key) != 0) {
            std::cerr << "Decription failed" << std::endl;
            break;
        }

		msg = std::string(decrypted.begin(), decrypted.end());

		log_file << "[" << current_timestamp() << "] Received: " << msg << std::endl;
		std::cout << "CLIENT: " << msg << std::endl;

		// If the message is "quit" finish
		if (msg == "quit")
		{
			std::cout << "Client disconnected" << std::endl;
			break;
		}

		// Response
		msg = "success";
		if (sendto(sock_fd, msg.data(), msg.size(), 0, reinterpret_cast<sockaddr*>(&addr), addr_len) < 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			std::cerr << "Failed to write to client" << std::endl;
			return EXIT_FAILURE;
		}
		log_file << "[" << current_timestamp() << "] Sent: " << msg << std::endl;
	}

	if (sock_fd != -1)
		close(sock_fd);
	log_file << "[" << current_timestamp() << "] Server closed" << std::endl;
	log_file.close();
	std::cout << "Closing server" << std::endl;
	return EXIT_SUCCESS;
}

