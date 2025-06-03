/**
 * Main file for UDP client app
 */

#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <bits/ostream.tcc>
#include <netdb.h>
#include <strings.h>
#include <csignal>
#include <vector>
#include <sodium.h>
#include <fstream>

/// Socket file descriptor to communicate whit the server
int sock_fd = -1;

/**
 * @param filename path to the key file
 * @param key char array to store the key
 */
bool load_key(const std::string& filename, unsigned char key[crypto_secretbox_KEYBYTES])
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;
    file.read(reinterpret_cast<char*>(key), crypto_secretbox_KEYBYTES);
    return file.gcount() == crypto_secretbox_KEYBYTES;
}

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

    // Initialize sodium (for encryption)
    if (sodium_init() == -1) 
    {
        std::cerr << "Failed to initialize libsodium" << std::endl;
        return EXIT_FAILURE;
    }

    // Retrieve key for encryption
    unsigned char key[crypto_secretbox_KEYBYTES];
    if (!load_key("../key.txt", key)) 
    {
        std::cerr << "Failed to load encryption key" << std::endl;
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

	// Begin communications
	for (auto i = 0; i < iterations; ++i)
	{
		// First send a message (WI_Fighters-i)
		msg = preamble + std::to_string(i);
        std::vector<unsigned char> bytes(msg.begin(), msg.end());

        // Generate encryption one time key
        unsigned char nonce[crypto_secretbox_NONCEBYTES];
        randombytes_buf(nonce, sizeof nonce);
        
        // Encrypt message
        std::vector<unsigned char> ciphertext(bytes.size() + crypto_secretbox_MACBYTES);
        crypto_secretbox_easy(ciphertext.data(), bytes.data(), bytes.size(), nonce, key);

		if (sendto(sock_fd, nonce, sizeof(nonce), 0, res->ai_addr, res->ai_addrlen) < 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			freeaddrinfo(res);
			std::cerr << "Failed to write to server" << std::endl;
			return EXIT_FAILURE;
		}

        if (sendto(sock_fd, ciphertext.data(), ciphertext.size(), 0, res->ai_addr, res->ai_addrlen) < 0)
		{
			if (sock_fd != -1)
				close(sock_fd);
			freeaddrinfo(res);
			std::cerr << "Failed to write to server" << std::endl;
			return EXIT_FAILURE;
		}

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
		std::cout << "SERVER: " << buffer.data() << std::endl;

		// Sleep
		usleep(sleep_ms * 1000);
	}

	if (sock_fd != -1)
	{
		// Send the "quit" message to the server before exiting
        unsigned char nonce[crypto_secretbox_NONCEBYTES];
        randombytes_buf(nonce, sizeof nonce);
        sendto(sock_fd, nonce, sizeof(nonce), 0, res->ai_addr, res->ai_addrlen);

		msg = "quit";
        std::vector<unsigned char> bytes(msg.begin(), msg.end());
        std::vector<unsigned char> ciphertext(bytes.size() + crypto_secretbox_MACBYTES);
        crypto_secretbox_easy(ciphertext.data(), bytes.data(), bytes.size(), nonce, key);
		sendto(sock_fd, ciphertext.data(), ciphertext.size(), 0, res->ai_addr, res->ai_addrlen);
		close(sock_fd);
	}
	freeaddrinfo(res);

	return EXIT_SUCCESS;
}


