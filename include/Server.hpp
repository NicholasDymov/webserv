#include <vector>

class Server {
  public:
	Server();
	Server(int port);
	Server(const Server &other);
	~Server();

	Server &operator=(const Server &other);

  private:
	std::vector<int> socket_fds;
};
