#include "IrcaaBot.hpp"

void
usage()
{
	std::cerr << "usage : ./ircaaBot <port> <password>" << std::endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        usage();
        exit(EXIT_FAILURE);
    }
    IrcaaBot x(std::atoi(argv[1]), argv[2]);
    return 0;
}
